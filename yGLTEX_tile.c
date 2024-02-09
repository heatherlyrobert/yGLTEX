/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"

/*
 *  main trouble, so much depends on glyphs from fonts and they vary widely
 *
 *
 *  MINIMAL RAMP
 *   0  1  2  3  4  5  6  7  8  9
 *      ¥  :  -  =  +  *  #  %  @
 *
 *
 *  MEGA-STANDARD RAMP
 *  
 *     .'`,^:";~      lighter
 *     -_+<>i!lI?
 *     /\|()1{}[]
 *     rcvunxzjft
 *     LCJUYXZO0Q
 *     oahkbdpqwm
 *     *WMB8&%$#@     darker
 *
 *  ANOTHER-MEGA RAMP
 *  
 *     @MBHER#KWXDFPQASUZ
 *     bdehx*8Gm&04LOVYkp
 *     q5Tagns69owz$CIu23
 *     Jcfry%1v7l+it[]{}?
 *     j|()=~!-/<>\"^_';,:'.
 *
 *
 *  SHRIKE SPECIFIC 20-STEP RAMP -- decently symmetrical and centered
 *   0  1  2  3  4  5  6  7  8  9  -  1  2  3  4  5  6  7  8  9
 *      ∑  ≤  -  ·  ~  ¥  +  =  ‚  §  Ò  Ï  G  Ì  ˇ  @  B  #  Ø
 *
 */


/*---(ready to create)----------------*/
static   char    zYGLTEX_ready     =  '-';

/*---(png title)----------------------*/
static   char    zYGLTEX_title     [LEN_DESC]  = "";
static   char    zYGLTEX_style     =  'r';       /* rag-edge vs wrapped          */
static   char    zYGLTEX_ramp      =  '-';       /* alpha to char ramping        */

/*---(layout)-------------------------*/
static   int     zYGLTEX_xmax      =    0;       /* layout x maximum             */
static   int     zYGLTEX_ymax      =    0;       /* layout y maximum             */

/*---(maximum dimentions in txt)------*/
static   int     zYGLTEX_xactual   =    0;       /* source x maximum (longest)   */
static   int     zYGLTEX_yactual   =    0;       /* source y maximum             */

/*---(header field count)-------------*/
static   int     zYGLTEX_fields    =    0;       /* tile header field structure  */

/*---(tile dimensions)----------------*/
static   int     zYGLTEX_xscale    =    0;       /* tile tile x size             */
static   int     zYGLTEX_yscale    =    0;       /* tile tile y size             */
static   int     zYGLTEX_buffer    =    0;       /* tile tile buffer (x & y)     */

/*---(png dimensions)-----------------*/
static   int     zYGLTEX_wide      =    0;       /* png width required           */
static   int     zYGLTEX_tall      =    0;       /* png height required          */

/*---(tile usage)---------------------*/
static   int     zYGLTEX_total     =    0;
static   int     zYGLTEX_used      =    0;



static  char     zYGLTEX_print [LEN_RECD] = "";



/*====================------------------------------------====================*/
/*===----                    text input controls                       ----===*/
/*====================------------------------------------====================*/
static void      o___CONTROLS___________o (void) {;}

char
ygltex_tile_ramp        (int a_line, char a_recd [LEN_HUGE], char *r_ramp)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_HUND]  = "";
   int         x_len       =    0;
   char        x_ramp      =  '∑';
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_ramp   != NULL)  *r_ramp = '∑';
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "#@ "            ,  3) != 0) {
      DEBUG_YGLTEX    yLOG_note    ("not a control record, must start with ∂#@ ∂");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "#@ tile_ramp "  , 13) != 0) {
      DEBUG_YGLTEX    yLOG_note    ("not a ramp record, must identify with ∂#@ tile_ramp ∂");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("a_line"    , a_line);
   ystrlcpy  (t, a_recd + 13, LEN_HUND);
   ystrltrim (t, ySTR_BOTH, LEN_HUND);
   DEBUG_YGLTEX    yLOG_info    ("t"         , t);
   x_len = strlen (t);
   /*---(checks)-------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len < 1) {
      DEBUG_YGLTEX    yLOG_note    ("ramp is empty");
      yURG_err ('f', "%4d, ∂#@ tile_ramp∂ is empty", a_line);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len > 1 && t [1] != ' ') {
      yURG_err ('f', "%4d, ∂#@ tile_ramp∂ (%-2.2s) must be char followed by at least one space", a_line, t);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_ramp = t [0];
   DEBUG_YGLTEX    yLOG_char    ("x_ramp"    , x_ramp);
   --rce;  if (x_ramp == 0 || strchr (YGLTEX_RAMPS, x_ramp) == NULL) {
      yURG_err ('f', "%4d, ∂#@ tile_ramp∂ (%c) is not valid [%s]", a_line, x_ramp, YGLTEX_RAMPS);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save∑back)----------------------*/
   if (r_ramp   != NULL)  *r_ramp = x_ramp;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_tile_title       (int a_line, char a_recd [LEN_HUGE], char r_title [LEN_DESC])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_HUND]  = "";
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_title  != NULL)  strcpy (r_title, "");
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "#@ "          ,  3) != 0) {
      DEBUG_YGLTEX    yLOG_note    ("not a control record, must start with ∂#@ ∂");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "#@ tile_title " , 14) != 0) {
      DEBUG_YGLTEX    yLOG_note    ("not a title record, must identify with ∂#@ tile_titile ∂");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("a_line"    , a_line);
   ystrlcpy  (t, a_recd + 14, LEN_HUND);
   ystrltrim (t, ySTR_BOTH, LEN_HUND);
   DEBUG_YGLTEX    yLOG_info    ("t"         , t);
   x_len = strlen (t);
   /*---(checks)-------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len < 1) {
      DEBUG_YGLTEX    yLOG_note    ("title is empty");
      yURG_err ('f', "%4d, ∂#@ tile_title∂ is empty", a_line);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len > 29) {
      DEBUG_YGLTEX    yLOG_note    ("title is too long");
      yURG_err ('f', "%4d, ∂#@ tile_title∂ length (%d) is too long (1-29)", a_line, x_len);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save∑back)----------------------*/
   if (r_title  != NULL)  ystrlcpy (r_title, t, LEN_DESC);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_tile_layout      (int a_line, char a_recd [LEN_HUGE], int *x_count, int *y_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_HUND]  = "";
   char       *p           = NULL;
   char       *q           =  " ";
   char       *r           = NULL;
   char        c           =    0;
   int         x           =    0;
   int         y           =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (x_count  != NULL)  *x_count  = 0;
   if (y_count  != NULL)  *y_count  = 0;
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "#@ "          ,  3) != 0) {
      DEBUG_YGLTEX    yLOG_note    ("not a control record, must start with ∂#@ ∂");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "#@ tile_layout ", 13) != 0) {
      DEBUG_YGLTEX    yLOG_note    ("not a layout record, must identify with ∂#@ tile_layout ∂");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("a_line"    , a_line);
   ystrlcpy  (t, a_recd, LEN_HUND);
   ystrltrim (t, ySTR_BOTH, LEN_HUND);
   DEBUG_YGLTEX    yLOG_info    ("t"         , t);
   /*---(prepare)------------------------*/
   p = strtok_r (t + 15, q, &r);
   while (p != NULL) {
      DEBUG_YGLTEX    yLOG_info    ("p"         , p);
      switch (c) {
      case  0 :  x = atoi (p);  break;
      case  1 :  y = atoi (p);  break;
      }
      ++c;
      p = strtok_r (NULL, q, &r);
   }
   /*---(checks)-------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("c"         , c);
   --rce;  if (c != 2) {
      DEBUG_YGLTEX    yLOG_note    ("field count must be 2");
      yURG_err ('f', "%4d, ∂#@ tile_layout∂ field count (%d) must be 2 [x y]", a_line, c);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("x_count"   , x);
   --rce;  if (x < 1 || x > 100) {
      DEBUG_YGLTEX    yLOG_note    ("x_count must be >= 1 and <= 100");
      yURG_err ('f', "%4d, ∂#@ tile_layout∂ x_count (%d) out-of-range (1-100)", a_line, x);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("y_count"   , y);
   --rce;  if (y < 0 || y > 100) {
      DEBUG_YGLTEX    yLOG_note    ("y_count must be >= 0 and <= 100");
      yURG_err ('f', "%4d, ∂#@ tile_layout∂ y_count (%d) out-of-range (0-100)", a_line, y);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save∑back)----------------------*/
   if (x_count  != NULL)  *x_count  = x;
   if (y_count  != NULL)  *y_count  = y;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_tile_sizing      (int a_line, char a_recd [LEN_HUGE], int *x_scale, int *y_scale, int *r_buffer)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_HUND]  = "";
   char       *p           = NULL;
   char       *q           =  " ";
   char       *r           = NULL;
   char        c           =    0;
   int         x           =    0;
   int         y           =    0;
   int         m           =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (x_scale  != NULL)  *x_scale  = 0;
   if (y_scale  != NULL)  *y_scale  = 0;
   if (r_buffer != NULL)  *r_buffer = 0;
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "#@ "          ,  3) != 0) {
      DEBUG_YGLTEX    yLOG_note    ("not a control record, must start with ∂#@ ∂");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "#@ tile_size ", 13) != 0) {
      DEBUG_YGLTEX    yLOG_note    ("not a sizing record, must identify with ∂#@ tile_size ∂");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("a_line"    , a_line);
   ystrlcpy  (t, a_recd, LEN_HUND);
   ystrltrim (t, ySTR_BOTH, LEN_HUND);
   /*---(parsing)------------------------*/
   p = strtok_r (t + 13, q, &r);
   while (p != NULL) {
      DEBUG_YGLTEX    yLOG_info    ("p"         , p);
      switch (c) {
      case  0 :  x = atoi (p);  break;
      case  1 :  y = atoi (p);  break;
      case  2 :  m = atoi (p);  break;
      }
      ++c;
      p = strtok_r (NULL, q, &r);
   }
   /*---(checks)-------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("c"         , c);
   --rce;  if (c != 3) {
      DEBUG_YGLTEX    yLOG_note    ("field count must be 3");
      yURG_err ('f', "%4d, ∂#@ tile_size∂ field count (%d) must be 3 [x y m]", a_line, c);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(checks)-------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("x_scale"   , x);
   --rce;  if (x < 20 || x > 100) {
      DEBUG_YGLTEX    yLOG_note    ("x_scale must be >= 20 and <= 100");
      yURG_err ('f', "%4d, ∂#@ tile_size∂ x_scale (%d) out-of-range (20-100)", a_line, x);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("y_scale"   , y);
   --rce;  if (y < 20 || y > 100) {
      DEBUG_YGLTEX    yLOG_note    ("y_scale must be >= 20 and <= 100");
      yURG_err ('f', "%4d, ∂#@ tile_size∂ y_scale (%d) out-of-range (20-100)", a_line, y);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("r_buffer"  , m);
   --rce;  if (m < 5 || m > 10) {
      DEBUG_YGLTEX    yLOG_note    ("r_buffer must be >= 5 and <= 10");
      yURG_err ('f', "%4d, ∂#@ tile_size∂ buffer (%d) out-of-range (5-10)", a_line, m);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save∑back)----------------------*/
   if (x_scale  != NULL)  *x_scale  = x;
   if (y_scale  != NULL)  *y_scale  = y;
   if (r_buffer != NULL)  *r_buffer = m;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_tile_fields      (int a_line, char a_recd [LEN_HUGE], int *r_fields)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_HUND]  = "";
   int         x_len       =    0;
   char       *p           = NULL;
   char       *q           =  " ";
   char       *r           = NULL;
   int         c           =    0;
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_fields != NULL)  *r_fields = 0;
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "#@ "          ,  3) != 0) {
      DEBUG_YGLTEX    yLOG_note    ("not a control record, must start with ∂#@ ∂");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "#@ tile_fields "  , 15) != 0) {
      DEBUG_YGLTEX    yLOG_note    ("not a title record, must identify with ∂#@ tile_fields ∂");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("a_line"    , a_line);
   ystrlcpy  (t, a_recd, LEN_HUND);
   ystrltrim (t, ySTR_BOTH, LEN_HUND);
   DEBUG_YGLTEX    yLOG_info    ("t"         , t);
   /*---(prepare)------------------------*/
   p = strtok_r (t + 15, q, &r);
   while (p != NULL) {
      DEBUG_YGLTEX    yLOG_info    ("p"         , p);
      switch (c) {
      case  0 :  n = atoi (p);  break;
      }
      ++c;
      p = strtok_r (NULL, q, &r);
   }
   /*---(checks)-------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("c"         , c);
   --rce;  if (c != 1) {
      DEBUG_YGLTEX    yLOG_note    ("field count must be 1");
      yURG_err ('f', "%4d, ∂#@ tile_fields∂ field count (%d) must be 1 [n]", a_line, c);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("n"         , n);
   --rce;  if (n < 1 || n > 3) {
      DEBUG_YGLTEX    yLOG_note    ("field count must be 1-3");
      yURG_err ('f', "%4d, ∂#@ tile_fields∂ count (%d) is out-of-range (1-3)", a_line, n);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save∑back)----------------------*/
   if (r_fields != NULL)  *r_fields = n;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                  writing and reading title                   ----===*/
/*====================------------------------------------====================*/
static void      o___TITLE______________o (void) {;}

char
ygltex_title_write      (int a_width, uchar *r_row, char a_title [LEN_DESC], int a_wide, int a_tall, int a_total, int a_used, int a_xmax, int a_ymax, int a_fields, int a_xscale, int a_yscale, int a_buffer)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        t           [LEN_FULL]  = "";
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("r_row"     , r_row);
   --rce;  if (r_row  == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_width"   , a_width);
   --rce;  if (a_width <  LEN_HUND) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("a_title"   , a_title);
   --rce;  if (a_title  == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_info    ("a_title"   , a_title);
   /*---(write)--------------------------*/
   sprintf (t, "TEXTURE TILES  %-30.30s  %5d  %5d  %3d  %3d  %3d  %3d  %3d  %3d  %3d  %3d  %-4.4s ",
         a_title, a_wide, a_tall, a_total, a_used, a_xmax, a_ymax, a_fields, a_xscale, a_yscale, a_buffer, P_VERNUM);
   ystrlcpy (r_row, t, a_width);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_title_read       (int a_width, uchar *a_row, char r_title [LEN_DESC], int *r_wide, int *r_tall, int *r_total, int *r_used, int *r_xmax, int *r_ymax, int *r_fields, int *r_xscale, int *r_yscale, int *r_buffer)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_FULL]  = "";
   char       *p           = NULL;
   char       *q           =  "";
   char       *r           = NULL;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_title  != NULL)  strcpy (r_title, "");
   if (r_wide   != NULL)  *r_wide   = 0;
   if (r_tall   != NULL)  *r_tall   = 0;
   if (r_total  != NULL)  *r_total  = 0;
   if (r_used   != NULL)  *r_used   = 0;
   if (r_xmax   != NULL)  *r_xmax   = 0;
   if (r_ymax   != NULL)  *r_ymax   = 0;
   if (r_fields != NULL)  *r_fields = 0;
   if (r_xscale != NULL)  *r_xscale = 0;
   if (r_yscale != NULL)  *r_yscale = 0;
   if (r_buffer != NULL)  *r_buffer = 0;
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("a_width"   , a_width);
   --rce;  if (a_width <  LEN_FULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("a_row"     , a_row);
   --rce;  if (a_row  == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save∑values)--------------------*/
   ystrlcpy (t, a_row, LEN_FULL);
   p = strtok_r (t, q, &r);
   --rce;  while (p != NULL) {
      DEBUG_YGLTEX    yLOG_complex ("loop"      , "%2d Â%sÊ", c, p);
      switch (c) {
      case  0 :  if (strncmp (p, "TEXTURE TILES", 13) != 0) {
                    DEBUG_YGLTEX    yLOG_note    ("title prefix is invalid");
                    DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
                    return rce;
                 }
      case  1 :  ystrlcpy (r_title, p, LEN_DESC);  ystrltrim (r_title, ySTR_BOTH, LEN_DESC);   break;
      case  2 :  if (r_wide   != NULL)  *r_wide   = atoi (p);               break;
      case  3 :  if (r_tall   != NULL)  *r_tall   = atoi (p);               break;
      case  4 :  if (r_total  != NULL)  *r_total  = atoi (p);               break;
      case  5 :  if (r_used   != NULL)  *r_used   = atoi (p);               break;
      case  6 :  if (r_xmax   != NULL)  *r_xmax   = atoi (p);               break;
      case  7 :  if (r_ymax   != NULL)  *r_ymax   = atoi (p);               break;
      case  8 :  if (r_fields != NULL)  *r_fields = atoi (p);               break;
      case  9 :  if (r_xscale != NULL)  *r_xscale = atoi (p);               break;
      case 10 :  if (r_yscale != NULL)  *r_yscale = atoi (p);               break;
      case 11 :  if (r_buffer != NULL)  *r_buffer = atoi (p);               break;
      }
      p = strtok_r (NULL, q, &r);
      ++c;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                writing and reading tile header               ----===*/
/*====================------------------------------------====================*/
static void      o___HEADER_____________o (void) {;}

char
ygltex_header_write     (int a_rlen, uchar *b_rdata, int a_col, int a_xscale, int a_buffer, int a_fields, char a_cat [LEN_LABEL], char a_sub [LEN_LABEL], char a_name [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_rpos      =    0;
   int         x_rend      =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("b_rdata"   , b_rdata);
   --rce;  if (b_rdata  == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_col"     , a_col);
   --rce;  if (a_col    <   0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_xscale"  , a_xscale);
   --rce;  if (a_xscale <   0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_buffer"  , a_buffer);
   --rce;  if (a_buffer <   0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_rpos    = a_buffer + (a_buffer * a_col) + (a_xscale * a_col);
   DEBUG_YGLTEX    yLOG_value   ("x_rpos"    , x_rpos);
   x_rpos   *= 4;
   DEBUG_YGLTEX    yLOG_value   ("x_rpos"    , x_rpos);
   x_rend    = x_rpos + (a_xscale * 4);
   DEBUG_YGLTEX    yLOG_value   ("x_rend"    , x_rend);
   DEBUG_YGLTEX    yLOG_point   ("a_rlen"    , a_rlen);
   --rce;  if (a_rlen <= x_rend) {
      DEBUG_YGLTEX    yLOG_note    ("attempting to write outside bounds of b_rdata");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_fields"  , a_fields);
   --rce;  if (a_fields <   1 || a_fields > 3) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("a_cat"     , a_cat);
   --rce;  if (a_fields != 1 && a_cat == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_info    ("a_cat"     , a_cat);
   DEBUG_YGLTEX    yLOG_point   ("a_sub"     , a_sub);
   --rce;  if (a_fields == 3 && a_sub == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_info    ("a_sub"     , a_sub);
   DEBUG_YGLTEX    yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_info    ("a_name"    , a_name);
   /*---(save∑values)--------------------*/
   switch (a_fields) {
   case  1 :  sprintf (b_rdata + x_rpos, "TILE HEADER ß %-20.20s ß"                      , a_name);                break;
   case  2 :  sprintf (b_rdata + x_rpos, "TILE HEADER ß %-20.20s ß %-20.20s ß"           , a_cat, a_name);         break;
   case  3 :  sprintf (b_rdata + x_rpos, "TILE HEADER ß %-20.20s ß %-20.20s ß %-20.20s ß", a_cat, a_sub, a_name);  break;
   default :
              DEBUG_YGLTEX    yLOG_note    ("field count not understood");
              DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
              return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return a_fields;
}

char
ygltex_header_read      (int a_rlen, uchar *a_rdata, int a_col, int a_xscale, int a_buffer, int a_fields, char r_cat [LEN_LABEL], char r_sub [LEN_LABEL], char r_name [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *q           =  "ß";
   char       *r           = NULL;
   char        c           =    0;
   int         x_rpos      =    0;
   int         x_rend      =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_cat  != NULL)  strcpy (r_cat  , "");
   if (r_sub  != NULL)  strcpy (r_sub  , "");
   if (r_name != NULL)  strcpy (r_name , "");
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_rdata"   , a_rdata);
   --rce;  if (a_rdata  == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_col"     , a_col);
   --rce;  if (a_col    <   0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_xscale"  , a_xscale);
   --rce;  if (a_xscale <   0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_buffer"  , a_buffer);
   --rce;  if (a_buffer <   0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_rpos    = a_buffer + (a_buffer * a_col) + (a_xscale * a_col);
   DEBUG_YGLTEX    yLOG_value   ("x_rpos"    , x_rpos);
   x_rpos   *= 4;
   DEBUG_YGLTEX    yLOG_value   ("x_rpos"    , x_rpos);
   x_rend    = x_rpos + (a_xscale * 4);
   DEBUG_YGLTEX    yLOG_value   ("x_rend"    , x_rend);
   DEBUG_YGLTEX    yLOG_point   ("a_rlen"    , a_rlen);
   --rce;  if (a_rlen <= x_rend) {
      DEBUG_YGLTEX    yLOG_note    ("attempting to read outside bounds of b_rdata");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_fields"  , a_fields);
   --rce;  if (a_fields <   1 || a_fields > 3) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save∑values)--------------------*/
   ystrlcpy (t, a_rdata + x_rpos, a_xscale * 4);
   p = strtok_r (t, q, &r);
   DEBUG_YGLTEX    yLOG_info    ("p"         , p);
   --rce;  if (strncmp (p, "TILE HEADER", 11) != 0) {
      DEBUG_YGLTEX    yLOG_note    ("header did not start with TILE HEADER");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   while (p != NULL) {
      if (a_fields == 3) {
         switch (c) {
         case 1 :  if (r_cat  != NULL)  { ystrlcpy (r_cat , p, LEN_LABEL);  ystrldchg (r_cat , '∑', ' ', LEN_LABEL);  ystrltrim (r_cat , ySTR_BOTH, LEN_LABEL); }  break;
         case 2 :  if (r_sub  != NULL)  { ystrlcpy (r_sub , p, LEN_LABEL);  ystrldchg (r_sub , '∑', ' ', LEN_LABEL);  ystrltrim (r_sub , ySTR_BOTH, LEN_LABEL); }  break;
         case 3 :  if (r_name != NULL)  { ystrlcpy (r_name, p, LEN_LABEL);  ystrldchg (r_name, '∑', ' ', LEN_LABEL);  ystrltrim (r_name, ySTR_BOTH, LEN_LABEL); }  break;
         }
      } else if (a_fields == 2) {
         switch (c) {
         case 1 :  if (r_cat  != NULL)  { ystrlcpy (r_cat , p, LEN_LABEL);  ystrldchg (r_cat , '∑', ' ', LEN_LABEL);  ystrltrim (r_cat , ySTR_BOTH, LEN_LABEL); }  break;
         case 2 :  if (r_name != NULL)  { ystrlcpy (r_name, p, LEN_LABEL);  ystrldchg (r_name, '∑', ' ', LEN_LABEL);  ystrltrim (r_name, ySTR_BOTH, LEN_LABEL); }  break;
         }
      } else if (a_fields == 1) {
         switch (c) {
         case 1 :  if (r_name != NULL)  { ystrlcpy (r_name, p, LEN_LABEL);  ystrldchg (r_name, '∑', ' ', LEN_LABEL);  ystrltrim (r_name, ySTR_BOTH, LEN_LABEL); }  break;
         }
      }
      p = strtok_r (NULL, q, &r);
      if (p != NULL)  ++c;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return c;
}

char
ygltex_header_audit     (int a_line, int a_col, int a_xbeg, char a_fields, char a_ramp, char a_tile [LEN_FULL], char a_inside [LEN_FULL], char *r_ramp)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_bad       =  '-';
   int         l           =    0;
   int         j           =    0;
   char        x_inside    [LEN_FULL]  = "";
   char       *p           = NULL;
   char       *q           =  " ";
   char       *r           = NULL;
   int         c           =    0;
   char        x_ramp      =  '∑';
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_complex ("a_args"    , "%3d, %3d, %3d, %3d, %c", a_line, a_col, a_xbeg, a_fields, a_ramp);
   /*---(default)------------------------*/
   if (r_ramp   != NULL)  *r_ramp = a_ramp;
   /*---(prepare)---------------------*/
   l = strlen (a_tile);
   /*---(check always)----------------*/
   --rce;  if (strncmp (a_tile,  "Å ", 2)  != 0) {
      yURG_err ('f', "%4d, tile header, column %d at pos %d (%-2.2s) does not begin with ∂Å ∂", a_line, a_col, a_xbeg, a_tile);
      x_bad = 'y';
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_tile + l - 2, " Å", 2)  != 0) {
      yURG_err ('f', "%4d, tile header, column %d at pos %d (%-2.2s) does not end with ∂ Å∂", a_line, a_col, a_xbeg + l - 2, a_tile + l - 2);
      x_bad = 'y';
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   l = strlen (a_inside);
   ystrlcpy  (x_inside, a_inside , LEN_FULL);
   ystrltrim (x_inside, ySTR_LEFT, LEN_FULL);
   a_xbeg += l - strlen (x_inside);
   ystrltrim (x_inside, ySTR_BOTH, LEN_FULL);
   l = strlen (x_inside);
   /*---(ramping)------------------------*/
   DEBUG_YGLTEX    yLOG_char    ("marker"    , x_inside [l - 2]);
   --rce;  if (x_inside [l - 2] == '[') {
      DEBUG_YGLTEX    yLOG_note    ("found ramp marker, update ramp");
      DEBUG_YGLTEX    yLOG_char    ("ramp?"     , x_inside [l - 1]);
      x_ramp = x_inside [l - 1];
      DEBUG_YGLTEX    yLOG_char    ("x_ramp"    , x_ramp);
      if (x_ramp == 0 || strchr (YGLTEX_RAMPS, x_ramp) == NULL) {
         yURG_err ('f', "%4d, tile header, column %d ramp (%c) is not valid [%s]", a_line, a_col, x_ramp, YGLTEX_RAMPS);
         DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      x_inside [l - 2] = '\0';
      l = strlen (x_inside);
   } else {
      x_ramp = a_ramp;
   }
   DEBUG_YGLTEX    yLOG_char    ("x_ramp"    , x_ramp);
   /*---(field count)--------------------*/
   DEBUG_YGLTEX    yLOG_complex ("x_inside"  , "%3dÂ%sÊ", l, x_inside);
   p = strtok_r (x_inside, q, &r);
   while (p != NULL) {
      DEBUG_YGLTEX    yLOG_info    ("p"         , p);
      ++c;
      p = strtok_r (NULL, q, &r);
   }
   --rce;  if (c != a_fields) {
      yURG_err ('f', "%4d, tile header, column %d field count %d does not match expected (%d)", a_line, a_col, c, a_fields);
      x_bad = 'y';
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(characters)---------------------*/
   DEBUG_YGLTEX    yLOG_value   ("l"         , l);
   --rce;  for (j = 0; j < l; ++j) {
      DEBUG_YGLTEX    yLOG_complex ("loop"      , "%d %c", j, x_inside [j]);
      if (strchr (YSTR_BASIC "∑ ", x_inside [j]) == NULL) {
         yURG_err ('f', "%4d, tile header, column %d at pos %d char (%c) not legal [A-Za-z0-9-._]", a_line, a_col, a_xbeg + 2 + j, x_inside [j]);
         x_bad = 'y';
         DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(save-back)----------------------*/
   if (r_ramp   != NULL)  *r_ramp = x_ramp;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_header_parse     (char a_fields, char a_ramp, char a_inside [LEN_FULL], char r_cat [LEN_LABEL], char r_sub [LEN_LABEL], char r_name [LEN_LABEL], char *r_ramp)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         l           =    0;
   char        x_inside    [LEN_FULL]  = "";
   char        x_ramp      =  '∑';
   char        x_cat       [LEN_LABEL] = "";
   char        x_sub       [LEN_LABEL] = "";
   char        x_name      [LEN_LABEL] = "";
   char       *p           = NULL;
   char       *q           =  " ";
   char       *r           = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_cat    != NULL)  strcpy (r_cat  , "");
   if (r_sub    != NULL)  strcpy (r_sub  , "");
   if (r_name   != NULL)  strcpy (r_name , "");
   if (r_ramp   != NULL)  *r_ramp = a_ramp;
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_inside"  , a_inside);
   --rce;  if (a_inside  == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_info    ("a_inside"  , a_inside);
   DEBUG_YGLTEX    yLOG_value   ("a_fields"  , a_fields);
   --rce;  if (a_fields <   1 || a_fields > 3) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)---------------------*/
   ystrlcpy  (x_inside, a_inside , LEN_FULL);
   ystrltrim (x_inside, ySTR_BOTH, LEN_FULL);
   l = strlen (x_inside);
   DEBUG_YGLTEX    yLOG_value   ("l"         , l);
   /*---(ramping))--------------------*/
   DEBUG_YGLTEX    yLOG_char    ("marker"    , x_inside [l - 2]);
   if (x_inside [l - 2] == '[') {
      DEBUG_YGLTEX    yLOG_note    ("found ramp marker, update ramp");
      DEBUG_YGLTEX    yLOG_char    ("ramp?"     , x_inside [l - 1]);
      x_ramp = x_inside [l - 1];
      x_inside [l - 2] = '\0';
      l = strlen (x_inside);
   } else {
      DEBUG_YGLTEX    yLOG_note    ("no ramp marker, use default ramp");
      x_ramp = a_ramp;
   }
   DEBUG_YGLTEX    yLOG_char    ("x_ramp"    , x_ramp);
   /*---(save∑values)--------------------*/
   DEBUG_YGLTEX    yLOG_complex ("x_inside"  , "%3dÂ%sÊ", l, x_inside);
   p = strtok_r (x_inside, q, &r);
   DEBUG_YGLTEX    yLOG_info    ("p"         , p);
   while (p != NULL) {
      if (a_fields == 3) {
         switch (c) {
         case 0 :  ystrlcpy (x_cat , p, LEN_LABEL);  ystrldchg (x_cat , '∑', ' ', LEN_LABEL);  ystrltrim (x_cat , ySTR_BOTH, LEN_LABEL);   break;
         case 1 :  ystrlcpy (x_sub , p, LEN_LABEL);  ystrldchg (x_sub , '∑', ' ', LEN_LABEL);  ystrltrim (x_sub , ySTR_BOTH, LEN_LABEL);   break;
         case 2 :  ystrlcpy (x_name, p, LEN_LABEL);  ystrldchg (x_name, '∑', ' ', LEN_LABEL);  ystrltrim (x_name, ySTR_BOTH, LEN_LABEL);   break;
         }
      } else if (a_fields == 2) {
         switch (c) {
         case 0 :  ystrlcpy (x_cat , p, LEN_LABEL);  ystrldchg (x_cat , '∑', ' ', LEN_LABEL);  ystrltrim (x_cat , ySTR_BOTH, LEN_LABEL);   break;
         case 1 :  ystrlcpy (x_name, p, LEN_LABEL);  ystrldchg (x_name, '∑', ' ', LEN_LABEL);  ystrltrim (x_name, ySTR_BOTH, LEN_LABEL);   break;
         }
      } else if (a_fields == 1) {
         switch (c) {
         case 0 :  ystrlcpy (x_name, p, LEN_LABEL);  ystrldchg (x_name, '∑', ' ', LEN_LABEL);  ystrltrim (x_name, ySTR_BOTH, LEN_LABEL);   break;
         }
      }
      p = strtok_r (NULL, q, &r);
      ++c;
      DEBUG_YGLTEX    yLOG_info    ("p"         , p);
   }
   DEBUG_YGLTEX    yLOG_value   ("c"         , c);
   --rce;  if (c != a_fields) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_cat    != NULL)  ystrlcpy (r_cat  , x_cat , LEN_LABEL);
   if (r_sub    != NULL)  ystrlcpy (r_sub  , x_sub , LEN_LABEL);
   if (r_name   != NULL)  ystrlcpy (r_name , x_name, LEN_LABEL);
   if (r_ramp   != NULL)  *r_ramp = x_ramp;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_header_handler   (char a_pass, char a_ramp, int a_line, char a_recd [LEN_HUGE], int a_xscale, int a_buffer, int a_fields, int x_max, int *r_count, char r_ramps [LEN_HUND], int a_rlen, uchar *b_rdata)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   int         x_beg       =    0;
   int         x_inc       =    0;
   char        x_ramps     [LEN_HUND]  = "";
   char        x_tile      [LEN_FULL]  = "";
   char        x_inside    [LEN_FULL]  = "";
   char        x_cat       [LEN_LABEL] = "";
   char        x_sub       [LEN_LABEL] = "";
   char        x_name      [LEN_LABEL] = "";
   char        x_ramp      =  '-';
   int         i           =    0;
   int         n           =    0;
   int         c           =    0;
   char        x_bad       =  '-';
   char       *p           = NULL;
   char       *q           =  " ";
   char       *r           = NULL;
   int         l           =    0;
   int         j           =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_char    ("a_ramp"    , a_ramp);
   /*---(default)------------------------*/
   if (r_count  != NULL)  *r_count = 0;
   if (r_ramps  != NULL) {
      for (i = 0; i < LEN_HUND; ++i)   r_ramps [i] = '\0';
      DEBUG_YGLTEX    yLOG_info    ("r_ramps"   , r_ramps);
   }
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_recd, "HÅ"     , 2) != 0) {
      DEBUG_YGLTEX    yLOG_note    ("not a header record, must start with ∂HÅ∂");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_xscale"   , a_xscale);
   --rce;  if (a_xscale < 20 || a_xscale > 100) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_fields"  , a_fields);
   --rce;  if (a_fields < 1 || a_fields > 3) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   for (i = 0; i < LEN_HUND; ++i)   x_ramps [i] = '\0';
   x_len = strlen (a_recd);
   x_inc = a_xscale + 2;
   x_beg = 1;
   /*---(parse tiles)--------------------*/
   --rce;  for (i = 0; i < 100; ++i) {
      DEBUG_YGLTEX    yLOG_complex ("column"    , "%2dc, %4db, %3di, %4de", i, x_beg, x_inc, x_beg + x_inc);
      /*---(check boundaries)------------*/
      if (x_beg + x_inc  > x_len) {
         yURG_err ('f', "%4d, tile header has too∑short or trailing junk after column %d at pos %d", a_line, n, x_beg);
         x_bad = 'y';
         break;
      }
      /*---(parse a column out)----------*/
      ystrlcpy (x_tile, a_recd + x_beg, x_inc + 1);
      l = strlen (x_tile);
      DEBUG_YGLTEX    yLOG_complex ("x_tile"    , "%3dÂ%sÊ", l, x_tile);
      ystrlcpy  (x_inside, x_tile + 2, x_inc - 3);
      l = strlen (x_inside);
      DEBUG_YGLTEX    yLOG_complex ("x_inside"  , "%3dÂ%sÊ", l, x_inside);
      /*---(check always)----------------*/
      if        (a_pass == '1') {
         rc = ygltex_header_audit   (a_line, i, x_beg, a_fields, a_ramp, x_tile, x_inside, &x_ramp);
         if (rc < 0)  x_bad = 'y';
         else {
            DEBUG_YGLTEX    yLOG_complex ("x_ramp"   , "%2d %c", i, x_ramp);
            x_ramps [i] = x_ramp;
         }
         DEBUG_YGLTEX    yLOG_info    ("x_ramps"   , x_ramps);
      } else if (a_pass == '2') {
         rc = ygltex_header_parse   (a_fields, a_ramp, x_inside, x_cat, x_sub, x_name, &x_ramp);
         if (rc < 0)  x_bad = 'y';
         else {
            DEBUG_YGLTEX    yLOG_complex ("x_ramp"   , "%2d %c", i, x_ramp);
            x_ramps [i] = x_ramp;
            rc = ygltex_header_write   (a_rlen, b_rdata, i, a_xscale, a_buffer, a_fields, x_cat, x_sub, x_name);
            if (rc < 0)  x_bad = 'y';
         }
         DEBUG_YGLTEX    yLOG_info    ("x_ramps"   , x_ramps);
      }
      /*---(next)---------------------------*/
      if (x_bad == 'y')  break;
      ++n;
      x_beg += x_inc;
      if (x_beg == x_len)  break;
   }
   /*---(trouble)------------------------*/
   --rce;  if (x_bad == 'y') {
      DEBUG_YGLTEX    yLOG_note    ("errors found in formatting");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save∑back)----------------------*/
   if (r_count  != NULL)  *r_count = n;
   if (r_ramps  != NULL) {
      for (i = 0; i < LEN_HUND; ++i)   r_ramps [i] = x_ramps [i];
      DEBUG_YGLTEX    yLOG_info    ("r_ramps"   , r_ramps);
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                 detail writing and reading                   ----===*/
/*====================------------------------------------====================*/
static void      o___DETAIL_____________o (void) {;}

char
ygltex_detail_audit     (int a_line, int a_col, int a_xbeg, char a_ramp, char a_tile [LEN_FULL], char a_inside [LEN_FULL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(prepare)---------------------*/
   l = strlen (a_tile);
   /*---(check always)----------------*/
   --rce;  if (strchr ("åÅá", a_tile [0]) == NULL) {
      yURG_err ('f', "%4d, tile detail column %d at pos %d (%c) does not begin with ∂Å∂ or ∂á∂ or ∂å∂", a_line, a_col, a_xbeg, a_tile [0]);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strchr ("åÅÜ", a_tile [l - 1]) == NULL) {
      yURG_err ('f', "%4d, tile detail column %d at pos %d (%c) does not end with ∂Å∂ or ∂Ü∂ or ∂å∂", a_line, a_col, a_xbeg + l - 1, a_tile [l - 1]);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(characters)---------------------*/
   rc = ygltex_ramp_audit (a_line, a_col, a_xbeg + 1, a_ramp, a_inside);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_detail_write     (int a_col, char a_ramp, int a_xscale, int a_buffer, char a_inside [LEN_FULL], int a_rlen, uchar *b_rdata)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   float       x_inc       = 255.0 / 9.0;
   int         i           =    0;
   uchar       c, a;
   int         l           =    0;
   int         x           =    0;
   int         x_tpos, x_rpos;
   int         r_min, r_max, r_pos;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_complex ("a_args"    , "%4d, %4d, %4d", a_col, a_xscale, a_buffer);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_inside"  , a_inside);
   --rce;  if (a_inside == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_col"     , a_col);
   --rce;  if (a_col < 0 || a_col >= 100) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("b_rdata"   , b_rdata);
   --rce;  if (b_rdata == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   l     = strlen (a_inside);
   r_min = a_buffer + (a_buffer * a_col) + (a_xscale * a_col);
   r_max = r_min + a_xscale;
   DEBUG_YGLTEX    yLOG_complex ("bounds"    , "%4d, %4d, %4d", r_min, r_max, a_rlen);
   --rce;  if (r_max >= a_rlen) {
      DEBUG_YGLTEX    yLOG_note    ("request writes outside b_rdata boundaries");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(write one line)-----------------*/
   --rce;  for (i = 0; i < l; ++i) {
      r_pos  = (r_min * 4) + (i * 4);
      c = a_inside [i];
      ygltex_ramp_char2alpha (a_ramp, c, &a);
      DEBUG_YGLTEX    yLOG_complex ("loop"      , "%4d, %4d, %c, %c", i, i * 4 + 3, c, a);
      b_rdata [r_pos    ] = 0;
      b_rdata [r_pos + 1] = 0;
      b_rdata [r_pos + 2] = 0;
      b_rdata [r_pos + 3] = a;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_detail_handler   (char a_pass, int a_line, char a_recd [LEN_HUGE], char a_ramps [LEN_HUND], int a_xscale, int a_buffer, int a_xlayout, int *r_count, int a_rlen, uchar *b_rdata)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   int         x_beg       =    0;
   int         x_inc       =    0;
   char        x_tile      [LEN_FULL]  = "";
   char        x_inside    [LEN_FULL]  = "";
   int         i           =    0;
   int         n           =    0;
   char        x_bad       =  '-';
   int         l           =    0;
   int         j           =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_count  != NULL)  *r_count = 0;
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_recd [0] != '¥') {
      DEBUG_YGLTEX    yLOG_note    ("not a detail record, must start with ∂¥∂");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strchr ("åÅá", a_recd [1]) == NULL) {
      DEBUG_YGLTEX    yLOG_note    ("not a detail record, character two must be ∂Å∂ or ∂á∂");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_xscale"  , a_xscale);
   --rce;  if (a_xscale < 20 || a_xscale > 100) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_len = strlen (a_recd);
   x_inc = a_xscale + 2;
   x_beg = 1;
   /*---(parse tiles)--------------------*/
   --rce;  for (i = 0; i < 100; ++i) {
      DEBUG_YGLTEX    yLOG_complex ("column"    , "%2dc, %4db, %3di, %4de", i, x_beg, x_inc, x_beg + x_inc);
      /*---(check boundaries)------------*/
      if (x_beg + x_inc  > x_len) {
         yURG_err ('f', "%4d, tile detail has too∑short or trailing junk after column %d at pos %d", a_line, n, x_beg);
         x_bad = 'y';
         break;
      }
      /*---(parse a column out)----------*/
      ystrlcpy (x_tile, a_recd + x_beg, x_inc + 1);
      l = strlen (x_tile);
      DEBUG_YGLTEX    yLOG_complex ("x_tile"    , "%3dÂ%sÊ", l, x_tile);
      ystrlcpy  (x_inside, x_tile + 1, x_inc - 1);
      l = strlen (x_inside);
      DEBUG_YGLTEX    yLOG_complex ("x_inside"  , "%3dÂ%sÊ", l, x_inside);
      /*---(check always)----------------*/
      if        (a_pass == '1') {
         rc = ygltex_detail_audit   (a_line, i + 1, x_beg, a_ramps [i], x_tile, x_inside);
         if (rc < 0)  x_bad = 'y';
      } else if (a_pass == '2') {
         rc = ygltex_detail_write   (i, a_ramps [i], a_xscale, a_buffer, x_inside, a_rlen, b_rdata);
      }
      /*---(next)---------------------------*/
      if (x_bad == 'y')  break;
      ++n;
      x_beg += x_inc;
      if (x_beg == x_len)  break;
   }
   /*---(trouble)------------------------*/
   --rce;  if (x_bad == 'y') {
      DEBUG_YGLTEX    yLOG_note    ("errors found in formatting");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save∑back)----------------------*/
   if (r_count  != NULL)  *r_count = n;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   read/audit text file                       ----===*/
/*====================------------------------------------====================*/
static void      o___READ_______________o (void) {;}

char
ygltex_tile_read        (FILE *f, int *b_line, int *r_len, char r_recd [LEN_HUGE], char *r_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_HUGE]  = "";
   int         x_len       =    0;
   char        t           [LEN_HUND]  = "";
   uchar       c           =  '∑';
   char        x_valid     =  '-';
   char        x_new       =  '-';
   int         x_line      =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(header)-------------------------*/
   if (r_len  != NULL)  *r_len   = 0;
   if (r_recd != NULL)  strcpy (r_recd, "");
   if (r_new  != NULL)  *r_new   = '-';
   if (b_line != NULL)  x_line = *b_line;
   /*---(open∑file)----------------------*/
   DEBUG_YGLTEX    yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read∑for∑next)------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets (x_recd, LEN_HUGE, f);
      if (feof (f))  {
         DEBUG_YGLTEX    yLOG_note    ("end of file reached");
         break;
      }
      ++x_line;
      x_len = strlen (x_recd);
      if (x_recd [x_len - 1] == '\n')  x_recd [--x_len] = '\0';
      ystrlcpy (t, x_recd, LEN_HUND);
      DEBUG_YGLTEX    yLOG_complex ("line"      , "%4d %4dÂ%sÊ", x_line, x_len, t);
      /*---(filter)----------------------*/
      c = x_recd [0];
      if      (strncmp (x_recd, "#@ "     , 3) == 0) {
         DEBUG_YGLTEX    yLOG_note    ("found a control record");
         x_valid = 'y';
      }
      else if (strncmp (x_recd, "HÅ "     , 3) == 0) {
         DEBUG_YGLTEX    yLOG_note    ("found a tile header record");
         x_valid = 'y';
         x_new   = 'y';
      }
      else if (strncmp (x_recd, "BÑÄ"     , 3) == 0) {
         DEBUG_YGLTEX    yLOG_note    ("found a tile bottom record");
         x_valid = 'y';
      }
      else if (c == (uchar) '¥' || c == '¥') {
         DEBUG_YGLTEX    yLOG_note    ("tile detail record");
         x_valid = 'y';
      }
      if (x_valid != 'y')  continue;
      /*---(accept)----------------------*/
      if (b_line != NULL)  *b_line = x_line;
      if (r_len  != NULL)  *r_len  = x_len;
      if (r_recd != NULL)  ystrlcpy (r_recd, x_recd, LEN_HUGE);
      if (r_new  != NULL)  *r_new  = x_new;
      rc = 1;
      break;
      /*---(done)------------------------*/
   }
   /*---(save-back)----------------------*/
   if (b_line != NULL)  *b_line = x_line;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return rc;
}


char
ygltex_tile_default     (char a_pass, char *r_ready, char r_title [LEN_DESC], char *r_style, char *r_ramp, int *r_wide, int *r_tall, int *r_total, int *r_used, int *r_xscale, int *r_yscale, int *r_buffer, int *r_fields, int *r_xmax, int *r_ymax, int *r_xactual, int *r_yactual)
{
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_senter  (__FUNCTION__);
   /*---(audit)--------------------------*/
   if (a_pass == '1') {
      yURG_msg ('-', "defaulting globals to initial/unusable values");
      /*---(overall)--------*/
      zYGLTEX_ready   = '-';
      strcpy (zYGLTEX_title  , "");
      zYGLTEX_style   = 'r';
      zYGLTEX_ramp    = '-';
      /*---(size)-----------*/
      zYGLTEX_wide    = 0;
      zYGLTEX_tall    = 0;
      /*---(usage)----------*/
      zYGLTEX_total   = 0;
      zYGLTEX_used    = 0;
      /*---(sizing)---------*/
      zYGLTEX_xscale  = 0;
      zYGLTEX_yscale  = 0;
      zYGLTEX_buffer  = 0;
      /*---(header)---------*/
      zYGLTEX_fields  = 0;
      /*---(layout)---------*/
      zYGLTEX_xmax    = 0;
      zYGLTEX_ymax    = 0;
      /*---(final)----------*/
      zYGLTEX_xactual = 0;
      zYGLTEX_yactual = 0;
   }
   /*---(creation)-----------------------*/
   yURG_msg ('-', "save values back to parameters");
   /*---(overall)--------*/
   if (r_ready   != NULL)   *r_ready      = zYGLTEX_ready;
   if (r_title   != NULL)   ystrlcpy (r_title  , zYGLTEX_title, LEN_DESC);
   if (r_style   != NULL)   *r_style      = zYGLTEX_style;
   if (r_ramp    != NULL)   *r_ramp       = zYGLTEX_ramp;
   /*---(size)-----------*/
   if (r_wide    != NULL)   *r_wide       = zYGLTEX_wide;
   if (r_tall    != NULL)   *r_tall       = zYGLTEX_tall;
   /*---(usage)----------*/
   if (r_total   != NULL)   *r_total      = zYGLTEX_total;
   if (r_used    != NULL)   *r_used       = zYGLTEX_used;
   /*---(sizing)---------*/
   if (r_xscale  != NULL)   *r_xscale     = zYGLTEX_xscale;
   if (r_yscale  != NULL)   *r_yscale     = zYGLTEX_yscale;
   if (r_buffer  != NULL)   *r_buffer     = zYGLTEX_buffer;
   /*---(header)---------*/
   if (r_fields  != NULL)   *r_fields     = zYGLTEX_fields;
   /*---(layout)---------*/
   if (r_xmax    != NULL)   *r_xmax       = zYGLTEX_xmax;
   if (r_ymax    != NULL)   *r_ymax       = zYGLTEX_ymax;
   /*---(actual)---------*/
   if (r_xactual != NULL)   *r_xactual    = zYGLTEX_xactual;
   if (r_yactual != NULL)   *r_yactual    = zYGLTEX_yactual;
   DEBUG_YGLTEX    yLOG_snote   ("globals values set");
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ygltex_tile_complete    (char a_pass, char a_title [LEN_DESC], char a_style, char a_ramp, int a_used, int a_xscale, int a_yscale, int a_buffer, int a_xmax, int a_ymax, int a_fields, int a_xactual, int a_yactual)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_bad       =  '-';
   /*---(quick-out)----------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(quick-out)----------------------*/
   if (a_pass != '1') {
      DEBUG_YGLTEX    yLOG_note    ("only on pass one (1)");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check result)-------------------*/
   yURG_msg ('-', "verifying overall audit quality");
   if (strcmp (a_title, "") == 0)   x_bad = 'y';
   if (a_xscale   < 20 || a_xscale > 100)   x_bad = 'y';
   if (a_yscale   < 20 || a_yscale > 100)   x_bad = 'y';
   if (a_buffer   <  5 || a_buffer >  10)   x_bad = 'y';
   if (a_xmax     <  1)                     x_bad = 'y';
   if (a_ymax     <  0)                     x_bad = 'y';
   if (a_fields   <  1 || a_fields > 3)     x_bad = 'y';
   if (a_xactual  <  1)                     x_bad = 'y';
   if (a_yactual  <  1)                     x_bad = 'y';
   DEBUG_YGLTEX    yLOG_char    ("x_bad"     , x_bad);
   --rce;  if (x_bad == 'y') {
      yURG_err ('f', "not all configuration data read");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "all configuration data read");
   /*---(save globals)-------------------*/
   zYGLTEX_ready   = 'y';
   ystrlcpy (zYGLTEX_title  , a_title, LEN_DESC);
   yURG_msg ('-', "title         Â%sÊ", zYGLTEX_title);
   zYGLTEX_style   = a_style;
   zYGLTEX_ramp    = a_ramp;
   zYGLTEX_used    = a_used;
   zYGLTEX_xmax    = a_xmax;
   zYGLTEX_ymax    = a_ymax;
   yURG_msg ('-', "count         %6dw by %6dt", zYGLTEX_xmax, zYGLTEX_ymax);
   zYGLTEX_xscale  = a_xscale;
   zYGLTEX_yscale  = a_yscale;
   zYGLTEX_buffer  = a_buffer;
   yURG_msg ('-', "scale         %6dw by %6dt with %dm", zYGLTEX_xscale, zYGLTEX_yscale, zYGLTEX_buffer);
   zYGLTEX_fields  = a_fields;
   yURG_msg ('-', "fields        %d", zYGLTEX_fields);
   zYGLTEX_xactual = a_xactual;
   zYGLTEX_yactual = a_yactual;
   yURG_msg ('-', "actual        %6dw by %6dt", zYGLTEX_xactual, zYGLTEX_yactual);
   /*---(calculate png size)-------------*/
   zYGLTEX_wide    = zYGLTEX_buffer + (zYGLTEX_buffer * zYGLTEX_xactual) + (zYGLTEX_xscale * zYGLTEX_xactual);
   zYGLTEX_tall    = zYGLTEX_buffer + (zYGLTEX_buffer * zYGLTEX_yactual) + (zYGLTEX_yscale * zYGLTEX_yactual);
   zYGLTEX_total   = zYGLTEX_xactual * zYGLTEX_yactual;
   DEBUG_YGLTEX    yLOG_complex ("png"       , "%6dw by %6dt", zYGLTEX_wide, zYGLTEX_tall);
   yURG_msg ('-', "actual        %6dw by %6dt", zYGLTEX_wide, zYGLTEX_tall);
   zYGLTEX_total   = zYGLTEX_xmax  * zYGLTEX_ymax ;
   zYGLTEX_wide    = zYGLTEX_buffer + (zYGLTEX_buffer * zYGLTEX_xmax ) + (zYGLTEX_xscale * zYGLTEX_xmax );
   if (zYGLTEX_ymax != 0) {
      zYGLTEX_total   = zYGLTEX_xmax * zYGLTEX_yactual;
      zYGLTEX_tall    = zYGLTEX_buffer + (zYGLTEX_buffer * zYGLTEX_ymax ) + (zYGLTEX_yscale * zYGLTEX_ymax );
   }
   yURG_msg ('-', "layout        %6dw by %6dt", zYGLTEX_wide, zYGLTEX_tall);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_tile_driver      (char a_pass, cchar a_tilename [LEN_HUND], int a_rbyte, png_bytep *b_rows)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   int         x_len       =    0;
   char        x_recd      [LEN_HUGE]  = "";
   /*---(inter-pass data)----------------*/
   char        x_ready, x_style, x_ramp;
   char        x_title     [LEN_DESC]  = "";
   int         x_wide, x_tall, x_total, x_used, x_xscale, x_yscale, x_buffer;
   int         x_fields, x_xmax, x_ymax, x_xactual, x_yactual;
   /*---(working fields)-----------------*/
   char        x_new       =  '-';
   char        x_rows      =    0;
   char        x_ramps     [LEN_HUND]  = "";
   int         n           =    0;
   int         x_line      =    0;
   int         x_header    =    0;
   char        x_bad       =  '-';
   int         x_ypos      =    0;
   int         x_rbyte     =    0;
   uchar      *x_rdata     = NULL;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_complex ("a_args"    , "%c, %s", a_pass, a_tilename);
   /*---(start)--------------------------*/
   if      (a_pass == '1')  yURG_msg ('>', "conducting txt file audit and data gathering...");
   else if (a_pass == '2')  yURG_msg ('>', "create png file contents...");
   else {
      DEBUG_YGLTEX    yLOG_note    ("unknown pass number");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   ygltex_tile_default     (a_pass, &x_ready, x_title, &x_style, &x_ramp, &x_wide, &x_tall, &x_total, &x_used, &x_xscale, &x_yscale, &x_buffer, &x_fields, &x_xmax, &x_ymax, &x_xactual, &x_yactual);
   /*---(header)-------------------------*/
   if (a_pass == '2') {
      x_rbyte = a_rbyte;
      x_rdata = b_rows [0];
      ygltex_title_write      (x_rbyte, x_rdata, x_title, x_wide, x_tall, x_total, x_used, x_xactual, x_yactual, x_fields, x_xscale, x_yscale, x_buffer);
   }
   /*---(open∑file)----------------------*/
   yURG_msg ('-', "openning file Â%sÊ", a_tilename);
   rc = ygltex_file_open  (a_tilename, 'r', NULL, NULL, &f);
   DEBUG_YGLTEX    yLOG_value   ("fopen"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_xactual = x_yactual = 0;
   /*---(read∑lines)---------------------*/
   while (1) {
      /*---(read)------------------------*/
      rc = ygltex_tile_read  (f, &x_line, &x_len, x_recd, &x_new);
      DEBUG_YGLTEX    yLOG_value   ("read"      , rc);
      if (rc == 0) {
         DEBUG_YGLTEX    yLOG_note    ("end of file, no more lines");
         break;
      }
      /*---(row location)----------------*/
      if (b_rows == NULL) {
         x_ypos  =    0;
         x_rbyte =    0;
         x_rdata = NULL;
      } else {
         x_ypos  = x_buffer + (x_buffer * x_yactual) + (x_yscale * x_yactual);
         x_rbyte = a_rbyte;
         DEBUG_YGLTEX    yLOG_complex ("row"       , "%3db, %3ds, %3da, %4dy", x_buffer, x_yscale, x_yactual, x_ypos);
      }
      /*---(handle new tile line)--------*/
      if  (strchr ("Yy", x_new) != NULL) {
         x_header = x_line;
         x_rows   = 0;
      }
      /*---(pass-one handlers only)------*/
      if      (a_pass == '1' && strncmp (x_recd, "#@ tile_title "  , 14) ==0) {
         rc = ygltex_tile_title   (x_line, x_recd, x_title);
         if (rc < 0)  yURG_err ('f', "%4d, ygltex_tile_title      (%d) failed", x_line, rc);
      }
      else if (a_pass == '1' && strncmp (x_recd, "#@ tile_ramp "   , 13) ==0) {
         rc = ygltex_tile_ramp    (x_line, x_recd, &x_ramp);
         if (rc < 0)  yURG_err ('f', "%4d, ygltex_tile_ramp       (%d) failed", x_line, rc);
      }
      else if (a_pass == '1' && strncmp (x_recd, "#@ tile_layout " , 15) ==0) {
         rc = ygltex_tile_layout  (x_line, x_recd, &x_xmax, &x_ymax);
         if (rc < 0)  yURG_err ('f', "%4d, ygltex_tile_layout     (%d) failed", x_line, rc);
      }
      else if (a_pass == '1' && strncmp (x_recd, "#@ tile_size "   , 13) ==0) {
         rc = ygltex_tile_sizing  (x_line, x_recd, &x_xscale, &x_yscale, &x_buffer);
         if (rc < 0)  yURG_err ('f', "%4d, ygltex_tile_sizing     (%d) failed", x_line, rc);
      }
      else if (a_pass == '1' && strncmp (x_recd, "#@ tile_fields " , 15) ==0) {
         rc = ygltex_tile_fields  (x_line, x_recd, &x_fields);
         if (rc < 0)  yURG_err ('f', "%4d, ygltex_tile_fields     (%d) failed", x_line, rc);
      }
      /*---(all-pass handlers)-----------*/
      else if (strncmp (x_recd, "BÑÄ"             ,  3) ==0) {
         if (a_pass == '1' && x_rows != x_yscale) yURG_err ('f', "%4d to %4d tile height (%d) not requested (%d)", x_header, x_line, x_rows, x_yscale);
         ++x_yactual;
      }
      else if (strncmp (x_recd, "HÅ "             ,  3) ==0) {
         if (b_rows != NULL) {
            x_ypos  -= 3;
            x_rdata  = b_rows [x_ypos];
            if (x_ypos >= x_tall) { x_ypos = 0;  x_rbyte = 0;  x_rdata == NULL; }
         }
         rc = ygltex_header_handler (a_pass, x_ramp, x_line, x_recd, x_xscale, x_buffer, x_fields, 99, &n, x_ramps, x_rbyte, x_rdata);
         if (a_pass == '1' && rc < 0)  yURG_err ('f', "%4d, ygltex_header_handler  (%d) failed", x_line, rc);
         if (n > x_xactual)  x_xactual = n;
         x_used += n;
         DEBUG_YGLTEX    yLOG_value   ("x_ramps"     , x_ramps);
      }
      else if (x_recd [0] == '¥') {
         if (b_rows != NULL) {
            x_ypos  += x_rows;
            x_rdata  = b_rows [x_ypos];
            if (x_ypos >= x_tall) { x_ypos = 0;  x_rbyte = 0;  x_rdata == NULL; }
         }
         DEBUG_YGLTEX    yLOG_complex ("to∑pass"   , "%4d %4d %p", x_ypos, x_rbyte, x_rdata);
         rc = ygltex_detail_handler (a_pass, x_line, x_recd, x_ramps, x_xscale, x_buffer, 99, &n, x_rbyte, x_rdata);
         if (a_pass == '1' && rc < 0)  yURG_err ('f', "%4d, ygltex__text_dtl_audit (%d) failed", x_line, rc);
         ++x_rows;
         if (n > x_xactual)  x_xactual = n;
      }
      /*---(done)------------------------*/
   }
   yURG_msg ('-', "processed %d lines", x_line);
   /*---(close∑file)---------------------*/
   yURG_msg ('-', "closing file");
   rc = ygltex_file_close  (NULL, NULL, &f);
   DEBUG_YGLTEX    yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check results)------------------*/
   ygltex_tile_complete    (a_pass, x_title, x_style, x_ramp, x_used, x_xscale, x_yscale, x_buffer, x_xmax, x_ymax, x_fields, x_xactual, x_yactual);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_tile_handler     (cchar a_tilename [LEN_PATH], int a_wide, int a_tall, int a_rbyte, png_bytep *b_rows)
{
   char        rc          =    0;
   rc = ygltex_tile_driver ('2', a_tilename, a_rbyte, b_rows);
   return rc;
}

char         /*-> convert ascii-art to png tiles --------------[ 123456789- ]-*/
yGLTEX_ascii2tiles      (char a_mode, cchar a_pngname [LEN_PATH], cchar a_tilename [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_ready     =  '-';
   int         x_wide, x_tall;
   /*---(audit tiles)--------------------*/
   rc = ygltex_tile_driver ('1', a_tilename, NULL, NULL);
   DEBUG_YGLTEX    yLOG_value   ("pass 1"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify results)-----------------*/
   yGLTEX_tile_data (&x_ready, NULL, NULL, NULL, &x_wide, &x_tall, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   DEBUG_YGLTEX    yLOG_char    ("x_ready"   , x_ready);
   --rce;  if ( x_ready != 'y') {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create png)---------------------*/
   rc = ygltex_file_new (a_pngname, YGLTEX_IMAGE, x_wide, x_tall, a_tilename, ygltex_tile_handler);
   DEBUG_YGLTEX    yLOG_value   ("pass 2"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                       making text                            ----===*/
/*====================------------------------------------====================*/
static void      o___PNG2TXT____________o (void) {;}


char
yGLTEX_tile_data        (char *r_ready, char r_title [LEN_DESC], char *r_style, char *r_ramp, int *r_wide, int *r_tall, int *r_total, int *r_used, int *r_xscale, int *r_yscale, int *r_buffer, int *r_fields, int *r_xmax, int *r_ymax, int *r_xactual, int *r_yactual)
{
   if (r_ready   != NULL)  *r_ready      = zYGLTEX_ready;
   if (r_title   != NULL)  ystrlcpy (r_title  , zYGLTEX_title, LEN_DESC);
   if (r_style   != NULL)  *r_style      = zYGLTEX_style;
   if (r_ramp    != NULL)  *r_ramp       = zYGLTEX_ramp;
   if (r_wide    != NULL)  *r_wide       = zYGLTEX_wide;
   if (r_tall    != NULL)  *r_tall       = zYGLTEX_tall;
   if (r_total   != NULL)  *r_total      = zYGLTEX_total;
   if (r_used    != NULL)  *r_used       = zYGLTEX_used;
   if (r_xscale  != NULL)  *r_xscale     = zYGLTEX_xscale;
   if (r_yscale  != NULL)  *r_yscale     = zYGLTEX_yscale;
   if (r_buffer  != NULL)  *r_buffer     = zYGLTEX_buffer;
   if (r_fields  != NULL)  *r_fields     = zYGLTEX_fields;
   if (r_xmax    != NULL)  *r_xmax       = zYGLTEX_xmax;
   if (r_ymax    != NULL)  *r_ymax       = zYGLTEX_ymax;
   if (r_xactual != NULL)  *r_xactual    = zYGLTEX_xactual;
   if (r_yactual != NULL)  *r_yactual    = zYGLTEX_yactual;
   return 0;
}


/*====================------------------------------------====================*/
/*===----                     unit testing                             ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST___________o (void) {;}

char*
ygltex__unit_show       (char a_ramp, int a_max, uchar a_row [LEN_RECD])
{
   uchar       c, d;
   float       x_inc       = 256.0 / 10.0;
   int         x           =    0;
   for (x = 0; x < LEN_RECD; ++x)  zYGLTEX_print [x] = '\0';
   for (x = 0; x < a_max; ++x) {
      c = a_row [x * 4 + 3];
      ygltex_ramp_alpha2char (a_ramp, c, &d);
      if (a_row [x * 4 + 0] != 0)  d = '∞';
      if (a_row [x * 4 + 1] != 0)  d = '∞';
      if (a_row [x * 4 + 2] != 0)  d = '∞';
      if (d == ' ')  d = '∑';
      zYGLTEX_print [x] = d;
   }
   return zYGLTEX_print;
}


