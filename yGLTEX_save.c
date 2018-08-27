/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"


char
yGLTEX__save_header  (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;             /* simple return code             */
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(create read struct)-------------*/
   DEBUG_YGLTEX    yLOG_note    ("creating png pointer (s_png)");
   s_png = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   DEBUG_YGLTEX    yLOG_point   ("s_png"     , s_png);
   --rce;  if (s_png == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("s_png"    , "can not get a write structure");
      yGLTEX__file_close  ();
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(create info struct)-------------*/
   DEBUG_YGLTEX    yLOG_note    ("creating info pointer (s_info)");
   s_info = png_create_info_struct (s_png);
   DEBUG_YGLTEX    yLOG_point   ("s_info"    , s_info);
   --rce;  if (s_info == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("s_info"   , "can not get a info structure");
      yGLTEX__file_close  ();
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(error jump)---------------------*/
   DEBUG_YGLTEX    yLOG_note    ("setting a jump buffer");
   rc = setjmp (png_jmpbuf (s_png));
   DEBUG_YGLTEX    yLOG_value   ("setjmp"    , rc);
   -rce;  if (rc <  0) {
      DEBUG_YGLTEX    yLOG_warn    ("setjmp"   , "can not setjmp for header write");
      yGLTEX__file_close ();
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(prep header)--------------------*/
   DEBUG_YGLTEX    yLOG_note    ("writing header with png_init_io");
   png_init_io (s_png, s_file);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yGLTEX__save_attrib  (cint a_width, cint a_height)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;             /* simple return code             */
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(set attributes)-----------------*/
   DEBUG_YGLTEX    yLOG_note    ("save width, height, and rowbytes");
   s_width   = a_width;
   s_height  = a_height;
   s_rowbyte = s_width * 4;
   /*---(error jump)---------------------*/
   DEBUG_YGLTEX    yLOG_note    ("setting a jump buffer");
   rc = setjmp (png_jmpbuf (s_png));
   DEBUG_YGLTEX    yLOG_value   ("setjmp"    , rc);
   -rce;  if (rc <  0) {
      DEBUG_YGLTEX    yLOG_warn    ("setjmp"   , "can not setjmp for attrib write");
      yGLTEX__file_close ();
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(write header)-------------------*/
   DEBUG_YGLTEX    yLOG_note    ("write the attributes");
   png_set_IHDR (s_png, s_info, s_width, s_height,
         8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
         PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
   png_write_info (s_png, s_info);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yGLTEX__save_image   (cchar a_source)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;             /* simple return code             */
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(grab pixels)--------------------*/
   DEBUG_YGLTEX    yLOG_note    ("read the pixels into s_image");
   --rce;
   switch (a_source) {
   case 'w' :
      DEBUG_YGLTEX    yLOG_note    ("copying from window");
      glReadPixels  (0, 0, s_width, s_height, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *) s_image);
      break;
   case 't' :
      DEBUG_YGLTEX    yLOG_note    ("copying from texture");
      glCopyTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, s_width, s_height, 0);
      glGetTexImage    (GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *) s_image);
      break;
   default  : 
      DEBUG_YGLTEX    yLOG_note    ("unknown type");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(write image)--------------------*/
   DEBUG_YGLTEX    yLOG_note    ("save the pixels into the file");
   png_write_image (s_png, s_rows);
   DEBUG_YGLTEX    yLOG_note    ("write the fail ending");
   png_write_end   (s_png, s_info);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}



/*============================----end-of-source---============================*/
