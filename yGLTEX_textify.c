/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"




static char   zYGLTEX_topp  [LEN_HUGE]  = "";
static char   zYGLTEX_head  [LEN_HUGE]  = "";
static char   zYGLTEX_sepp  [LEN_HUGE]  = "";
static char   zYGLTEX_bott  [LEN_HUGE]  = "";

static char   zYGLTEX_print [LEN_HUGE]  = "";

/*>                                                                                   <* 
 *> #@ tile_title     vikeys·ribbon·icons                                             <* 
 *> #@ tile_size      60 60 5                                                         <* 
 *> #@ tile_layout    25 ??                                                           <* 
 *> #@ tile_fields    3                                                               <* 
 *>                                                                                   <*/



/*====================------------------------------------====================*/
/*===----                     detailed functions                      ----===*/
/*====================------------------------------------====================*/
static void      o___DETAIL_____________o (void) {;}

char
ygltex_textify_prefix   (FILE *f, char a_pngname [LEN_PATH], char a_style, int a_wide, int a_tall, int a_xscale, int a_xmargin, int a_yscale, int a_ymargin)
{
   char        t           [LEN_HUND]   = "RAMP UNKNOWN";
   switch (a_style) {
   case 's' : sprintf (t, "shrike-font²20-step²ramp²å%sæ", zYGLTEX_shrike);   break;
   case '-' : sprintf (t, "minimal²10-step²ramp²å%sæ"    , zYGLTEX_minimal);  break;
   }
   fprintf (f, "#!/usr/local/bin/asciiart --import\n");
   fprintf (f, "##   yGLTEX library (%s) yGLTEX_png2ascii\n", P_VERNUM);
   fprintf (f, "##   settings  %4dxs, %4dxm, %4dys, %4dym\n", a_xscale, a_xmargin, a_yscale, a_ymargin);
   fprintf (f, "\n\n");
   fprintf (f, "#@ tile_source    %s (%dw by %dt)\n", a_pngname, a_wide, a_tall);
   fprintf (f, "#@ tile_ramp      %c   %s\n", a_style, t);
   fprintf (f, "#@ tile_title     [title here]\n");
   fprintf (f, "#@ tile_size      %-3d %-3d 5\n", a_xscale, a_yscale);
   fprintf (f, "#@ tile_layout    99  ??\n");
   fprintf (f, "#@ tile_fields    1\n");
   fprintf (f, "\n\n");
   return 0;
}

char
ygltex_textify_prepare  (int a_wide, int a_xscale, int a_xmargin)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        c           =    0;
   char        i           =    0;
   char        t           [LEN_FULL]  = "";
   float       x_cen       =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_complex ("a_args"    , "%4dw, %3ds, %3db", a_wide, a_xscale, a_xmargin);
   /*---(prepare)------------------------*/
   c = a_wide / a_xscale;
   DEBUG_YGLTEX    yLOG_value   ("c"         , c);
   x_cen = ((a_xscale - 1) / 2.0) + 1;
   DEBUG_YGLTEX    yLOG_double  ("x_cen"     , x_cen);
   /*---(top)----------------------------*/
   strcpy (zYGLTEX_topp, "°");
   for (i = 0; i < c; ++i) {
      sprintf (t, "ƒ%*.*s‚", a_xscale, a_xscale, YSTR_HORZ);
      strcat (zYGLTEX_topp, t);
   }
   /*---(header)-------------------------*/
   strcpy (zYGLTEX_head, "H");
   for (i = 0; i < c; ++i) {
      sprintf (t, " %*.*s ", a_xscale - 2, a_xscale - 2, YSTR_EDOTS);
      strcat (zYGLTEX_head, t);
   }
   /*---(separator)----------------------*/
   strcpy (zYGLTEX_sepp, "T");
   for (i = 0; i < c; ++i) {
      sprintf (t, "‡%*.*s†", a_xscale, a_xscale, YSTR_HORZ);
      if      (a_xmargin > 0 && a_xmargin < 10)  t [a_xmargin] = t [a_xscale + 1 - a_xmargin] = '‰';
      t [(int) floor (x_cen)] = t [(int) ceil  (x_cen)] = '‰';
      strcat (zYGLTEX_sepp, t);
   }
   /*---(bottom)-------------------------*/
   strcpy (zYGLTEX_bott, "B");
   for (i = 0; i < c; ++i) {
      sprintf (t, "„%*.*s…", a_xscale, a_xscale, YSTR_HORZ);
      if (a_xmargin > 0 && a_xmargin < 10)  t [a_xmargin] = t [a_xscale + 1 - a_xmargin] = 'ˆ';
      t [(int) floor (x_cen)] = t [(int) ceil  (x_cen)] = 'ˆ';
      strcat (zYGLTEX_bott, t);
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char*
ygltex_textify_print    (FILE *f, char a_which)
{
   if (f != NULL) {
      switch (a_which) {
      case '°' :  fprintf (f, "%s\n", zYGLTEX_topp);   break;
      case 'H' :  fprintf (f, "%s\n", zYGLTEX_head);   break;
      case 'T' :  fprintf (f, "%s\n", zYGLTEX_sepp);   break;
      case 'B' :  fprintf (f, "%s\n", zYGLTEX_bott);   break;
      case '´' :  fprintf (f, "%s\n", zYGLTEX_print);  break;
      }
   }
   switch (a_which) {
   case '°' :  return zYGLTEX_topp;   break;
   case 'H' :  return zYGLTEX_head;   break;
   case 'T' :  return zYGLTEX_sepp;   break;
   case 'B' :  return zYGLTEX_bott;   break;
   case '´' :  return zYGLTEX_print;  break;
   }
   return "unknown";
}

char
ygltex_textify_single   (FILE *f, int a_line, char a_style, int a_left, int a_xscale, int a_xmargin, int a_yscale, int a_ymargin, int a_rbyte, png_bytep a_row)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_max       =    0;
   int         i           =    0;
   uchar       c           =  ' ';
   uchar       d           =  ' ';
   char        t           [LEN_TERSE] = "";
   char        y_on        =  '-';
   char        y_rel       =    0;
   char        x_rel       =    0;
   float       y_mid       =    0;
   float       x_cen       =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_complex ("a_args"    , "%4dl, %3dxs, %5drb", a_left, a_xscale, a_rbyte);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_row"     , a_row);
   --rce;  if (a_row    == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   x_max = a_left + a_xscale - 1;
   DEBUG_YGLTEX    yLOG_point   ("x_max"     , x_max);
   --rce;  if (a_rbyte  <= x_max) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   y_rel = a_line % a_yscale;
   y_mid = (a_yscale - 1) / 2.0;
   x_cen = (a_xscale - 1) / 2.0;
   if      (a_ymargin > 0 && y_rel == a_ymargin)                y_on = 'y';
   else if (a_ymargin > 0 && y_rel == a_yscale - 1 - a_ymargin) y_on = 'y';
   else if (fabs (y_rel - y_mid) < 1.0)        y_on = 'y';
   else                                        y_on = '-';
   /*---(interpret)----------------------*/
   if (a_left == 0)  strcpy (zYGLTEX_print, "´");
   if (y_on == 'y')  strcat (zYGLTEX_print, "‡");
   else              strcat (zYGLTEX_print, "");
   for (i = a_left; i <= x_max; ++i) {
      c = ygltex_ramp_alpha2char (a_style, a_row [(i * 4) + 3], NULL);
      if (y_on == 'y' && c == ' ')  c = '²';
      if (strchr (" ²", c) != NULL) {
         d = c;
         x_rel = i - a_left;
         if      (a_xmargin > 0 && x_rel == a_xmargin - 1)           c = 'Œ';
         else if (a_xmargin > 0 && x_rel == a_xscale - a_xmargin)    c = 'Œ';
         else if (fabs (x_rel - x_cen) < 1.0)       c = 'Œ';
         if (d == (uchar) '²' && c == (uchar) 'Œ')  c = 'Š';
      }
      sprintf (t, "%c", c);
      DEBUG_YGLTEX    yLOG_complex ("loop"      , "%2d, %c, å%sæ", i, c, t);
      strcat  (zYGLTEX_print, t);
   }
   if (y_on == 'y')  strcat (zYGLTEX_print, "†");
   else              strcat (zYGLTEX_print, "");
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_textify_line     (FILE *f, int a_line, char a_style, int a_wide, int a_xscale, int a_xmargin, int a_yscale, int a_ymargin, int a_rbyte, png_bytep a_row)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        c           =    0;
   char        i           =    0;
   char        t           [LEN_FULL]  = "";
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_complex ("a_args"    , "%4d, %4dw, %3dxs, %3dys", a_line, a_wide, a_xscale, a_yscale);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_row"     , a_row);
   --rce;  if (a_row    == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(prepare)------------------------*/
   c = a_wide / a_xscale;
   DEBUG_YGLTEX    yLOG_point   ("c"         , c);
   /*---(header)-------------------------*/
   if (a_line % a_yscale == 0) {
      DEBUG_YGLTEX    yLOG_note    ("top line, must print headers");
      ygltex_textify_print  (f, '°');
      ygltex_textify_print  (f, 'H');
      ygltex_textify_print  (f, 'T');
   }
   /*---(detail)-------------------------*/
   strcpy (zYGLTEX_print, "");
   for (i = 0; i < c; ++i) {
      ygltex_textify_single (f, a_line, a_style, i * a_xscale, a_xscale, a_xmargin, a_yscale, a_ymargin, a_rbyte, a_row);
   }
   ygltex_textify_print  (f, '´');
   /*---(footer)-------------------------*/
   if (a_line % a_yscale == a_yscale - 1) {
      DEBUG_YGLTEX    yLOG_note    ("bottom line, must print footers");
      ygltex_textify_print  (f, 'B');
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          main driver                        ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER_____________o (void) {;}

char
yGLTEX_png2ascii         (cchar a_pngname [LEN_PATH], cchar a_tilename [LEN_PATH], char a_style, int a_xscale, int a_xmargin, int a_yscale, int a_ymargin)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         x_wide, x_tall, x_rbyte;
   png_byte   *x_image     = NULL;
   png_bytep  *x_rows      = NULL;
   FILE       *f           = NULL;
   int         i           =    0;
   png_bytep   x_row       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_complex ("a_args"    , "%c, %4dxs, %4dxm, %4dys, %4dym", a_style, a_xscale, a_xmargin, a_yscale, a_ymargin);
   /*---(open png file)------------------*/
   rc = ygltex_file_exist (a_pngname, YGLTEX_IMAGE, &x_wide, &x_tall, &x_rbyte, &x_image, &x_rows, NULL, NULL, NULL);
   DEBUG_YGLTEX    yLOG_value   ("exist"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_complex ("data"      , "%4dw, %4dt, %5dr, %p, %p", x_wide, x_tall, x_rbyte, x_image, x_rows);
   /*---(open output)--------------------*/
   rc = ygltex_file_open  (a_tilename, 'w', NULL, NULL, &f);
   DEBUG_YGLTEX    yLOG_value   ("open"      , rc);
   /*---(handle)-------------------------*/
   rc = ygltex_textify_prefix  (f, a_pngname, a_style, x_wide, x_tall, a_xscale, a_xmargin, a_yscale, a_ymargin);
   rc = ygltex_textify_prepare (x_wide, a_xscale, a_xmargin);
   for (i = 0; i < x_tall; ++i) {
      x_row = x_rows [i];
      rc = ygltex_textify_line (f, i, a_style, x_wide, a_xscale, a_xmargin, a_yscale, a_ymargin, x_rbyte, x_row);
      DEBUG_YGLTEX    yLOG_complex ("line"      , "%4d#, %4drc", i, rc);
   }
   /*---(close output)-------------------*/
   rc = ygltex_file_close (NULL, NULL, &f);
   DEBUG_YGLTEX    yLOG_value   ("close"     , rc);
   /*---(free image)---------------------*/
   rc = ygltex_image_free   (&x_image, &x_rows);
   DEBUG_YGLTEX    yLOG_value   ("image"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}


