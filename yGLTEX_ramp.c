/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"



char  *zYGLTEX_allow   = "°¬²";
char  *zYGLTEX_minimal = " ΄:-=+*#%@";
char  *zYGLTEX_shrike  = " ·-α~΄+=β¤ρμGνÿ@B#―";      /*  0 to 21 pixels (range of 22) lit of 60 available (6x10 font) */



/*====================------------------------------------====================*/
/*===----                      ascii-art ramping                       ----===*/
/*====================------------------------------------====================*/
static void      o___RAMP_______________o (void) {;}

uchar
ygltex_ramp_alpha2char  (char a_ramp, uchar v, uchar *c)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *x_valid     = NULL;
   char        l           =    0;
   char        i           =    0;
   uchar       n, d;
   float       x_inc       =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (c != NULL)  *c = '°';
   /*---(handle type)--------------------*/
   DEBUG_YGLTEX    yLOG_char    ("a_ramp"    , a_ramp);
   --rce;  switch (a_ramp) {
   case 's' :
      DEBUG_YGLTEX    yLOG_note    ("set as shrike-specific (20)");
      x_valid = zYGLTEX_shrike;
      break;
   case '-' :
      DEBUG_YGLTEX    yLOG_note    ("set as minimal (10)");
      x_valid = zYGLTEX_minimal;
      break;
   default  :
      DEBUG_YGLTEX    yLOG_note    ("type not recognized");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return '°';
   }
   DEBUG_YGLTEX    yLOG_info    ("x_valid"   , x_valid);
   l = strlen (x_valid);
   DEBUG_YGLTEX    yLOG_value   ("l"         , l);
   x_inc = 256.0 / l;
   DEBUG_YGLTEX    yLOG_double  ("x_inc"     , x_inc);
   DEBUG_YGLTEX    yLOG_value   ("v"         , v);
   n  = v / x_inc;
   DEBUG_YGLTEX    yLOG_value   ("n"         , n);
   d  = x_valid [n];
   DEBUG_YGLTEX    yLOG_char    ("d"         , d);
   /*---(save-back)----------------------*/
   if (c != NULL)  *c = d;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return d;
}

uchar
ygltex_ramp_char2alpha  (char a_ramp, uchar c, uchar *a)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *x_valid     = NULL;
   char        l           =    0;
   char        i           =    0;
   char       *p           = NULL;
   uchar       n, d;
   float       x_inc       =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (a != NULL)  *a = 0;
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("c"         , c);
   --rce;  if (c < 32 || c == 127) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return '°';
   }
   DEBUG_YGLTEX    yLOG_char    ("c"         , c);
   /*---(quick-out)----------------------*/
   if (strchr (zYGLTEX_allow, c) != NULL) {
      DEBUG_YGLTEX    yLOG_note    ("filler characters, alpha is zero");
      d = 0;
      if (a != NULL)  *a = d;
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return d;
   }
   if (a_ramp == '-' && c == (uchar) '·') {
      DEBUG_YGLTEX    yLOG_note    ("special minimal filler, alpha is zero");
      d = 0;
      if (a != NULL)  *a = d;
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return d;
   }
   /*---(handle type)--------------------*/
   DEBUG_YGLTEX    yLOG_char    ("a_ramp"    , a_ramp);
   --rce;  switch (a_ramp) {
   case 's' :
      DEBUG_YGLTEX    yLOG_note    ("set as shrike-specific (20)");
      x_valid = zYGLTEX_shrike;
      break;
   case '-' :
      DEBUG_YGLTEX    yLOG_note    ("set as minimal (10)");
      x_valid = zYGLTEX_minimal;
      break;
   default  :
      DEBUG_YGLTEX    yLOG_note    ("type not recognized");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return '°';
   }
   DEBUG_YGLTEX    yLOG_info    ("x_valid"   , x_valid);
   l = strlen (x_valid);
   DEBUG_YGLTEX    yLOG_value   ("l"         , l);
   x_inc = 255.0 / (l - 1);
   DEBUG_YGLTEX    yLOG_double  ("x_inc"     , x_inc);
   p = strchr (x_valid, c);
   DEBUG_YGLTEX    yLOG_point   ("p"         , p);
   --rce;  if (p == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return '°';
   }
   n = p - x_valid;
   DEBUG_YGLTEX    yLOG_value   ("n"         , n);
   d = n * x_inc;
   DEBUG_YGLTEX    yLOG_value   ("d"         , d);
   /*---(save-back)----------------------*/
   if (a != NULL)  *a = d;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return d;
}

char
ygltex_ramp_audit       (int a_line, int a_col, int x_beg, char a_ramp, char a_inside [LEN_FULL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *x_valid     = NULL;
   int         l           =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_inside"  , a_inside);
   --rce;  if (a_inside == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_info    ("a_inside"  , a_inside);
   /*---(handle type)--------------------*/
   DEBUG_YGLTEX    yLOG_char    ("a_ramp"    , a_ramp);
   --rce;  switch (a_ramp) {
   case 's' :
      DEBUG_YGLTEX    yLOG_note    ("set as shrike-specific (20)");
      x_valid = zYGLTEX_shrike;
      break;
   case '-' :
      DEBUG_YGLTEX    yLOG_note    ("set as minimal (10)");
      x_valid = zYGLTEX_minimal;
      break;
   default  :
      DEBUG_YGLTEX    yLOG_note    ("ramp not recognized");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_info    ("x_valid"   , x_valid);
   /*---(validate)-----------------------*/
   l = strlen (a_inside);
   DEBUG_YGLTEX    yLOG_value   ("l"         , l);
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (zYGLTEX_allow, a_inside [i]) != NULL)   continue;
      if (strchr (x_valid, a_inside [i]) == NULL) {
         yURG_err ('f', "%4d, tile detail, column %d at pos %d (%c) not legal (%s) or ignored (%s)", a_line, a_col, x_beg + i, a_inside [i], x_valid, zYGLTEX_allow);
         DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}


