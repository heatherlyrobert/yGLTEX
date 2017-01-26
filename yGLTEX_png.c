/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"


static FILE          *s_file      = NULL;
static png_structp    s_png;
static png_infop      s_info;
static png_infop      s_end;
static png_byte      *s_image     = NULL;;
static png_bytep     *s_rows      = NULL;;
GLuint                s_tex       = 0;;
static int            s_width     = 0;
static int            s_height    = 0;
static int            s_rowbyte   = 0;


char               /* PURPOSE : make a png image into a texture --------------*/
yGLTEX__png_open     (const char *a_filename)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         x_len       = 0;
   /*---(defense)------------------------*/
   --rce;  if (a_filename == NULL) {
    URG_VERB     printf("   - FATAL, filename is null\n");
      return  rce;
   }
   x_len = strlen (a_filename);
   --rce;  if (x_len < 5) {
    URG_VERB     printf("   - FATAL, file name too short (%d < 5)\n", x_len);
      return  rce;
   }
   URG_VERB   printf ("   - file name : %s\n", a_filename);
   /*---(open png file)------------------*/
   s_file = fopen (a_filename, "rb");
   --rce;  if (s_file == NULL) {
      URG_VERB   printf("   - FATAL, can not find file\n");
      return rce;
   }
   URG_VERB   printf ("   - status    : confirmed and open for read-binary\n");
   return 0;
}

char               /* PURPOSE : make a png image into a texture --------------*/
yGLTEX__png_close    (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   /*---(destroy pointers)---------------*/
   png_destroy_read_struct (&s_png, &s_info, &s_end);
   /*---(clear memory)-------------------*/
   --rce;  if (s_image != NULL) {
      free     (s_image);
      s_image = NULL;
   }
   --rce;  if (s_rows  != NULL) {
      free     (s_rows);
      s_rows  = NULL;
   }
   /*---(close file)---------------------*/
   --rce;  if (s_file  != NULL) {
      fclose   (s_file);
      s_file  = NULL;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char               /* PURPOSE : make a png image into a texture --------------*/
yGLTEX__png_header   (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;             /* simple return code             */
   int         x_len       = 0;
   png_byte    x_header    [8];             /* png header                     */
   /*---(check the header)---------------*/
   fread (x_header, 1, 8, s_file);
   rc = png_sig_cmp (x_header, 0, 8);
   --rce;  if (rc != 0) {
      fclose(s_file);
      URG_VERB     printf("   - FATAL, header not png\n");
      return  rce;
   }
   URG_VERB   printf("   - header    : confirmed as png\n");
   /*---(create read struct)-------------*/
   s_png = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   --rce;  if (s_png == NULL) {
      URG_VERB   printf("   - FATAL, s_png error\n");
      yGLTEX__png_close  ();
      return  rce;
   }
   URG_VERB   printf("   - pointer   : png pointer confirmed\n");
   /*---(create info struct)-------------*/
   s_info = png_create_info_struct (s_png);
   --rce;  if (s_info == NULL) {
      URG_VERB   printf("   - FATAL, s_info error\n");
      yGLTEX__png_close  ();
      return  rce;
   }
   URG_VERB   printf("   - pointer   : info pointer confirmed\n");
   /*---(create info struct)-------------*/
   s_end = png_create_info_struct (s_png);
   --rce;  if (s_end == NULL) {
      URG_VERB   printf("   - FATAL, end_ptr error\n");
      yGLTEX__png_close  ();
      return  rce;
   }
   URG_VERB   printf("   - pointer   : end pointer confirmed\n");
   return 0;
}

char               /* PURPOSE : make a png image into a texture --------------*/
yGLTEX__png_attrib   (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;
   int         x_depth     = 0;
   int         x_color     = 0;
   int         x_channel   = 0;
   /*---(error stuff 1)------------------*/
   URG_VERB   printf ("   - set jump  : ");
   rc = setjmp (png_jmpbuf (s_png));
   URG_VERB   printf ("(%d) ", rc);
   -rce;  if (rc <  0) {
      URG_VERB   printf ("FAILED, closing and exiting\n");
      yGLTEX__png_close  ();
      return  rce;
   }
   URG_VERB   printf ("confirmed\n");
   /*---(setup read)---------------------*/
   png_init_io          (s_png, s_file);
   png_set_sig_bytes    (s_png, 8);
   png_read_info        (s_png, s_info);
   URG_VERB   printf ("   - set read  : complete\n");
   /*---(get info)-----------------------*/
   s_width      = png_get_image_width  (s_png, s_info);
   URG_VERB   printf ("   - width     : %ld\n", s_width);
   s_height     = png_get_image_height (s_png, s_info);
   URG_VERB   printf ("   - height    : %ld\n", s_height);
   x_color      = png_get_color_type   (s_png, s_info);
   URG_VERB   printf ("   - color     : %ld\n", x_color);
   x_depth      = png_get_bit_depth    (s_png, s_info);
   URG_VERB   printf ("   - depth     : %ld\n", x_depth);
   png_read_update_info (s_png, s_info);
   --rce;  if (x_color  != PNG_COLOR_TYPE_RGBA) {
      URG_VERB   printf("   - FATAL, color is NOT RGBA\n");
      yGLTEX__png_close  ();
      return  rce;
   }
   URG_VERB   printf("   - color is RGBA, excellent\n");
   s_rowbyte = png_get_rowbytes (s_png, s_info);
   URG_VERB   printf ("   - rowbytes  : %ld\n", s_rowbyte);
   x_channel = png_get_channels (s_png, s_info);
   URG_VERB   printf ("   - channels  : %ld\n", x_channel);
   /*---(transform)----------------------*/
   if (x_color == PNG_COLOR_TYPE_PALETTE)
      png_set_palette_to_rgb (s_png);        /* makes rgb                      */
   if (png_get_valid (s_png, s_info, PNG_INFO_tRNS))
      png_set_tRNS_to_alpha  (s_png);        /* expands out alpha              */
   URG_VERB   printf("   - palette and alpha are good\n");
   /*---(complete)-----------------------*/
   return 0;
}

char               /* PURPOSE : make a png image into a texture --------------*/
yGLTEX__png_read     (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   /*---(error stuff 2)------------------*/
   --rce;  if (setjmp(png_jmpbuf(s_png))) {
      URG_VERB   printf("   - FATAL, error during read image\n");
      yGLTEX__png_close  ();
      return  rce;
   }
   URG_VERB   printf("   - setjmp is good\n");
   /*---(allocate image)-----------------*/
   s_image = (unsigned char*) malloc(sizeof(png_byte) * s_rowbyte * s_height);
   --rce;  if (!s_image) {
      URG_VERB   printf("s_image error\n");
      yGLTEX__png_close  ();
      return  rce;
   }
   URG_VERB   printf("   - image data is good\n");
   /*---(row pointers)-------------------*/
   s_rows = (png_bytepp)  malloc(sizeof(png_bytep) * s_height);
   --rce;  if (s_rows == NULL) {
      URG_VERB   printf("s_rows error\n");
      yGLTEX__png_close  ();
      return  rce;
   }
   URG_VERB   printf("   - row pointers are good\n");
   uint i;
   for (i = 0; i < s_height; ++i) {
      s_rows[s_height - 1 - i] = s_image + (i * s_rowbyte);
   }
   /*---(read)---------------------------*/
   URG_VERB   printf("   - pre read_image\n");
   png_read_image (s_png, s_rows);
   URG_VERB   printf("   - read_image was good\n");
   /*> unsigned char *bytey;                                                                  <* 
    *> for (i = 0; i < s_rowbyte; ++i) {                                               <* 
    *>    bytey = s_image + (50 * s_rowbyte) + i;                                   <* 
    *>    *bytey = 255;                                                               <* 
    *> }                                                                              <*/
   return 0;
}

char               /* PURPOSE : make a png image into a texture --------------*/
yGLTEX__png_tex      (void)
{
   /*---(make texture)-------------------*/
   glGenTextures   (1, &s_tex);
   URG_VERB   printf("   - texture   : %d\n", s_tex);
   glBindTexture   (GL_TEXTURE_2D, s_tex);
   URG_VERB   printf("   - bound\n");
   glTexParameteri (GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri (GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S,     GL_REPEAT );
   glTexParameterf (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T,     GL_REPEAT );
   glTexParameteri (GL_TEXTURE_2D,  GL_GENERATE_MIPMAP,    GL_TRUE);
   glTexEnvi       (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,   GL_REPLACE);
   URG_VERB   printf("   - set up attributes\n");
   /*> glHint          (GL_TEXTURE_COMPRESSION_HINT,           GL_NICEST);            <*/
   /*> glTexImage2D    (GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA, twidth, theight, 0, GL_RGBA, GL_UNSIGNED_BYTE, s_image);   <*/
   glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGBA, s_width, s_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, s_image);
   URG_VERB   printf("   - drew image\n");
   glBindTexture (GL_TEXTURE_2D, 0);
   URG_VERB   printf("   - unbound texture\n");
   /*---(clean)--------------------------*/
   return 0;
}

GLuint             /* PURPOSE : make a png image into a texture --------------*/
yGLTEX_png2tex       (cchar *a_filename)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;             /* simple return code             */
   /*---(header)-------------------------*/
   URG_VERB   printf ("\nPNG_LOAD ()\n");
   /*---(open png file)------------------*/
   if (rc == 0)  rc = yGLTEX__png_open     (a_filename);
   if (rc == 0)  rc = yGLTEX__png_header   ();
   if (rc == 0)  rc = yGLTEX__png_attrib   ();
   if (rc == 0)  rc = yGLTEX__png_read     ();
   if (rc == 0)  rc = yGLTEX__png_tex      ();
   yGLTEX__png_close    ();
   URG_VERB   printf("   - texture   : %d\n", s_tex);
   /*---(complete)-----------------------*/
   return s_tex;
}


/*============================----end-of-source---============================*/
