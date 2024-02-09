/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"

/*
 *        SWITCH EVERYTHING TO PARAMETERS, NOT GLOBALS
 *
 */

/*> char yGLTEX__save_header  (void) { return 0; }                                    <*/

char
ygltex_save_header      (FILE *f, png_structp **r_png, png_infop **r_info)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("f"         , f);
   --rce;  if (f        == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("r_png"     , r_png);
   --rce;  if (r_png    == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("*r_png"    , *r_png);
   --rce;  if (*r_png   != NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("r_info"    , r_info);
   --rce;  if (r_info   == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("*r_info"   , *r_info);
   --rce;  if (*r_info  != NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(create write struct)------------*/
   DEBUG_YGLTEX    yLOG_note    ("creating png pointer (*r_png)");
   *r_png = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   DEBUG_YGLTEX    yLOG_point   ("*r_png"     , *r_png);
   --rce;  if (*r_png == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("can not get a write structure");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(create info struct)-------------*/
   DEBUG_YGLTEX    yLOG_note    ("creating info pointer (*r_info)");
   *r_info = png_create_info_struct (*r_png);
   DEBUG_YGLTEX    yLOG_point   ("*r_info"    , *r_info);
   --rce;  if (*r_info == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("can not get a info structure");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(error jump)---------------------*/
   DEBUG_YGLTEX    yLOG_note    ("setting a jump buffer");
   rc = setjmp (png_jmpbuf (*r_png));
   DEBUG_YGLTEX    yLOG_value   ("setjmp"    , rc);
   -rce;  if (rc <  0) {
      DEBUG_YGLTEX    yLOG_warn    ("not setjmp for header write");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(prep header)--------------------*/
   DEBUG_YGLTEX    yLOG_note    ("writing header with png_init_io");
   png_init_io (*r_png, f);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_save_free        (png_structp **r_png, png_infop **r_info)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("r_png"     , r_png);
   --rce;  if (r_png    == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("*r_png"    , *r_png);
   --rce;  if (*r_png   == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("r_info"    , r_info);
   --rce;  if (r_info   == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("*r_info"   , *r_info);
   --rce;  if (*r_info  == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(destroy)------------------------*/
   DEBUG_YGLTEX    yLOG_note    ("call destroy write structures");
   png_destroy_write_struct (r_png, r_info);
   /*---(ground)-------------------------*/
   DEBUG_YGLTEX    yLOG_note    ("ground pointers");
   *r_png  = NULL;
   DEBUG_YGLTEX    yLOG_point   ("*r_png"    , *r_png);
   *r_info = NULL;
   DEBUG_YGLTEX    yLOG_point   ("*r_info"   , *r_info);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_save_attrib      (png_structp *a_png, png_infop *a_info, int a_wide, int a_tall, int *r_rowbyte)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;             /* simple return code             */
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_rowbyte != NULL)  *r_rowbyte = 0;
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_png"     , a_png);
   --rce;  if (a_png    == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("a_info"    , a_info);
   --rce;  if (a_info   == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_wide"    , a_wide);
   --rce;  if (a_wide <= 0) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_value   ("a_tall"    , a_tall);
   --rce;  if (a_tall <= 0) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(error jump)---------------------*/
   DEBUG_YGLTEX    yLOG_note    ("setting a jump buffer");
   rc = setjmp (png_jmpbuf (a_png));
   DEBUG_YGLTEX    yLOG_value   ("setjmp"    , rc);
   -rce;  if (rc <  0) {
      DEBUG_YGLTEX    yLOG_warn    ("setjmp can not setjmp for attrib write");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(write header)-------------------*/
   DEBUG_YGLTEX    yLOG_note    ("write the attributes");
   png_set_IHDR (a_png, a_info, a_wide, a_tall,
         8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
         PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
   png_write_info (a_png, a_info);
   /*---(save-back)----------------------*/
   DEBUG_YGLTEX    yLOG_note    ("save width, height, and rowbytes");
   if (r_rowbyte != NULL)  *r_rowbyte = a_wide * 4;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_save_image    (png_structp *a_png, png_infop *a_info, png_byte *a_image, png_bytep *a_rows, char a_source, int a_wide, int a_tall)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_png"     , a_png);
   --rce;  if (a_png    == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("a_info"    , a_info);
   --rce;  if (a_info   == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("a_image"   , a_image);
   --rce;  if (a_image  == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("a_rows"    , a_rows);
   --rce;  if (a_rows   == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(grab pixels)--------------------*/
   DEBUG_YGLTEX    yLOG_note    ("read the pixels into a_image");
   --rce;
   switch (a_source) {
   case 'w' :
      DEBUG_YGLTEX    yLOG_note    ("copying from window");
      glReadPixels  (0, 0, a_wide, a_tall, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *) a_image);
      break;
   case 't' :
      DEBUG_YGLTEX    yLOG_note    ("copying from texture");
      glCopyTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, a_wide, a_tall, 0);
      glGetTexImage    (GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *) a_image);
      break;
   case 'c' :
      DEBUG_YGLTEX    yLOG_note    ("edited in place");
      break;
   default  : 
      DEBUG_YGLTEX    yLOG_note    ("unknown type");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(write image)--------------------*/
   DEBUG_YGLTEX    yLOG_note    ("save the pixels into the file");
   png_write_image (a_png, a_rows);
   DEBUG_YGLTEX    yLOG_note    ("write the fail ending");
   png_write_end   (a_png, a_info);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                               <* 
 *> yYGLTEX__save_header   (void)                                                      <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-----------+-----------+-+/                                        <* 
 *>    char        rce         = -10;           /+ return code for errors         +/   <* 
 *>    int         rc          = 0;             /+ simple return code             +/   <* 
 *>    /+---(header)-------------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);                                    <* 
 *>    /+---(create read struct)-------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("creating png pointer (s_png)");                  <* 
 *>    s_png = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);      <* 
 *>    DEBUG_YGLTEX    yLOG_point   ("s_png"     , s_png);                             <* 
 *>    --rce;  if (s_png == NULL) {                                                    <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("s_png can not get a write structure");        <* 
 *>       ygltex_file_close_easy  ();                                                  <* 
 *>       DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                 <* 
 *>       return  rce;                                                                 <* 
 *>    }                                                                               <* 
 *>    /+---(create info struct)-------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("creating info pointer (s_info)");                <* 
 *>    s_info = png_create_info_struct (s_png);                                        <* 
 *>    DEBUG_YGLTEX    yLOG_point   ("s_info"    , s_info);                            <* 
 *>    --rce;  if (s_info == NULL) {                                                   <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("s_info can not get a info structure");        <* 
 *>       ygltex_file_close_easy  ();                                                  <* 
 *>       DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                 <* 
 *>       return  rce;                                                                 <* 
 *>    }                                                                               <* 
 *>    /+---(error jump)---------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("setting a jump buffer");                         <* 
 *>    rc = setjmp (png_jmpbuf (s_png));                                               <* 
 *>    DEBUG_YGLTEX    yLOG_value   ("setjmp"    , rc);                                <* 
 *>    -rce;  if (rc <  0) {                                                           <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("setjmp can not setjmp for header write");     <* 
 *>       ygltex_file_close_easy ();                                                   <* 
 *>       DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                 <* 
 *>       return  rce;                                                                 <* 
 *>    }                                                                               <* 
 *>    /+---(prep header)--------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("writing header with png_init_io");               <* 
 *>    png_init_io (s_png, zYGLTEX.f_file);                                            <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                    <* 
 *>    return 0;                                                                       <* 
 *> }                                                                                  <*/

/*> char                                                                               <* 
 *> yGLTEX__save_attrib  (cint a_width, cint a_height)                                 <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-----------+-----------+-+/                                        <* 
 *>    char        rce         = -10;           /+ return code for errors         +/   <* 
 *>    int         rc          = 0;             /+ simple return code             +/   <* 
 *>    /+---(header)-------------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);                                    <* 
 *>    /+---(set attributes)-----------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("save width, height, and rowbytes");              <* 
 *>    s_width   = a_width;                                                            <* 
 *>    s_height  = a_height;                                                           <* 
 *>    s_rowbyte = s_width * 4;                                                        <* 
 *>    /+---(error jump)---------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("setting a jump buffer");                         <* 
 *>    rc = setjmp (png_jmpbuf (s_png));                                               <* 
 *>    DEBUG_YGLTEX    yLOG_value   ("setjmp"    , rc);                                <* 
 *>    -rce;  if (rc <  0) {                                                           <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("setjmp can not setjmp for attrib write");     <* 
 *>       ygltex_file_close_easy ();                                                   <* 
 *>       DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                 <* 
 *>       return  rce;                                                                 <* 
 *>    }                                                                               <* 
 *>    /+---(write header)-------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("write the attributes");                          <* 
 *>    png_set_IHDR (s_png, s_info, s_width, s_height,                                 <* 
 *>          8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,                               <* 
 *>          PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);                         <* 
 *>    png_write_info (s_png, s_info);                                                 <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                    <* 
 *>    return 0;                                                                       <* 
 *> }                                                                                  <*/

/*> char                                                                                            <* 
 *> yGLTEX__save_image   (cchar a_source)                                                           <* 
 *> {                                                                                               <* 
 *>    /+---(locals)-----------+-----------+-+/                                                     <* 
 *>    char        rce         = -10;           /+ return code for errors         +/                <* 
 *>    int         rc          = 0;             /+ simple return code             +/                <* 
 *>    /+---(header)-------------------------+/                                                     <* 
 *>    DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);                                                 <* 
 *>    /+---(grab pixels)--------------------+/                                                     <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("read the pixels into s_image");                               <* 
 *>    --rce;                                                                                       <* 
 *>    switch (a_source) {                                                                          <* 
 *>    case 'w' :                                                                                   <* 
 *>       DEBUG_YGLTEX    yLOG_note    ("copying from window");                                     <* 
 *>       glReadPixels  (0, 0, s_width, s_height, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *) s_image);   <* 
 *>       break;                                                                                    <* 
 *>    case 't' :                                                                                   <* 
 *>       DEBUG_YGLTEX    yLOG_note    ("copying from texture");                                    <* 
 *>       glCopyTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, s_width, s_height, 0);                 <* 
 *>       glGetTexImage    (GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *) s_image);       <* 
 *>       break;                                                                                    <* 
 *>    case 'c' :                                                                                   <* 
 *>       DEBUG_YGLTEX    yLOG_note    ("edited in place");                                         <* 
 *>       break;                                                                                    <* 
 *>    default  :                                                                                   <* 
 *>       DEBUG_YGLTEX    yLOG_note    ("unknown type");                                            <* 
 *>       DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);                                         <* 
 *>       return rce;                                                                               <* 
 *>    }                                                                                            <* 
 *>    /+---(write image)--------------------+/                                                     <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("save the pixels into the file");                              <* 
 *>    png_write_image (s_png, s_rows);                                                             <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("write the fail ending");                                      <* 
 *>    png_write_end   (s_png, s_info);                                                             <* 
 *>    /+---(complete)-----------------------+/                                                     <* 
 *>    DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                                 <* 
 *>    return 0;                                                                                    <* 
 *> }                                                                                               <*/



/*============================----end-of-source---============================*/
