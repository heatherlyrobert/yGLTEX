/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"




char               /* PURPOSE : make a png image into a texture --------------*/
yGLTEX__read_header  (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;             /* simple return code             */
   int         x_len       = 0;
   png_byte    x_header    [8];             /* png header                     */
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(check the header)---------------*/
   DEBUG_YGLTEX    yLOG_note    ("read header (first 8 bytes)");
   fread (x_header, 1, 8, s_file);
   rc = png_sig_cmp (x_header, 0, 8);
   DEBUG_YGLTEX    yLOG_value   ("rc"        , rc);
   --rce;  if (rc != 0) {
      DEBUG_YGLTEX    yLOG_warn    ("header can not interpret header");
      yGLTEX__file_close  ();
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(create read struct)-------------*/
   DEBUG_YGLTEX    yLOG_note    ("creating png pointer (s_png)");
   s_png = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   DEBUG_YGLTEX    yLOG_point   ("s_png"     , s_png);
   --rce;  if (s_png == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("s_png can not get a write structure");
      yGLTEX__file_close  ();
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(create info struct)-------------*/
   DEBUG_YGLTEX    yLOG_note    ("creating info pointer (s_info)");
   s_info = png_create_info_struct (s_png);
   DEBUG_YGLTEX    yLOG_point   ("s_info"    , s_info);
   --rce;  if (s_info == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("s_info can not get a info structure");
      yGLTEX__file_close  ();
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(create end struct)--------------*/
   DEBUG_YGLTEX    yLOG_note    ("creating end pointer (s_end)");
   s_end = png_create_info_struct (s_png);
   DEBUG_YGLTEX    yLOG_point   ("s_end"     , s_end);
   --rce;  if (s_end == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("s_end can not get a end structure");
      yGLTEX__file_close  ();
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char               /* PURPOSE : make a png image into a texture --------------*/
yGLTEX__read_attrib  (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;
   int         x_depth     = 0;
   int         x_color     = 0;
   int         x_channel   = 0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(error jump)---------------------*/
   DEBUG_YGLTEX    yLOG_note    ("setting a jump buffer");
   rc = setjmp (png_jmpbuf (s_png));
   DEBUG_YGLTEX    yLOG_value   ("setjmp"    , rc);
   -rce;  if (rc <  0) {
      DEBUG_YGLTEX    yLOG_warn    ("setjmp can not setjmp for header write");
      yGLTEX__file_close ();
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(setup read)---------------------*/
   DEBUG_YGLTEX    yLOG_note    ("initiating io (png_init_io)");
   png_init_io          (s_png, s_file);
   DEBUG_YGLTEX    yLOG_note    ("moving header information out of the way");
   png_set_sig_bytes    (s_png, 8);
   png_read_info        (s_png, s_info);
   /*---(get info)-----------------------*/
   s_width      = png_get_image_width  (s_png, s_info);
   DEBUG_YGLTEX    yLOG_value   ("width"     , s_width);
   s_height     = png_get_image_height (s_png, s_info);
   DEBUG_YGLTEX    yLOG_value   ("height"    , s_height);
   x_color      = png_get_color_type   (s_png, s_info);
   DEBUG_YGLTEX    yLOG_value   ("color"     , x_color);
   x_depth      = png_get_bit_depth    (s_png, s_info);
   DEBUG_YGLTEX    yLOG_value   ("depth"     , x_depth);
   DEBUG_YGLTEX    yLOG_note    ("read update");
   png_read_update_info (s_png, s_info);
   --rce;  if (x_color  != PNG_COLOR_TYPE_RGBA) {
      DEBUG_YGLTEX    yLOG_warn    ("x_color image is not RGBA");
      yGLTEX__file_close ();
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   s_rowbyte = png_get_rowbytes (s_png, s_info);
   DEBUG_YGLTEX    yLOG_value   ("rowbytes"  , s_rowbyte);
   x_channel = png_get_channels (s_png, s_info);
   DEBUG_YGLTEX    yLOG_value   ("channels"  , x_channel);
   /*---(transform)----------------------*/
   DEBUG_YGLTEX    yLOG_note    ("check pallette");
   if (x_color == PNG_COLOR_TYPE_PALETTE)
      png_set_palette_to_rgb (s_png);        /* makes rgb                      */
   DEBUG_YGLTEX    yLOG_note    ("check alpha");
   if (png_get_valid (s_png, s_info, PNG_INFO_tRNS))
      png_set_tRNS_to_alpha  (s_png);        /* expands out alpha              */
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char               /* PURPOSE : make a png image into a texture --------------*/
yGLTEX__read_image   (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(error jump)---------------------*/
   DEBUG_YGLTEX    yLOG_note    ("setting a jump buffer");
   rc = setjmp (png_jmpbuf (s_png));
   DEBUG_YGLTEX    yLOG_value   ("setjmp"    , rc);
   -rce;  if (rc <  0) {
      DEBUG_YGLTEX    yLOG_warn    ("setjmp can not setjmp for header write");
      yGLTEX__file_close ();
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(read)---------------------------*/
   DEBUG_YGLTEX    yLOG_note    ("read image data");
   png_read_image (s_png, s_rows);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char               /* PURPOSE : make a png image into a texture --------------*/
yGLTEX__read_tex     (void)
{
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(make texture)-------------------*/
   glGenTextures   (1, &s_tex);
   DEBUG_YGLTEX    yLOG_value   ("s_tex"     , s_tex);
   DEBUG_YGLTEX    yLOG_note    ("binding texture");
   glBindTexture   (GL_TEXTURE_2D, s_tex);
   DEBUG_YGLTEX    yLOG_note    ("set attributes");
   glTexParameteri (GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri (GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S,     GL_REPEAT );
   glTexParameterf (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T,     GL_REPEAT );
   glTexParameteri (GL_TEXTURE_2D,  GL_GENERATE_MIPMAP,    GL_TRUE);
   glTexEnvi       (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,   GL_REPLACE);
   /*> glHint          (GL_TEXTURE_COMPRESSION_HINT,           GL_NICEST);            <*/
   /*> glTexImage2D    (GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA, twidth, theight, 0, GL_RGBA, GL_UNSIGNED_BYTE, s_image);   <*/
   DEBUG_YGLTEX    yLOG_note    ("copy image to tex using glTexImage2D");
   glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGBA, s_width, s_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, s_image);
   DEBUG_YGLTEX    yLOG_note    ("unbinding texture");
   glBindTexture (GL_TEXTURE_2D, 0);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}


/*============================----end-of-source---============================*/
