/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"



/*---(ready to create)----------------*/
static   char    s_ready     =  '-';

/*---(png title)----------------------*/
static   char    s_title     [LEN_DESC]  = "";

/*---(layout)-------------------------*/
static   int     s_xcount    =    0;
static   int     s_ycount    =    0;

/*---(header field count)-------------*/
static   int     s_fields    =    0;

/*---(tile dimensions)----------------*/
static   int     s_xscale    =    0;
static   int     s_yscale    =    0;
static   int     s_margin    =    0;

/*---(maximum dimentions in txt)------*/
static   int     s_xactual   =    0;
static   int     s_yactual   =    0;

/*---(png dimensions)-----------------*/
static   int     s_wide      =    0;
static   int     s_tall      =    0;



static  char s_print [LEN_RECD] = "";



/*====================------------------------------------====================*/
/*===----                       file handling                          ----===*/
/*====================------------------------------------====================*/
static void      o___FILE_______________o (void) {;}

char
ygltex__text_open       (char a_name [LEN_HUND], char a_access, FILE **r_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   FILE       *f           = NULL;
   char        x_access    [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_info    ("a_name"    , a_name);
   DEBUG_YGLTEX    yLOG_point   ("r_file"    , r_file);
   --rce;  if (r_file == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("*r_file"   , *r_file);
   --rce;  if (*r_file != NULL) {
      DEBUG_YGLTEX    yLOG_note    ("file already open");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check access)-------------------*/
   DEBUG_YGLTEX    yLOG_char    ("a_access"  , a_access);
   --rce;  switch (a_access) {
   case 'r' :   strcpy (x_access, "rt");   break;
   case 'w' :   strcpy (x_access, "wt");   break;
   default  :
                DEBUG_YGLTEX    yLOG_note    ("access request not understood");
                DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
                return rce;
   }
   /*---(open)---------------------------*/
   f = fopen (a_name, "rt");
   DEBUG_YGLTEX    yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("file could not be openned");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save∑back)----------------------*/
   *r_file = f;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex__text_close      (FILE **r_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("r_file"    , r_file);
   --rce;  if (r_file == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("*r_file"   , *r_file);
   --rce;  if (*r_file == NULL) {
      DEBUG_YGLTEX    yLOG_note    ("file not open");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(open)---------------------------*/
   fflush (*r_file);
   rc = fclose (*r_file);
   DEBUG_YGLTEX    yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_warn    ("file could not be closed");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground)-------------------------*/
   *r_file = NULL;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}




/*====================------------------------------------====================*/
/*===----                  writing and reading title                   ----===*/
/*====================------------------------------------====================*/
static void      o___TITLE______________o (void) {;}

char
ygltex__title_write     (char a_title [LEN_DESC], int x_count, int y_count, int x_scale, int y_scale, int a_margin, int a_max, uchar *r_row)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_title"   , a_title);
   --rce;  if (a_title  == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_info    ("a_title"   , a_title);
   DEBUG_YGLTEX    yLOG_point   ("r_row"     , r_row);
   --rce;  if (r_row  == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("x_count"   , x_count);
   --rce;  if (x_count  < 1) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("y_count"   , y_count);
   --rce;  if (y_count  < 1) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("x_scale"   , x_scale);
   --rce;  if (x_scale  < 20) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("y_scale"   , y_scale);
   --rce;  if (y_scale  < 20) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_margin"  , a_margin);
   --rce;  if (a_margin <  5) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_max"     , a_max);
   --rce;  if (a_max <  LEN_HUND) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   for (i = 0; i < a_max; ++i)  r_row [i] = '\0';
   /*---(save∑values)--------------------*/
   sprintf (r_row, "HEATHERLY TILES ß %-30.30s ß %3d ß %3d ß %3d ß %3d ß %1d ß %-4.4s ß",
         a_title, x_count, y_count, x_scale, y_scale, a_margin, P_VERNUM);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex__title_read      (int a_max, uchar *a_row, char r_title [LEN_DESC], int *x_count, int *y_count, int *x_scale, int *y_scale, int *r_margin)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_HUND]  = "";
   char       *p           = NULL;
   char       *q           =  "ß";
   char       *r           = NULL;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("a_max"     , a_max);
   --rce;  if (a_max <  LEN_HUND) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("a_row"     , a_row);
   --rce;  if (a_row  == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("r_title"   , r_title);
   --rce;  if (r_title  == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("x_count"   , x_count);
   --rce;  if (x_count    == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("y_count"   , y_count);
   --rce;  if (y_count    == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("x_scale"   , x_scale);
   --rce;  if (x_scale    == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("y_scale"   , y_scale);
   --rce;  if (y_scale    == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("r_margin"  , r_margin);
   --rce;  if (r_margin   == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save∑values)--------------------*/
   ystrlcpy (t, a_row, LEN_HUND);
   p = strtok_r (t, q, &r);
   while (p != NULL) {
      switch (c) {
      case 0 :  ystrlcpy (r_title, p, LEN_DESC);  ystrltrim (r_title, ySTR_BOTH, LEN_DESC);  break;
      case 1 :  *x_count  = atoi (p);               break;
      case 2 :  *y_count  = atoi (p);               break;
      case 3 :  *x_scale  = atoi (p);               break;
      case 4 :  *y_scale  = atoi (p);               break;
      case 5 :  *r_margin = atoi (p);               break;
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
ygltex__header_write    (int x, char a_cat [LEN_LABEL], char a_sub [LEN_LABEL], char a_name [LEN_LABEL], int a_max, uchar *r_row)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("x"         , x);
   --rce;  if (x < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("a_cat"     , a_cat);
   --rce;  if (a_cat == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_info    ("a_cat"     , a_cat);
   DEBUG_YGLTEX    yLOG_point   ("a_sub"     , a_sub);
   --rce;  if (a_sub == NULL) {
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
   DEBUG_YGLTEX    yLOG_point   ("r_row"     , r_row);
   --rce;  if (r_row  == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_max"     , a_max);
   --rce;  if (a_max - x <  LEN_HUND) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save∑values)--------------------*/
   sprintf (r_row + x, "%-20.20s ß %-20.20s ß %-20.20s ß",
         a_cat, a_sub, a_name);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex__header_read     (int a_max, uchar *a_row, int x, char r_cat [LEN_LABEL], char r_sub [LEN_LABEL], char r_name [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_HUND]  = "";
   char       *p           = NULL;
   char       *q           =  "ß";
   char       *r           = NULL;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("a_max"     , a_max);
   --rce;  if (a_max <  LEN_HUND) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("a_row"     , a_row);
   --rce;  if (a_row  == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("x"         , x);
   --rce;  if (x <  0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("r_cat"     , r_cat);
   --rce;  if (r_cat   == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("r_sub"     , r_sub);
   --rce;  if (r_sub   == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("r_name"    , r_name);
   --rce;  if (r_name  == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save∑values)--------------------*/
   ystrlcpy (t, a_row + x, LEN_HUND);
   p = strtok_r (t, q, &r);
   while (p != NULL) {
      switch (c) {
      case 0 :  ystrlcpy (r_cat , p, LEN_LABEL);  ystrltrim (r_cat , ySTR_BOTH, LEN_LABEL);  break;
      case 1 :  ystrlcpy (r_sub , p, LEN_LABEL);  ystrltrim (r_sub , ySTR_BOTH, LEN_LABEL);  break;
      case 2 :  ystrlcpy (r_name, p, LEN_LABEL);  ystrltrim (r_name, ySTR_BOTH, LEN_LABEL);  break;
      }
      p = strtok_r (NULL, q, &r);
      ++c;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                   read/audit text file                       ----===*/
/*====================------------------------------------====================*/
static void      o___READ_______________o (void) {;}

char
ygltex__text_read       (FILE *f, int *b_line, int *r_len, char r_recd [LEN_HUGE], char *r_new)
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
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return rc;
}

char
ygltex__text_sizing     (int a_line, char a_recd [LEN_HUGE], int *x_scale, int *y_scale, int *r_margin)
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
   if (r_margin != NULL)  *r_margin = 0;
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
   DEBUG_YGLTEX    yLOG_value   ("r_margin"  , m);
   --rce;  if (m < 5 || m > 10) {
      DEBUG_YGLTEX    yLOG_note    ("r_margin must be >= 5 and <= 10");
      yURG_err ('f', "%4d, ∂#@ tile_size∂ margin (%d) out-of-range (5-10)", a_line, m);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save∑back)----------------------*/
   if (x_scale  != NULL)  *x_scale  = x;
   if (y_scale  != NULL)  *y_scale  = y;
   if (r_margin != NULL)  *r_margin = m;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex__text_layout     (int a_line, char a_recd [LEN_HUGE], int *x_count, int *y_count)
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
ygltex__text_title      (int a_line, char a_recd [LEN_HUGE], char r_title [LEN_DESC])
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
ygltex__text_fields     (int a_line, char a_recd [LEN_HUGE], int *r_fields)
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

char
ygltex__text_hdr_audit  (int a_line, char a_recd [LEN_HUGE], int x_scale, int a_fields, int x_max, int *r_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   int         x_beg       =    0;
   int         x_inc       =    0;
   char        x_tile      [LEN_FULL]  = "";
   char        x_inside    [LEN_FULL]  = "";
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
   /*---(default)------------------------*/
   if (r_count  != NULL)  *r_count = 0;
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
   DEBUG_YGLTEX    yLOG_value   ("x_scale"   , x_scale);
   --rce;  if (x_scale < 20 || x_scale > 100) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_fields"  , a_fields);
   --rce;  if (a_fields < 1 || a_fields > 3) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_len = strlen (a_recd);
   x_inc = x_scale + 2;
   x_beg = 1;
   /*---(parse tiles)--------------------*/
   --rce;  for (i = 0; i < 100; ++i) {
      DEBUG_YGLTEX    yLOG_complex ("column"    , "%2dc, %4db, %3di, %4de", i, x_beg, x_inc, x_beg + x_inc);
      if (x_beg + x_inc  > x_len) {
         yURG_err ('f', "%4d, tile header has too∑short or trailing junk after column %d at pos %d", a_line, n, x_beg);
         x_bad = 'y';
         break;
      }
      ystrlcpy (x_tile, a_recd + x_beg, x_inc + 1);
      l = strlen (x_tile);
      DEBUG_YGLTEX    yLOG_complex ("x_tile"    , "%3dÂ%sÊ", l, x_tile);
      /*---(check always)----------------*/
      if (strncmp (x_tile,  "Å ", 2)  != 0) {
         yURG_err ('f', "%4d, tile header column %d at pos %d does not begin with ∂Å ∂", a_line, n + 1, x_beg);
         x_bad = 'y';
         break;
      }
      if (strncmp (x_tile + x_inc - 2, " Å", 2)  != 0) {
         yURG_err ('f', "%4d, tile header column %d at pos %d does not end with ∂ Å∂", a_line, n + 1, x_beg + x_inc - 2);
         x_bad = 'y';
         break;
      }
      /*---(field count)--------------------*/
      ystrlcpy  (x_inside, x_tile + 2, x_inc - 3);
      l = strlen (x_inside);
      DEBUG_YGLTEX    yLOG_complex ("x_inside"  , "%3dÂ%sÊ", l, x_inside);
      c = 0;
      p = strtok_r (x_inside, q, &r);
      while (p != NULL) {
         DEBUG_YGLTEX    yLOG_info    ("p"         , p);
         ++c;
         p = strtok_r (NULL, q, &r);
      }
      if (c != a_fields) {
         yURG_err ('f', "%4d, tile header column %d field count %d does not match expected (%d)", a_line, n + 1, c, a_fields);
         x_bad = 'y';
         break;
      }
      /*---(characters)---------------------*/
      l = strlen (x_inside);
      for (j = 0; j < l; ++j) {
         if (strchr (YSTR_BASIC "∑ ", x_inside [j]) == NULL) {
            yURG_err ('f', "%4d, tile header column %d pos %d char (%c) not legal", a_line, n + 1, x_beg + 2 + j, x_inside [j]);
            x_bad = 'y';
            break;
         }
      }
      if (x_bad == 'y')  break;
      /*---(next)---------------------------*/
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

char
ygltex__text_hdr_one    (int a_line, int a_col, int x_beg, char a_fields, char a_tile [LEN_FULL], char a_inside [LEN_FULL])
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
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(prepare)---------------------*/
   l = strlen (a_tile);
   /*---(check always)----------------*/
   --rce;  if (strncmp (a_tile,  "Å ", 2)  != 0) {
      yURG_err ('f', "%4d, tile header column %d at pos %d does not begin with ∂Å ∂", a_line, a_col, x_beg);
      x_bad = 'y';
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_tile + l - 2, " Å", 2)  != 0) {
      yURG_err ('f', "%4d, tile header column %d at pos %d does not end with ∂ Å∂", a_line, a_col, x_beg + l - 2);
      x_bad = 'y';
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(field count)--------------------*/
   ystrlcpy  (x_inside, a_tile + 2, l - 3);
   l = strlen (x_inside);
   DEBUG_YGLTEX    yLOG_complex ("x_inside"  , "%3dÂ%sÊ", l, x_inside);
   p = strtok_r (x_inside, q, &r);
   while (p != NULL) {
      DEBUG_YGLTEX    yLOG_info    ("p"         , p);
      ++c;
      p = strtok_r (NULL, q, &r);
   }
   --rce;  if (c != a_fields) {
      yURG_err ('f', "%4d, tile header column %d field count %d does not match expected (%d)", a_line, a_col, c, a_fields);
      x_bad = 'y';
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(characters)---------------------*/
   l = strlen (a_inside);
   --rce;  for (j = 0; j < l; ++j) {
      if (strchr (YSTR_BASIC "∑ ", x_inside [j]) == NULL) {
         yURG_err ('f', "%4d, tile header column %d pos %d char (%c) not legal", a_line, a_col, x_beg + 2 + j, x_inside [j]);
         x_bad = 'y';
         DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex__png_hdr_one     (int a_line, int a_col, int a_beg, int a_xscale, int a_margin, char a_fields, char a_inside [LEN_FULL], int a_rlen, uchar *b_rdata)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_bad       =  '-';
   int         l           =    0;
   int         j           =    0;
   char        x_inside    [LEN_FULL]  = "";
   char        x_cat       [LEN_LABEL] = "";
   char        x_sub       [LEN_LABEL] = "";
   char        x_name      [LEN_LABEL] = "";
   char        t           [LEN_FULL]  = "";
   char        x_header    [LEN_FULL]  = "";
   char       *p           = NULL;
   char       *q           =  " ";
   char       *r           = NULL;
   int         c           =    0;
   int         r_xpos      =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(prepare)---------------------*/
   l = strlen (a_inside);
   ystrlcpy  (x_inside, a_inside, l);
   DEBUG_YGLTEX    yLOG_complex ("x_inside"  , "%3dÂ%sÊ", l, x_inside);
   p = strtok_r (x_inside, q, &r);
   ystrlcpy  (x_cat , p        , LEN_LABEL);
   ystrldchg (x_cat , '∑', ' ' , LEN_LABEL);
   ystrltrim (x_cat , ySTR_BOTH, LEN_LABEL);
   DEBUG_YGLTEX    yLOG_delim   ("x_cat"     , x_cat);
   sprintf (x_header, "HEADER ß %-20.20s ß", x_cat);
   if (a_fields > 1) {
      p = strtok_r (NULL, q, &r);
      ystrlcpy  (x_cat , p        , LEN_LABEL);
      ystrldchg (x_cat , '∑', ' ' , LEN_LABEL);
      ystrltrim (x_cat , ySTR_BOTH, LEN_LABEL);
      DEBUG_YGLTEX    yLOG_delim   ("x_sub"     , x_sub);
      sprintf (t, " %-20.20s ß", x_sub);
      ystrlcat (x_header, t, LEN_FULL);
   }
   if (a_fields > 2) {
      p = strtok_r (NULL, q, &r);
      ystrlcpy  (x_name, p        , LEN_LABEL);
      ystrldchg (x_name, '∑', ' ' , LEN_LABEL);
      ystrltrim (x_name, ySTR_BOTH, LEN_LABEL);
      DEBUG_YGLTEX    yLOG_delim   ("x_name"    , x_name);
      sprintf (t, " %-20.20s ß", x_name);
      ystrlcat (x_header, t, LEN_FULL);
   }
   /*---(save∑values)--------------------*/
   r_xpos    = a_margin + (a_margin * a_col) + (a_xscale * a_col);
   sprintf (b_rdata + (r_xpos * 4), "%s", x_header);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex__header          (char a_pass, int a_line, char a_recd [LEN_HUGE], int x_scale, int a_margin, int a_fields, int x_max, int *r_count, int a_rlen, uchar *b_rdata)
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
   int         c           =    0;
   char        x_bad       =  '-';
   char       *p           = NULL;
   char       *q           =  " ";
   char       *r           = NULL;
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
   --rce;  if (strncmp (a_recd, "HÅ"     , 2) != 0) {
      DEBUG_YGLTEX    yLOG_note    ("not a header record, must start with ∂HÅ∂");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("x_scale"   , x_scale);
   --rce;  if (x_scale < 20 || x_scale > 100) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_fields"  , a_fields);
   --rce;  if (a_fields < 1 || a_fields > 3) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_len = strlen (a_recd);
   x_inc = x_scale + 2;
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
         rc = ygltex__text_hdr_one  (a_line, i + 1, x_beg, a_fields, x_tile, x_inside);
         if (rc < 0)  x_bad = 'y';
      } else if (a_pass == '2') {
         rc = ygltex__png_hdr_one   (a_line, i, x_beg, x_scale, a_margin, a_fields, x_inside, a_rlen, b_rdata);
         if (rc < 0)  x_bad = 'y';
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

char
ygltex__text_dtl_one    (int a_line, int a_col, int x_beg, char a_tile [LEN_FULL], char a_inside [LEN_FULL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_bad       =  '-';
   int         l           =    0;
   int         j           =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(prepare)---------------------*/
   l = strlen (a_tile);
   /*---(check always)----------------*/
   --rce;  if (strchr ("åÅá", a_tile [0]) == NULL) {
      yURG_err ('f', "%4d, tile detail column %d at pos %d does not begin with ∂Å∂ or ∂á∂ or ∂å∂", a_line, a_col, x_beg);
      x_bad = 'y';
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strchr ("åÅÜ", a_tile [l - 1]) == NULL) {
      yURG_err ('f', "%4d, tile detail column %d at pos %d does not end with ∂Å∂ or ∂Ü∂ or ∂å∂", a_line, a_col, x_beg + l - 2);
      x_bad = 'y';
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(characters)---------------------*/
   l = strlen (a_inside);
   --rce;  for (j = 0; j < l; ++j) {
      if (strchr ("@%#*+=-:¥∑≤å ¨", a_inside [j]) == NULL) {
         yURG_err ('f', "%4d, tile detail column %d pos %d char (%c) not legal", a_line, a_col, x_beg + 1 + j, a_inside [j]);
         x_bad = 'y';
         DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex__png_dtl_one     (int a_line, int a_col, int a_beg, int a_xscale, int a_margin, char a_inside [LEN_FULL], int a_rlen, uchar *b_rdata)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   float       x_inc       = 255.0 / 9.0;
   int         i           =    0;
   char        c, d;
   int         l           =    0;
   int         x           =    0;
   int         x_tpos, x_rpos;
   int         r_min, r_max, r_pos;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_complex ("a_args"    , "%4d, %4d, %4d, %4d", a_col, a_beg, a_xscale, a_margin);
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
   DEBUG_YGLTEX    yLOG_value   ("a_beg"     , a_beg);
   --rce;  if (a_beg < 2) {
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
   r_min = a_margin + (a_margin * a_col) + (a_xscale * a_col);
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
      if (c == 0)                                   { c = ' '; d = 0; }
      else if (strchr ("ÉâÇÄÅÑàÖáÜ∑≤", c) != NULL)  { c = ' '; d = 0; }
      else switch (c) {
      case ' ' :  d = 0 * x_inc;  break;
      case '¥' :  d = 1 * x_inc;  break;
      case ':' :  d = 2 * x_inc;  break;
      case '-' :  d = 3 * x_inc;  break;
      case '=' :  d = 4 * x_inc;  break;
      case '+' :  d = 5 * x_inc;  break;
      case '*' :  d = 6 * x_inc;  break;
      case '#' :  d = 7 * x_inc;  break;
      case '%' :  d = 8 * x_inc;  break;
      case '@' :  d = 9 * x_inc;  break;
      default  :  d = 0 * x_inc;  break;
      }
      DEBUG_YGLTEX    yLOG_complex ("loop"      , "%4d, %4d, %c, %c", i, i * 4 + 3, c, d);
      b_rdata [r_pos    ] = 0;
      b_rdata [r_pos + 1] = 0;
      b_rdata [r_pos + 2] = 0;
      b_rdata [r_pos + 3] = d;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex__detail          (char a_pass, int a_line, char a_recd [LEN_HUGE], int x_scale, int a_margin, int x_max, int *r_count, int a_rlen, uchar *b_rdata)
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
   DEBUG_YGLTEX    yLOG_value   ("x_scale"   , x_scale);
   --rce;  if (x_scale < 20 || x_scale > 100) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_len = strlen (a_recd);
   x_inc = x_scale + 2;
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
         rc = ygltex__text_dtl_one  (a_line, i + 1, x_beg, x_tile, x_inside);
         if (rc < 0)  x_bad = 'y';
      } else if (a_pass == '2') {
         rc = ygltex__png_dtl_one   (a_line, i, x_beg + 1, x_scale, a_margin, x_inside, a_rlen, b_rdata);
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

char
ygltex__text_default    (char a_pass, char a_title [LEN_DESC], int *x_scale, int *y_scale, int *a_margin, int *x_count, int *y_count, int *a_fields, int *x_actual, int *y_actual)
{
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_senter  (__FUNCTION__);
   /*---(audit)--------------------------*/
   if (a_pass == '1') {
      yURG_msg ('-', "defaulting globals to initial/unusable values");
      s_ready   = '-';
      strcpy (s_title  , "");
      s_xcount  = 0;
      s_ycount  = 0;
      s_xscale  = 0;
      s_yscale  = 0;
      s_margin  = 0;
      s_fields  = 0;
      s_xactual = 0;
      s_yactual = 0;
      s_wide    = 0;
      s_tall    = 0;
   }
   /*---(creation)-----------------------*/
   else {
      yURG_msg ('-', "accept globals from audit run");
      ystrlcpy (a_title  , s_title, LEN_DESC);
      if (x_scale  != NULL)  *x_scale     = s_xscale;
      if (y_scale  != NULL)  *y_scale     = s_yscale;
      if (a_margin != NULL)  *a_margin    = s_margin;
      if (a_fields != NULL)  *a_fields    = s_fields;
      if (x_count  != NULL)  *x_count     = s_xcount;
      if (y_count  != NULL)  *y_count     = s_ycount;
      if (x_actual != NULL)  *x_actual    = s_xactual;
      if (y_actual != NULL)  *y_actual    = s_yactual;
   }
   DEBUG_YGLTEX    yLOG_snote   ("globals values set");
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ygltex__text_complete   (char a_pass, char a_title [LEN_DESC], int x_scale, int y_scale, int a_margin, int x_count, int y_count, int a_fields, int x_actual, int y_actual)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_bad       =  '-';
   /*---(quick-out)----------------------*/
   DEBUG_YGLTEX    yLOG_senter  (__FUNCTION__);
   /*---(quick-out)----------------------*/
   if (a_pass != '1') {
      DEBUG_YGLTEX    yLOG_snote   ("not pass one");
      DEBUG_YGLTEX    yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(check result)-------------------*/
   yURG_msg ('-', "verifying overall audit quality");
   if (strcmp (a_title, "") == 0)   x_bad = 'y';
   if (x_scale   < 20)              x_bad = 'y';
   if (y_scale   < 20)              x_bad = 'y';
   if (a_margin  <  5)              x_bad = 'y';
   if (x_count   <  1)              x_bad = 'y';
   if (y_count   <  0)              x_bad = 'y';
   if (a_fields  <  1)              x_bad = 'y';
   if (x_actual  <  1)              x_bad = 'y';
   if (y_actual  <  1)              x_bad = 'y';
   --rce;  if (x_bad == 'y') {
      yURG_err ('f', "not all configuration data read");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "all configuration data read");
   /*---(save globals)-------------------*/
   s_ready   = 'y';
   ystrlcpy (s_title  , a_title, LEN_DESC);
   yURG_msg ('-', "title         Â%sÊ", s_title);
   s_xcount  = x_count;
   s_ycount  = y_count;
   yURG_msg ('-', "count         %6dw by %6dt", s_xcount, s_ycount);
   s_xscale  = x_scale;
   s_yscale  = y_scale;
   s_margin  = a_margin;
   yURG_msg ('-', "scale         %6dw by %6dt with %dm", s_xscale, s_yscale, s_margin);
   s_fields  = a_fields;
   yURG_msg ('-', "fields        %d", s_fields);
   s_xactual = x_actual;
   s_yactual = y_actual;
   yURG_msg ('-', "actual        %6dw by %6dt", s_xactual, s_yactual);
   /*---(calculate png size)-------------*/
   s_wide    = s_margin + (s_margin * s_xactual) + (s_xscale * s_xactual);
   s_tall    = s_margin + (s_margin * s_yactual) + (s_yscale * s_yactual);
   DEBUG_YGLTEX    yLOG_complex ("png"       , "%6dw by %6dt", s_wide, s_tall);
   yURG_msg ('-', "biggest       %6dw by %6dt", s_wide, s_tall);
   s_wide    = s_margin + (s_margin * s_xcount ) + (s_xscale * s_xcount );
   if (s_ycount != 0) s_tall    = s_margin + (s_margin * s_ycount ) + (s_yscale * s_ycount );
   yURG_msg ('-', "layout        %6dw by %6dt", s_wide, s_tall);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ygltex_text_driver      (char a_pass, cchar a_name [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   int         x_len       =    0;
   char        x_recd      [LEN_HUGE]  = "";
   char        x_title     [LEN_DESC]  = "";
   char        x_new       =  '-';
   char        x_rows      =    0;
   int         x_scale     =    0;
   int         y_scale     =    0;
   int         x_margin    =    0;
   int         x_fields    =    0;
   int         x_count     =    0;
   int         y_count     =    0;
   int         x_actual    =    0;
   int         y_actual    =    0;
   int         y_tiles     =    0;
   int         n           =    0;
   int         x_line      =    0;
   int         x_header    =    0;
   char        x_bad       =  '-';
   int         r_ypos      =    0;
   int         r_rowbyte   =    0;
   uchar      *r_data      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_complex ("a_args"    , "%c, %s", a_pass, a_name);
   /*---(start)--------------------------*/
   if      (a_pass == '1')  yURG_msg ('>', "conducting txt file audit and data gathering...");
   else if (a_pass == '2')  yURG_msg ('>', "create png file contents...");
   else {
      DEBUG_YGLTEX    yLOG_note    ("unknown pass number");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   ygltex__text_default    (a_pass, x_title, &x_scale, &y_scale, &x_margin, &x_count, &y_count, &x_fields, &x_actual, &y_actual);
   /*---(header)-------------------------*/
   if (a_pass == '2') {
      ygltex__title_write     (x_title, x_actual, y_actual, x_scale, y_scale, x_margin, r_rowbyte, r_data);
   }
   /*---(open∑file)----------------------*/
   yURG_msg ('-', "openning file Â%sÊ", a_name);
   rc = ygltex__text_open (a_name, 'r', &f);
   DEBUG_YGLTEX    yLOG_value   ("fopen"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read∑lines)---------------------*/
   while (1) {
      /*---(read)------------------------*/
      rc = ygltex__text_read (f, &x_line, &x_len, x_recd, &x_new);
      DEBUG_YGLTEX    yLOG_value   ("read"      , rc);
      if (rc == 0) {
         DEBUG_YGLTEX    yLOG_note    ("end of file, no more lines");
         break;
      }
      /*---(handle new tile line)--------*/
      if  (strchr ("Yy", x_new) != NULL) {
         x_header = x_line;
         x_rows   = 0;
      }
      /*---(pass-one handlers only)------*/
      if      (a_pass == '1' && strncmp (x_recd, "#@ tile_title "  , 14) ==0) {
         rc = ygltex__text_title  (x_line, x_recd, x_title);
         if (rc < 0)  yURG_err ('f', "%4d, ygltex__text_title     (%d) failed", x_line, rc);
      }
      else if (a_pass == '1' && strncmp (x_recd, "#@ tile_size "   , 13) ==0) {
         rc = ygltex__text_sizing (x_line, x_recd, &x_scale, &y_scale, &x_margin);
         if (rc < 0)  yURG_err ('f', "%4d, ygltex__text_sizing    (%d) failed", x_line, rc);
      }
      else if (a_pass == '1' && strncmp (x_recd, "#@ tile_layout " , 15) ==0) {
         rc = ygltex__text_layout (x_line, x_recd, &x_count, &y_count);
         if (rc < 0)  yURG_err ('f', "%4d, ygltex__text_layout    (%d) failed", x_line, rc);
      }
      else if (a_pass == '1' && strncmp (x_recd, "#@ tile_fields " , 15) ==0) {
         rc = ygltex__text_fields (x_line, x_recd, &x_fields);
         if (rc < 0)  yURG_err ('f', "%4d, ygltex__text_fields    (%d) failed", x_line, rc);
      }
      /*---(all-pass handlers)-----------*/
      else if (strncmp (x_recd, "BÑÄ"             ,  3) ==0) {
         if (a_pass == '1' && x_rows != y_scale) yURG_err ('f', "%4d to %4d tile height (%d) not requested (%d)", x_header, x_line, x_rows, y_scale);
         ++y_tiles;
      }
      else if (strncmp (x_recd, "HÅ "             ,  3) ==0) {
         r_ypos = s_margin + (s_margin * y_tiles) + (s_yscale * y_tiles);
         if (s_rows == NULL) {
            r_ypos    =    0;
            r_rowbyte =    0;
            r_data    = NULL;
         } else {
            r_ypos    = s_margin + (s_margin * y_tiles) + (s_yscale * y_tiles) - 3;
            r_rowbyte = s_rowbyte;
            r_data    = s_rows [r_ypos];
            if (r_ypos >= s_height) { r_ypos = 0;  r_rowbyte = 0;  r_data == NULL; }
         }
         rc = ygltex__header (a_pass, x_line, x_recd, x_scale, x_margin, x_fields, 99, &n, r_rowbyte, r_data);
         if (a_pass == '1' && rc < 0)  yURG_err ('f', "%4d, ygltex__text_hdr_audit (%d) failed", x_line, rc);
         if (n > x_actual)  x_actual = n;
      }
      else if (x_recd [0] == '¥') {
         DEBUG_YGLTEX    yLOG_complex ("size"      , "%4d %4d", s_wide, s_tall);
         DEBUG_YGLTEX    yLOG_complex ("tex"       , "%4d %4d %4d %p", s_width, s_height, s_rowbyte, s_rows);
         DEBUG_YGLTEX    yLOG_value   ("y_tiles"   , y_tiles);
         DEBUG_YGLTEX    yLOG_value   ("x_rows"    , x_rows);
         if (s_rows == NULL) {
            r_ypos    =    0;
            r_rowbyte =    0;
            r_data    = NULL;
         } else {
            r_ypos    = s_margin + (s_margin * y_tiles) + (s_yscale * y_tiles) + x_rows;
            DEBUG_YGLTEX    yLOG_value   ("r_ypos"    , r_ypos);
            r_rowbyte = s_rowbyte;
            r_data    = s_rows [r_ypos];
            if (r_ypos >= s_height) { r_ypos = 0;  r_rowbyte = 0;  r_data == NULL; }
         }
         DEBUG_YGLTEX    yLOG_complex ("to∑pass"   , "%4d %4d %p", r_ypos, r_rowbyte, r_data);
         rc = ygltex__detail (a_pass, x_line, x_recd, x_scale, x_margin, 99, &n, r_rowbyte, r_data);
         if (a_pass == '1' && rc < 0)  yURG_err ('f', "%4d, ygltex__text_dtl_audit (%d) failed", x_line, rc);
         ++x_rows;
         if (n > x_actual)  x_actual = n;
      }
      /*---(done)------------------------*/
   }
   yURG_msg ('-', "processed %d lines", x_line);
   /*---(close∑file)---------------------*/
   yURG_msg ('-', "closing file");
   rc = ygltex__text_close (&f);
   DEBUG_YGLTEX    yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check results)------------------*/
   ygltex__text_complete   (a_pass, x_title, x_scale, y_scale, x_margin, x_count, y_count, x_fields, x_actual, y_tiles);
   /*> if (strcmp (x_title, "") == 0)   x_bad = 'y';                                  <* 
    *> if (x_scale   < 20)              x_bad = 'y';                                  <* 
    *> if (y_scale   < 20)              x_bad = 'y';                                  <* 
    *> if (x_margin  <  5)              x_bad = 'y';                                  <* 
    *> if (x_count   <  1)              x_bad = 'y';                                  <* 
    *> if (y_count   <  0)              x_bad = 'y';                                  <* 
    *> if (x_fields  <  1)              x_bad = 'y';                                  <* 
    *> if (x_actual  <  1)              x_bad = 'y';                                  <* 
    *> if (y_actual  <  1)              x_bad = 'y';                                  <* 
    *> --rce;  if (x_bad == 'y') {                                                    <* 
    *>    yURG_err ('f', "not all configuration data read");                          <* 
    *>    DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);                           <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> yURG_msg ('-', "all configuration data read");                                 <*/
   /*---(save globals)-------------------*/
   /*> s_ready   = 'y';                                                                       <* 
    *> ystrlcpy (s_title  , x_title, LEN_DESC);                                               <* 
    *> yURG_msg ('-', "title         Â%sÊ", s_title);                                         <* 
    *> s_xcount  = x_count;                                                                   <* 
    *> s_ycount  = y_count;                                                                   <* 
    *> yURG_msg ('-', "count         %6dw by %6dt", s_xcount, s_ycount);                      <* 
    *> s_xscale  = x_scale;                                                                   <* 
    *> s_yscale  = y_scale;                                                                   <* 
    *> s_margin  = x_margin;                                                                  <* 
    *> yURG_msg ('-', "scale         %6dw by %6dt with %dm", s_xscale, s_yscale, s_margin);   <* 
    *> s_fields  = x_fields;                                                                  <* 
    *> yURG_msg ('-', "fields        %d", s_fields);                                          <* 
    *> s_xactual = x_actual;                                                                  <* 
    *> s_yactual = y_actual;                                                                  <* 
    *> yURG_msg ('-', "actual        %6dw by %6dt", s_xactual, s_yactual);                    <*/
   /*---(calculate png size)-------------*/
   /*> s_wide    = s_margin + (s_margin * s_xactual) + (s_xscale * s_xactual);                      <* 
    *> s_tall    = s_margin + (s_margin * s_yactual) + (s_yscale * s_yactual);                      <* 
    *> DEBUG_YGLTEX    yLOG_complex ("png"       , "%6dw by %6dt", s_wide, s_tall);                 <* 
    *> yURG_msg ('-', "biggest       %6dw by %6dt", s_wide, s_tall);                                <* 
    *> s_wide    = s_margin + (s_margin * s_xcount ) + (s_xscale * s_xcount );                      <* 
    *> if (s_ycount != 0) s_tall    = s_margin + (s_margin * s_ycount ) + (s_yscale * s_ycount );   <* 
    *> yURG_msg ('-', "layout        %6dw by %6dt", s_wide, s_tall);                                <*/
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                 detail writing and reading                   ----===*/
/*====================------------------------------------====================*/
static void      o___DETAIL_____________o (void) {;}



/*====================------------------------------------====================*/
/*===----                  writing and reading lines                  ----===*/
/*====================------------------------------------====================*/
static void      o___OLDER______________o (void) {;}


char
ygltex__png_detail_one  (char a_recd [LEN_HUGE], int x, int w, int r_max, uchar *r_row)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_min, x_max;
   float       x_inc       = 255.0 / 9.0;
   int         i           =    0;
   char        c, d;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("r_row"     , r_row);
   --rce;  if (r_row  == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("x"         , x);
   --rce;  if (x < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("w"         , w);
   --rce;  if (w < 1) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_len = strlen (a_recd);
   x_min = x;
   x_max = x + w - 1;
   DEBUG_YGLTEX    yLOG_complex ("bounds"    , "%4d, %4d, %4d", x_min, x_max, r_max);
   --rce;  if (x_max >= x_len) {
      DEBUG_YGLTEX    yLOG_note    ("request reads outside a_recd boundaries");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_max * 4 >= r_max) {
      DEBUG_YGLTEX    yLOG_note    ("request writes outside r_row boundaries");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear)--------------------------*/
   for (i = x_min; i <= x_max; ++i) {
      r_row [i * 4    ] = 0;
      r_row [i * 4 + 1] = 0;
      r_row [i * 4 + 2] = 0;
      r_row [i * 4 + 3] = 0;
   }
   /*---(write one line)-----------------*/
   --rce;  for (i = x_min; i <= x_max; ++i) {
      c = a_recd [i];
      if (c == 0)                                   { c = ' '; d = 0; }
      else if (strchr ("ÉâÇÄÅÑàÖáÜ∑≤", c) != NULL)  { c = ' '; d = 0; }
      else switch (c) {
      case ' ' :  d = 0 * x_inc;  break;
      case '¥' :  d = 1 * x_inc;  break;
      case ':' :  d = 2 * x_inc;  break;
      case '-' :  d = 3 * x_inc;  break;
      case '=' :  d = 4 * x_inc;  break;
      case '+' :  d = 5 * x_inc;  break;
      case '*' :  d = 6 * x_inc;  break;
      case '#' :  d = 7 * x_inc;  break;
      case '%' :  d = 8 * x_inc;  break;
      case '@' :  d = 9 * x_inc;  break;
      case '¨' :  d = 0 * x_inc;  break;
      default  :
                  DEBUG_YGLTEX    yLOG_complex ("badchar"   , "%c/%3d in pos %d is illegal ( ¥:-=+*#%@)", c, c, i);
                  DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
                  return rce;
      }
      DEBUG_YGLTEX    yLOG_complex ("loop"      , "%4d, %4d, %c, %c", i, i * 4 + 3, c, d);
      r_row [i * 4 + 3] = d;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yGLTEX__write_full_line (int a_len, char a_recd [LEN_HUGE], int r_max, uchar *r_row)
{
}


char
yGLTEX_edit__trans_OLD  (char a_name [LEN_HUND], int x_beg, int y_beg, int x_scale, int y_scale, int x_cnt, int y_cnt)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   uchar       c, d;
   int         x           =    0;
   int         y           =    0;
   int         i           =    0;
   char        x_recd      [LEN_HUGE]  = "";
   char        t           [LEN_HUND]  = "";
   int         x_len       =    0;
   int         i_min, i_max, i_scale;
   int         y_min, y_max, x_min, x_max;
   float       x_inc       = 255.0 / 9.0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(open∑file)----------------------*/
   rc = ygltex__text_open (a_name, 'r', &f);
   DEBUG_YGLTEX    yLOG_value   ("fopen"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   y_min       = y_scale * y_beg;
   y_max       = y_min + (y_scale * y_cnt);
   x_min       = x_scale * x_beg + 1;
   x_max       = x_min + (x_scale * x_cnt);
   i_scale     = y_scale + 2;
   i_min       = 0;
   i_max       = i_scale * (y_beg + y_cnt);
   DEBUG_YGLTEX    yLOG_complex ("bounds"    , "%4di to %4di, %4dx to %4dx, %4dy to %4dy", i_min, i_max, x_min, x_max, y_min, y_max);
   /*---(read∑lines)---------------------*/
   for (i = i_min; i < y_max; ++i) {
      /*---(read)------------------------*/
      DEBUG_YGLTEX    yLOG_value   ("i"         , i);
      rc = ygltex__text_read (f, NULL, &x_len, x_recd, NULL);
      DEBUG_YGLTEX    yLOG_value   ("read"      , rc);
      if (rc == 0) {
         DEBUG_YGLTEX    yLOG_note    ("end of file, no more lines");
         break;
      }
      /*> fgets (x_recd, LEN_HUGE, f);                                                <* 
       *> if (feof (f))  {                                                            <* 
       *>    DEBUG_YGLTEX    yLOG_note    ("end of file reached");                    <* 
       *>    break;                                                                   <* 
       *> }                                                                           <* 
       *> x_len = strlen (x_recd);                                                    <* 
       *> if (x_recd [x_len - 1] == '\n')  x_recd [--x_len] = '\0';                   <* 
       *> ystrlcpy (t, x_recd, LEN_HUND);                                             <* 
       *> DEBUG_YGLTEX    yLOG_info    ("t"         , t);                             <* 
       *> if (x_len < 60) {                                                           <* 
       *>    DEBUG_YGLTEX    yLOG_note    ("too short, skip");                        <* 
       *>    continue;                                                                <* 
       *> }                                                                           <*/
      /*---(filter)----------------------*/
      /*> if (i % i_scale <= 1) {                                                     <* 
       *>    DEBUG_YGLTEX    yLOG_note    ("header rows");                            <* 
       *>    continue;                                                                <* 
       *> }                                                                           <*/
      /*> if (y < y_min) {                                                            <* 
       *>    DEBUG_YGLTEX    yLOG_note    ("not yet reached vertical start");         <* 
       *>    continue;                                                                <* 
       *> }                                                                           <*/
      /*> c = x_recd [0];                                                             <* 
       *> DEBUG_YGLTEX    yLOG_char    ("c"         , c);                             <* 
       *> if (c != (uchar) '¥') {                                                     <* 
       *>    DEBUG_YGLTEX    yLOG_note    ("not a detail line, skipping");            <* 
       *>    continue;                                                                <* 
       *> }                                                                           <*/
      /*---(cleanse)---------------------*/
      for (x = x_min; x < x_max; ++x) {
         if (x > x_len)  break;
         c = x_recd [x];
         if (c == 0)                                   { c = ' '; d = 0; }
         else if (strchr ("ÉâÇÄÅÑàÖáÜ∑≤", c) != NULL)  { c = ' '; d = 0; }
         else switch (c) {
         case ' ' :  d = 0 * x_inc;  break;
         case '¥' :  d = 1 * x_inc;  c = '.';  break;
         case ':' :  d = 2 * x_inc;  break;
         case '-' :  d = 3 * x_inc;  break;
         case '=' :  d = 4 * x_inc;  break;
         case '+' :  d = 5 * x_inc;  break;
         case '*' :  d = 6 * x_inc;  break;
         case '#' :  d = 7 * x_inc;  break;
         case '%' :  d = 8 * x_inc;  break;
         case '@' :  d = 9 * x_inc;  break;
         case '¨' :  d = 0 * x_inc;  break;
         default  :  d = 9 * x_inc;  break;
         }
         s_rows [y][(x - x_min) * 4    ] = 0;
         s_rows [y][(x - x_min) * 4 + 1] = 0;
         s_rows [y][(x - x_min) * 4 + 2] = 0;
         s_rows [y][(x - x_min) * 4 + 3] = d;
         /*> printf ("%c/%3d ", c, d);                                                <*/
         printf ("%c", c);
      }
      printf ("\n");
      ++y;
   }
   /*---(close∑file)---------------------*/
   rc = ygltex__text_close (&f);
   DEBUG_YGLTEX    yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yGLTEX_edit__trans      (char a_name [LEN_HUND], int x_beg, int y_beg, int x_scale, int y_scale, int x_cnt, int y_cnt)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   uchar       c, d;
   int         x           =    0;
   int         y           =    0;
   int         i           =    0;
   char        x_recd      [LEN_HUGE]  = "";
   char        t           [LEN_HUND]  = "";
   int         x_len       =    0;
   int         i_min, i_max, i_scale;
   int         y_min, y_max, x_min, x_max;
   float       x_inc       = 255.0 / 9.0;
   char        x_row       =   -1;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(open∑file)----------------------*/
   rc = ygltex__text_open (a_name, 'r', &f);
   DEBUG_YGLTEX    yLOG_value   ("fopen"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   y_min       = y_scale * y_beg;
   y_max       = y_min + (y_scale * y_cnt);
   x_min       = x_scale * x_beg + 1;
   x_max       = x_min + (x_scale * x_cnt);
   i_scale     = y_scale + 2;
   i_min       = 0;
   i_max       = i_scale * (y_beg + y_cnt);
   DEBUG_YGLTEX    yLOG_complex ("bounds"    , "%4di to %4di, %4dx to %4dx, %4dy to %4dy", i_min, i_max, x_min, x_max, y_min, y_max);
   /*---(read∑lines)---------------------*/
   while (1) {
      /*---(read)------------------------*/
      rc = ygltex__text_read (f, NULL, &x_len, x_recd, &x_row);
      DEBUG_YGLTEX    yLOG_value   ("read"      , rc);
      if (rc == 0) {
         DEBUG_YGLTEX    yLOG_note    ("end of file, no more lines");
         break;
      }
      DEBUG_YGLTEX    yLOG_complex ("rows"      , "%3db, %3dc, %3dc", y_beg, y_cnt, x_row);
      if (x_row >= y_beg + y_cnt) {
         DEBUG_YGLTEX    yLOG_note    ("passed last row allowed");
         break;
      }
      if (x_row < y_beg) {
         DEBUG_YGLTEX    yLOG_note    ("not yet reached requested row");
         continue;
      }
      /*---(cleanse)---------------------*/
      for (x = x_min; x < x_max; ++x) {
         if (x > x_len)  break;
         c = x_recd [x];
         if (c == 0)                                   { c = ' '; d = 0; }
         else if (strchr ("ÉâÇÄÅÑàÖáÜ∑≤", c) != NULL)  { c = ' '; d = 0; }
         else switch (c) {
         case ' ' :  d = 0 * x_inc;  break;
         case '¥' :  d = 1 * x_inc;  c = '.';  break;
         case ':' :  d = 2 * x_inc;  break;
         case '-' :  d = 3 * x_inc;  break;
         case '=' :  d = 4 * x_inc;  break;
         case '+' :  d = 5 * x_inc;  break;
         case '*' :  d = 6 * x_inc;  break;
         case '#' :  d = 7 * x_inc;  break;
         case '%' :  d = 8 * x_inc;  break;
         case '@' :  d = 9 * x_inc;  break;
         case '¨' :  d = 0 * x_inc;  break;
         default  :  d = 9 * x_inc;  break;
         }
         s_rows [y][(x - x_min) * 4    ] = 0;
         s_rows [y][(x - x_min) * 4 + 1] = 0;
         s_rows [y][(x - x_min) * 4 + 2] = 0;
         s_rows [y][(x - x_min) * 4 + 3] = d;
         /*> printf ("%c/%3d ", c, d);                                                <*/
         printf ("%c", c);
      }
      printf ("\n");
      ++y;
   }
   /*---(close∑file)---------------------*/
   rc = ygltex__text_close (&f);
   DEBUG_YGLTEX    yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                              <* 
 *> yGLTEX_edit__row        (int a_len, char a_recd [LEN_HUGE], y, x, w)              <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    char        rc          =    0;                                                <* 
 *> }                                                                                 <*/

char
yGLTEX_edit__trans_NEW  (char a_name [LEN_HUND], int x_beg, int y_beg, int x_scale, int y_scale, int x_cnt, int y_cnt)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   uchar       c, d;
   int         x           =    0;
   int         y           =    0;
   int         i           =    0;
   char        x_recd      [LEN_HUGE]  = "";
   char        t           [LEN_HUND]  = "";
   int         x_len       =    0;
   int         i_min, i_max, i_scale;
   int         y_min, y_max, x_min, x_max;
   float       x_inc       = 255.0 / 9.0;
   char        x_row       =   -1;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(open∑file)----------------------*/
   rc = ygltex__text_open (a_name, 'r', &f);
   DEBUG_YGLTEX    yLOG_value   ("fopen"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   y_min       = y_scale * y_beg;
   y_max       = y_min + (y_scale * y_cnt);
   x_min       = x_scale * x_beg + 1;
   x_max       = x_min + (x_scale * x_cnt);
   i_scale     = y_scale + 2;
   i_min       = 0;
   i_max       = i_scale * (y_beg + y_cnt);
   DEBUG_YGLTEX    yLOG_complex ("bounds"    , "%4di to %4di, %4dx to %4dx, %4dy to %4dy", i_min, i_max, x_min, x_max, y_min, y_max);
   /*---(read∑lines)---------------------*/
   while (1) {
      /*---(read)------------------------*/
      rc = ygltex__text_read (f, NULL, &x_len, x_recd, &x_row);
      DEBUG_YGLTEX    yLOG_value   ("read"      , rc);
      if (rc == 0) {
         DEBUG_YGLTEX    yLOG_note    ("end of file, no more lines");
         break;
      }
      DEBUG_YGLTEX    yLOG_complex ("rows"      , "%3db, %3dc, %3dc", y_beg, y_cnt, x_row);
      if (x_row >= y_beg + y_cnt) {
         DEBUG_YGLTEX    yLOG_note    ("passed last row allowed");
         break;
      }
      if (x_row < y_beg) {
         DEBUG_YGLTEX    yLOG_note    ("not yet reached requested row");
         continue;
      }
      /*---(cleanse)---------------------*/
      for (x = x_min; x < x_max; ++x) {
         if (x > x_len)  break;
         c = x_recd [x];
         if (c == 0)                                   { c = ' '; d = 0; }
         else if (strchr ("ÉâÇÄÅÑàÖáÜ∑≤", c) != NULL)  { c = ' '; d = 0; }
         else switch (c) {
         case ' ' :  d = 0 * x_inc;  break;
         case '¥' :  d = 1 * x_inc;  c = '.';  break;
         case ':' :  d = 2 * x_inc;  break;
         case '-' :  d = 3 * x_inc;  break;
         case '=' :  d = 4 * x_inc;  break;
         case '+' :  d = 5 * x_inc;  break;
         case '*' :  d = 6 * x_inc;  break;
         case '#' :  d = 7 * x_inc;  break;
         case '%' :  d = 8 * x_inc;  break;
         case '@' :  d = 9 * x_inc;  break;
         case '¨' :  d = 0 * x_inc;  break;
         default  :  d = 9 * x_inc;  break;
         }
         s_rows [y][(x - x_min) * 4    ] = 0;
         s_rows [y][(x - x_min) * 4 + 1] = 0;
         s_rows [y][(x - x_min) * 4 + 2] = 0;
         s_rows [y][(x - x_min) * 4 + 3] = d;
         /*> printf ("%c/%3d ", c, d);                                                <*/
         printf ("%c", c);
      }
      printf ("\n");
      ++y;
   }
   /*---(close∑file)---------------------*/
   rc = ygltex__text_close (&f);
   DEBUG_YGLTEX    yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yGLTEX_txt2png          (char a_mode, cchar a_name [LEN_HUND], cchar a_dest [LEN_HUND])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;             /* simple return code             */
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(conduct audit)------------------*/
   if (a_mode == 'a') {
      yURG_msg_live ();
      yURG_err_live ();
   }
   rc = ygltex_text_driver ('1', a_name);
   --rce;  if (rc < 0) {
      yURG_err ('F', "text file failed audit, use --audit to see details");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_mode == 'a') {
      yURG_msg ('C', "SUCCESS, txt file passed all audits");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prepare png)--------------------*/
   if (rc == 0) {
      rc = yGLTEX__file_open    (a_dest, 'w');
      DEBUG_YGLTEX    yLOG_value   ("png open"  , rc);
   }
   if (rc == 0) {
      rc = yGLTEX__save_header  ();
      DEBUG_YGLTEX    yLOG_value   ("png header", rc);
   }
   if (rc == 0) {
      rc = yGLTEX__save_attrib  (s_wide, s_tall);
      DEBUG_YGLTEX    yLOG_value   ("png attrib", rc);
   }
   if (rc == 0) {
      rc = yGLTEX__file_alloc   ();
      DEBUG_YGLTEX    yLOG_value   ("png alloc" , rc);
   }
   --rce;  if (rc < 0) {
      yGLTEX__file_close    ();
      DEBUG_YGLTEX    yLOG_value   ("close"     , rc);
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update png)---------------------*/
   rc = ygltex_text_driver ('2', a_name);
   /*> rc = yGLTEX_edit__trans   (a_name,  0, 0, 60, 60, 22, 12);                     <*/
   DEBUG_YGLTEX    yLOG_value   ("png update", rc);
   /*---(save png)-----------------------*/
   if (rc == 0) {
      rc = yGLTEX__save_image   ('c');
      DEBUG_YGLTEX    yLOG_value   ("png save"  , rc);
   }
   /*---(close png)----------------------*/
   yGLTEX__file_close    ();
   DEBUG_YGLTEX    yLOG_value   ("close"     , rc);
   if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yGLTEX_txt2png_OLD      (char a_mode, cchar a_name [LEN_HUND], cchar a_dest [LEN_HUND], cint a_width, cint a_height, cint a_beg)
{
}



/*====================------------------------------------====================*/
/*===----                       making text                            ----===*/
/*====================------------------------------------====================*/
static void      o___PNG2TXT____________o (void) {;}

char
yGLTEX_edit_icon     (int x_beg, int y_beg, int x_scale, int y_scale, int x_cnt, int y_cnt)
{
   /*---(locals)-----------+-----------+-*/
   int         y, x, i;
   png_bytep  *x_cur       = s_rows [0];
   uchar       c           =  '∑';
   uchar       d           =  '∑';
   int         y_min       = y_scale * y_beg;
   int         y_max       = y_min + (y_scale * y_cnt);
   int         x_min       = x_scale * x_beg;
   int         x_max       = x_min + (x_scale * x_cnt);
   for (y = y_min; y < y_max; ++y) {
      /*---(toprow)----------------------*/
      if (y % y_scale == 0) {
         for (i = 0; i < x_cnt; ++i) printf ("ÉÄÄÄÄÄÄâÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄââÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄâÄÄÄÄÄÄÇ");
         printf ("\n");
         continue;
      }
      if (y % y_scale == y_scale - 1) {
         for (i = 0; i < x_cnt; ++i) printf ("ÑÄÄÄÄÄÄàÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄààÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄàÄÄÄÄÄÄÖ");
         printf ("\n");
         continue;
      }
      /*---(toprow)----------------------*/
      for (x = x_min; x < x_max * 4; x += 4) {
         /*> printf ("%3d %3d %3d %3d   ", s_rows [y][x], s_rows [y][x + 1], s_rows [y][x + 2], s_rows [y][x + 3]);   <*/
         if (x % (x_scale * 4) == 0) {
            if      (y % y_scale ==  6)  printf ("á");
            else if (y % y_scale == 29)  printf ("á");
            else if (y % y_scale == 30)  printf ("á");
            else if (y % y_scale == 53)  printf ("á");
            else                         printf ("Å");
            continue;
         }
         if ((x % (x_scale * 4)) / 4 == x_scale - 1) {
            if      (y % y_scale ==  6)  printf ("Ü");
            else if (y % y_scale == 29)  printf ("Ü");
            else if (y % y_scale == 30)  printf ("Ü");
            else if (y % y_scale == 53)  printf ("Ü");
            else                         printf ("Å");
            continue;
         }
         c = s_rows [y][x + 3];
         c /= (256.0 / 10.0);
         switch (c) {
         case 0 :  d = ' ';  break;
         case 1 :  d = '¥';  break;
         case 2 :  d = ':';  break;
         case 3 :  d = '-';  break;
         case 4 :  d = '=';  break;
         case 5 :  d = '+';  break;
         case 6 :  d = '*';  break;
         case 7 :  d = '#';  break;
         case 8 :  d = '%';  break;
         case 9 :  d = '@';  break;
         default:  d = '∞';  break;
         }
         if (d == ' ') {
            if      ((x % (x_scale * 4) / 4) == 7 )  d = '∑';
            else if ((x % (x_scale * 4) / 4) == 29)  d = '∑';
            else if ((x % (x_scale * 4) / 4) == 30)  d = '∑';
            else if ((x % (x_scale * 4) / 4) == 52)  d = '∑';
            else if (y % y_scale ==  6)      d = '∑';
            else if (y % y_scale == 29)      d = '∑';
            else if (y % y_scale == 30)      d = '∑';
            else if (y % y_scale == 53)      d = '∑';
         }
         printf ("%c", d);
      }
      printf ("\n");
   }
   return 0;
}

char
yGLTEX_png2txt          (cchar a_name [LEN_HUND])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;             /* simple return code             */
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(open png file)------------------*/
   if (rc == 0)  rc = yGLTEX__file_open    (a_name, 'r');
   if (rc == 0)  rc = yGLTEX__read_header  ();
   if (rc == 0)  rc = yGLTEX__read_attrib  ();
   if (rc == 0)  rc = yGLTEX__file_alloc   ();
   if (rc == 0)  rc = yGLTEX__read_image   ();
   /*> if (rc == 0)  rc = yGLTEX__read_tex     ();                                    <*/
   yGLTEX_edit_icon      (  0,  0, 60, 60, 45, 21);
   yGLTEX__file_close    ();
   DEBUG_YGLTEX    yLOG_value   ("rc"        , rc);
   if (rc < 0) return rc;
   DEBUG_YGLTEX    yLOG_value   ("s_tex"     , s_tex);

   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     unit testing                             ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST___________o (void) {;}

char*
ygltex__unit_show       (int a_max, uchar a_row [LEN_RECD])
{
   uchar       c, d;
   float       x_inc       = 256.0 / 10.0;
   int         x           =    0;
   for (x = 0; x < LEN_RECD; ++x)  s_print [x] = '\0';
   for (x = 0; x < a_max; ++x) {
      c = a_row [x * 4 + 3] / x_inc;
      switch (c) {
      case 0 :  d = ' ';  break;
      case 1 :  d = '¥';  break;
      case 2 :  d = ':';  break;
      case 3 :  d = '-';  break;
      case 4 :  d = '=';  break;
      case 5 :  d = '+';  break;
      case 6 :  d = '*';  break;
      case 7 :  d = '#';  break;
      case 8 :  d = '%';  break;
      case 9 :  d = '@';  break;
      default:  d = '∞';  break;
      }
      if (a_row [x * 4 + 0] != 0)  d = '∞';
      if (a_row [x * 4 + 1] != 0)  d = '∞';
      if (a_row [x * 4 + 2] != 0)  d = '∞';
      if (d == ' ')  d = '∑';
      s_print [x] = d;
   }
   return s_print;
}


