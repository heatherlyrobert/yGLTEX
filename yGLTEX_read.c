/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"




char
ygltex_read_header      (FILE *f, png_structp **r_png, png_infop **r_info, png_infop **r_end)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   png_byte    x_header    [8];             /* png header                     */
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
   DEBUG_YGLTEX    yLOG_point   ("r_end"     , r_end);
   --rce;  if (r_end    == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("*r_end"    , *r_end);
   --rce;  if (*r_end   != NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(check the header)---------------*/
   DEBUG_YGLTEX    yLOG_note    ("read header (first 8 bytes)");
   fread (x_header, 1, 8, f);
   rc = png_sig_cmp (x_header, 0, 8);
   DEBUG_YGLTEX    yLOG_value   ("rc"        , rc);
   --rce;  if (rc != 0) {
      DEBUG_YGLTEX    yLOG_warn    ("header can not interpret header");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(create read struct)-------------*/
   DEBUG_YGLTEX    yLOG_note    ("creating png pointer (*r_png)");
   *r_png = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   DEBUG_YGLTEX    yLOG_point   ("*r_png"    , *r_png);
   --rce;  if (*r_png == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("can not get a write structure");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(create info struct)-------------*/
   DEBUG_YGLTEX    yLOG_note    ("creating info pointer (*r_info)");
   *r_info = png_create_info_struct (*r_png);
   DEBUG_YGLTEX    yLOG_point   ("*r_info"   , *r_info);
   --rce;  if (*r_info == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("can not get a info structure");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(create end struct)--------------*/
   DEBUG_YGLTEX    yLOG_note    ("creating end pointer (*r_end)");
   *r_end = png_create_info_struct (*r_png);
   DEBUG_YGLTEX    yLOG_point   ("*r_end"    , *r_end);
   --rce;  if (*r_end == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("can not get a end structure");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_read_free        (png_structp **r_png, png_infop **r_info, png_infop **r_end)
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
   DEBUG_YGLTEX    yLOG_point   ("r_end"     , r_end);
   --rce;  if (r_end    == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("*r_end"    , *r_end);
   --rce;  if (*r_end   == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(destroy)------------------------*/
   DEBUG_YGLTEX    yLOG_note    ("call destroy read structures");
   png_destroy_read_struct (r_png, r_info, r_end);
   /*---(ground)-------------------------*/
   DEBUG_YGLTEX    yLOG_note    ("ground pointers");
   *r_png  = NULL;
   DEBUG_YGLTEX    yLOG_point   ("*r_png"    , *r_png);
   *r_info = NULL;
   DEBUG_YGLTEX    yLOG_point   ("*r_info"   , *r_info);
   *r_end  = NULL;
   DEBUG_YGLTEX    yLOG_point   ("*r_end"    , *r_end);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_read_attrib      (FILE *f, png_structp *a_png, png_infop *a_info, int *r_wide, int *r_tall, int *r_color, int *r_depth, int *r_rowbyte, int *r_channel)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;
   int         x_wide, x_tall, x_depth, x_color, x_rowbyte, x_channel;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_wide    != NULL)  *r_wide    = 0;
   if (r_tall    != NULL)  *r_tall    = 0;
   if (r_color   != NULL)  *r_color   = 0;
   if (r_depth   != NULL)  *r_depth   = 0;
   if (r_rowbyte != NULL)  *r_rowbyte = 0;
   if (r_channel != NULL)  *r_channel = 0;
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("f"         , f);
   --rce;  if (f        == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
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
   /*---(error jump)---------------------*/
   DEBUG_YGLTEX    yLOG_note    ("setting a jump buffer");
   rc = setjmp (png_jmpbuf (a_png));
   DEBUG_YGLTEX    yLOG_value   ("setjmp"    , rc);
   -rce;  if (rc <  0) {
      DEBUG_YGLTEX    yLOG_warn    ("setjmp can not setjmp for header write");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(setup read)---------------------*/
   DEBUG_YGLTEX    yLOG_note    ("initiating io (png_init_io)");
   png_init_io          (a_png, f);
   DEBUG_YGLTEX    yLOG_note    ("moving header information out of the way");
   png_set_sig_bytes    (a_png, 8);
   png_read_info        (a_png, a_info);
   /*---(get info)-----------------------*/
   x_wide       = png_get_image_width  (a_png, a_info);
   DEBUG_YGLTEX    yLOG_value   ("x_wide"    , x_wide);
   x_tall       = png_get_image_height (a_png, a_info);
   DEBUG_YGLTEX    yLOG_value   ("height"    , x_tall);
   x_color      = png_get_color_type   (a_png, a_info);
   DEBUG_YGLTEX    yLOG_value   ("color"     , x_color);
   x_depth      = png_get_bit_depth    (a_png, a_info);
   DEBUG_YGLTEX    yLOG_value   ("depth"     , x_depth);
   DEBUG_YGLTEX    yLOG_note    ("read update");
   png_read_update_info (a_png, a_info);
   --rce;  if (x_color  != PNG_COLOR_TYPE_RGBA) {
      DEBUG_YGLTEX    yLOG_warn    ("x_color image is not RGBA");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   x_rowbyte = png_get_rowbytes (a_png, a_info);
   DEBUG_YGLTEX    yLOG_value   ("rowbytes"  , x_rowbyte);
   x_channel = png_get_channels (a_png, a_info);
   DEBUG_YGLTEX    yLOG_value   ("channels"  , x_channel);
   /*---(transform)----------------------*/
   DEBUG_YGLTEX    yLOG_note    ("check pallette");
   if (x_color == PNG_COLOR_TYPE_PALETTE)
      png_set_palette_to_rgb (a_png);        /* makes rgb                      */
   DEBUG_YGLTEX    yLOG_note    ("check alpha");
   if (png_get_valid (a_png, a_info, PNG_INFO_tRNS))
      png_set_tRNS_to_alpha  (a_png);        /* expands out alpha              */
   /*---(save-back)----------------------*/
   if (r_wide    != NULL)  *r_wide    = x_wide;
   if (r_tall    != NULL)  *r_tall    = x_tall;
   if (r_color   != NULL)  *r_color   = x_color;
   if (r_depth   != NULL)  *r_depth   = x_depth;
   if (r_rowbyte != NULL)  *r_rowbyte = x_rowbyte;
   if (r_channel != NULL)  *r_channel = x_channel;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_read_image       (png_structp *a_png, png_byte *a_image, png_bytep *a_rows, char a_dest, int a_wide, int a_tall, int *r_tex)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_png"     , a_png);
   --rce;  if (a_png    == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("a_rows"    , a_rows);
   --rce;  if (a_rows   == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(error jump)---------------------*/
   DEBUG_YGLTEX    yLOG_note    ("setting a jump buffer");
   rc = setjmp (png_jmpbuf (a_png));
   DEBUG_YGLTEX    yLOG_value   ("setjmp"    , rc);
   -rce;  if (rc <  0) {
      DEBUG_YGLTEX    yLOG_warn    ("setjmp can not setjmp for header write");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(read)---------------------------*/
   DEBUG_YGLTEX    yLOG_note    ("read image data");
   png_read_image (a_png, a_rows);
   /*---(make texture)-------------------*/
   DEBUG_YGLTEX    yLOG_point   ("r_tex"     , r_tex);
   if (a_dest == YGLTEX_TEXTURE && r_tex != NULL) {
      glGenTextures   (1, r_tex);
      DEBUG_YGLTEX    yLOG_value   ("*r_tex"    , *r_tex);
      DEBUG_YGLTEX    yLOG_note    ("binding texture");
      glBindTexture   (GL_TEXTURE_2D, *r_tex);
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
      glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGBA, a_wide, a_tall, 0, GL_RGBA, GL_UNSIGNED_BYTE, a_image);
      DEBUG_YGLTEX    yLOG_note    ("unbinding texture");
      glBindTexture (GL_TEXTURE_2D, 0);
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_read_parse       (int a_wide, int a_tall, int a_rbyte, png_bytep *a_rows, void *c_titles, void *c_headers)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   uchar      *x_rdata     = NULL;
   int         x_row, x_col;
   int         x_xpos      =    0;
   int         x_ypos      =    0;
   char        x_title     [LEN_DESC]  = "";
   char        x_cat       [LEN_LABEL];
   char        x_sub       [LEN_LABEL];
   char        x_name      [LEN_LABEL];
   int         x_used, x_xmax, x_ymax, x_fields, x_xscale, x_yscale, x_buffer;
   char      (*x_titles)   (char a_title [LEN_DESC], int a_used, int a_xmax, int a_ymax, int a_fields, int a_xscale, int a_yscale, int a_buffer);
   char      (*x_headers)  (int a_row, int a_col, char a_cat [LEN_LABEL], char a_sub [LEN_LABEL], char a_name [LEN_LABEL]);
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_complex ("a_args"    , "%4dw, %4dt, %5dr, %p, %p, %p", a_wide, a_tall, a_rbyte, a_rows, c_titles, c_headers);
   /*---(quick-out)----------------------*/
   if (c_titles == NULL && c_headers == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return 0;
   }
   x_titles  = c_titles;
   x_headers = c_headers;
   /*---(defense)------------------------*/
   --rce;  if (a_rows == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(extract title)------------------*/
   if (x_titles  != NULL) {
      x_rdata = a_rows [0];
      rc = ygltex_title_read       (a_rbyte, x_rdata, x_title, NULL, NULL, NULL, &x_used, &x_xmax, &x_ymax, &x_fields, &x_xscale, &x_yscale, &x_buffer);
      DEBUG_YGLTEX    yLOG_complex ("title"     , "%4drc, %-30.30s, %3du, %3dx, %3dy, %df, %3dxc, %3dys, %2db", rc, x_title, x_used, x_xmax, x_ymax, x_fields, x_xscale, x_yscale, x_buffer);
      --rce;  if (rc < 0) {
         DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = x_titles (x_title, x_used, x_xmax, x_ymax, x_fields, x_xscale, x_yscale, x_buffer);
      DEBUG_YGLTEX    yLOG_value   ("x_titles"  , rc);
   } else {
      DEBUG_YGLTEX    yLOG_note    ("title data not requested (no function pointer given)");
   }
   /*---(headers)------------------------*/
   if (x_headers != NULL) {
      for (x_row = 0; x_row < x_ymax; ++x_row) {
         x_ypos  = x_buffer + (x_buffer * x_row) + (x_yscale * x_row) - 3;
         DEBUG_YGLTEX    yLOG_value   ("x_ypos"    , x_ypos);
         x_rdata = a_rows [x_ypos];
         for (x_col = 0; x_col < x_xmax; ++x_col) {
            rc = ygltex_header_read (a_rbyte, x_rdata, x_col, x_xscale, x_buffer, x_fields, x_cat, x_sub, x_name);
            DEBUG_YGLTEX    yLOG_complex ("header"    , "%2dr, %2dc, %4drc, %-20.20s, %-20.20s, %-20.20s", x_row, x_col, rc, x_cat, x_sub, x_name);
            if (rc >= 0) {
               rc = x_headers (x_row, x_col, x_cat, x_sub, x_name);
               DEBUG_YGLTEX    yLOG_value   ("x_headers" , rc);
            }
         }
      }
   } else {
      DEBUG_YGLTEX    yLOG_note    ("header data not requested (no function pointer given)");
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}




/*> char               /+ PURPOSE : make a png image into a texture --------------+/   <* 
 *> yGLTEX__read_header  (void)                                                        <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-----------+-----------+-+/                                        <* 
 *>    char        rce         = -10;           /+ return code for errors         +/   <* 
 *>    int         rc          = 0;             /+ simple return code             +/   <* 
 *>    int         x_len       = 0;                                                    <* 
 *>    png_byte    x_header    [8];             /+ png header                     +/   <* 
 *>    /+---(header)-------------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);                                    <* 
 *>    /+---(check the header)---------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("read header (first 8 bytes)");                   <* 
 *>    fread (x_header, 1, 8, zYGLTEX.f_file);                                         <* 
 *>    rc = png_sig_cmp (x_header, 0, 8);                                              <* 
 *>    DEBUG_YGLTEX    yLOG_value   ("rc"        , rc);                                <* 
 *>    --rce;  if (rc != 0) {                                                          <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("header can not interpret header");            <* 
 *>       ygltex_file_close_easy  ();                                                  <* 
 *>       DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                 <* 
 *>       return  rce;                                                                 <* 
 *>    }                                                                               <* 
 *>    /+---(create read struct)-------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("creating png pointer (s_png)");                  <* 
 *>    s_png = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);       <* 
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
 *>    /+---(create end struct)--------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("creating end pointer (s_end)");                  <* 
 *>    s_end = png_create_info_struct (s_png);                                         <* 
 *>    DEBUG_YGLTEX    yLOG_point   ("s_end"     , s_end);                             <* 
 *>    --rce;  if (s_end == NULL) {                                                    <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("s_end can not get a end structure");          <* 
 *>       ygltex_file_close_easy  ();                                                  <* 
 *>       DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                 <* 
 *>       return  rce;                                                                 <* 
 *>    }                                                                               <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                    <* 
 *>    return 0;                                                                       <* 
 *> }                                                                                  <*/

/*> char               /+ PURPOSE : make a png image into a texture --------------+/    <* 
 *> yGLTEX__read_attrib  (void)                                                         <* 
 *> {                                                                                   <* 
 *>    /+---(locals)-----------+-----------+-+/                                         <* 
 *>    char        rce         = -10;           /+ return code for errors         +/    <* 
 *>    char        rc          =   0;                                                   <* 
 *>    int         x_depth     = 0;                                                     <* 
 *>    int         x_color     = 0;                                                     <* 
 *>    int         x_channel   = 0;                                                     <* 
 *>    /+---(header)-------------------------+/                                         <* 
 *>    DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);                                     <* 
 *>    /+---(error jump)---------------------+/                                         <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("setting a jump buffer");                          <* 
 *>    rc = setjmp (png_jmpbuf (s_png));                                                <* 
 *>    DEBUG_YGLTEX    yLOG_value   ("setjmp"    , rc);                                 <* 
 *>    -rce;  if (rc <  0) {                                                            <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("setjmp can not setjmp for header write");      <* 
 *>       ygltex_file_close_easy ();                                                    <* 
 *>       DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                  <* 
 *>       return  rce;                                                                  <* 
 *>    }                                                                                <* 
 *>    /+---(setup read)---------------------+/                                         <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("initiating io (png_init_io)");                    <* 
 *>    png_init_io          (s_png, zYGLTEX.f_file);                                    <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("moving header information out of the way");       <* 
 *>    png_set_sig_bytes    (s_png, 8);                                                 <* 
 *>    png_read_info        (s_png, s_info);                                            <* 
 *>    /+---(get info)-----------------------+/                                         <* 
 *>    s_width      = png_get_image_width  (s_png, s_info);                             <* 
 *>    DEBUG_YGLTEX    yLOG_value   ("width"     , s_width);                            <* 
 *>    s_height     = png_get_image_height (s_png, s_info);                             <* 
 *>    DEBUG_YGLTEX    yLOG_value   ("height"    , s_height);                           <* 
 *>    x_color      = png_get_color_type   (s_png, s_info);                             <* 
 *>    DEBUG_YGLTEX    yLOG_value   ("color"     , x_color);                            <* 
 *>    x_depth      = png_get_bit_depth    (s_png, s_info);                             <* 
 *>    DEBUG_YGLTEX    yLOG_value   ("depth"     , x_depth);                            <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("read update");                                    <* 
 *>    png_read_update_info (s_png, s_info);                                            <* 
 *>    --rce;  if (x_color  != PNG_COLOR_TYPE_RGBA) {                                   <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("x_color image is not RGBA");                   <* 
 *>       ygltex_file_close_easy ();                                                    <* 
 *>       DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                  <* 
 *>       return  rce;                                                                  <* 
 *>    }                                                                                <* 
 *>    s_rowbyte = png_get_rowbytes (s_png, s_info);                                    <* 
 *>    DEBUG_YGLTEX    yLOG_value   ("rowbytes"  , s_rowbyte);                          <* 
 *>    x_channel = png_get_channels (s_png, s_info);                                    <* 
 *>    DEBUG_YGLTEX    yLOG_value   ("channels"  , x_channel);                          <* 
 *>    /+---(transform)----------------------+/                                         <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("check pallette");                                 <* 
 *>    if (x_color == PNG_COLOR_TYPE_PALETTE)                                           <* 
 *>       png_set_palette_to_rgb (s_png);        /+ makes rgb                      +/   <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("check alpha");                                    <* 
 *>    if (png_get_valid (s_png, s_info, PNG_INFO_tRNS))                                <* 
 *>       png_set_tRNS_to_alpha  (s_png);        /+ expands out alpha              +/   <* 
 *>    /+---(complete)-----------------------+/                                         <* 
 *>    DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                     <* 
 *>    return 0;                                                                        <* 
 *> }                                                                                   <*/

/*> char               /+ PURPOSE : make a png image into a texture --------------+/   <* 
 *> yGLTEX__read_image   (void)                                                        <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-----------+-----------+-+/                                        <* 
 *>    char        rce         = -10;           /+ return code for errors         +/   <* 
 *>    char        rc          =   0;                                                  <* 
 *>    /+---(header)-------------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);                                    <* 
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
 *>    /+---(read)---------------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("read image data");                               <* 
 *>    png_read_image (s_png, s_rows);                                                 <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                    <* 
 *>    return 0;                                                                       <* 
 *> }                                                                                  <*/

/*> char               /+ PURPOSE : make a png image into a texture --------------+/                                               <* 
 *> yGLTEX__read_tex     (void)                                                                                                    <* 
 *> {                                                                                                                              <* 
 *>    /+---(header)-------------------------+/                                                                                    <* 
 *>    DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);                                                                                <* 
 *>    /+---(make texture)-------------------+/                                                                                    <* 
 *>    glGenTextures   (1, &s_tex);                                                                                                <* 
 *>    DEBUG_YGLTEX    yLOG_value   ("s_tex"     , s_tex);                                                                         <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("binding texture");                                                                           <* 
 *>    glBindTexture   (GL_TEXTURE_2D, s_tex);                                                                                     <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("set attributes");                                                                            <* 
 *>    glTexParameteri (GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);                                           <* 
 *>    glTexParameteri (GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR);                                                         <* 
 *>    glTexParameterf (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S,     GL_REPEAT );                                                        <* 
 *>    glTexParameterf (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T,     GL_REPEAT );                                                        <* 
 *>    glTexParameteri (GL_TEXTURE_2D,  GL_GENERATE_MIPMAP,    GL_TRUE);                                                           <* 
 *>    glTexEnvi       (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,   GL_REPLACE);                                                        <* 
 *>    /+> glHint          (GL_TEXTURE_COMPRESSION_HINT,           GL_NICEST);            <+/                                      <* 
 *>    /+> glTexImage2D    (GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA, twidth, theight, 0, GL_RGBA, GL_UNSIGNED_BYTE, s_image);   <+/   <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("copy image to tex using glTexImage2D");                                                      <* 
 *>    glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGBA, s_width, s_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, s_image);                      <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("unbinding texture");                                                                         <* 
 *>    glBindTexture (GL_TEXTURE_2D, 0);                                                                                           <* 
 *>    /+---(complete)-----------------------+/                                                                                    <* 
 *>    DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                                                                <* 
 *>    return 0;                                                                                                                   <* 
 *> }                                                                                                                              <*/


/*============================----end-of-source---============================*/
