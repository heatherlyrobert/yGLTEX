/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"


FILE          *s_file      = NULL;
png_structp    s_png;
png_infop      s_info;
int            s_width     = 0;
int            s_height    = 0;
png_byte      *s_image     = NULL;;
png_bytep     *s_rows      = NULL;;
int            s_rowbyte   = 0;
GLuint         s_tex       = 0;;


char               /* PURPOSE : make a png image into a texture --------------*/
yGLTEX__file_open    (const char *a_name, const char a_mode)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         x_len       = 0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("a_name"   , "texture name can not be null");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   x_len = strlen (a_name);
   DEBUG_YGLTEX    yLOG_point   ("x_len"     , x_len);
   --rce;  if (x_len < 5) {
      DEBUG_YGLTEX    yLOG_warn    ("a_name"   , "texture name is too short ( < 5 chars)");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_info    ("a_name"    , a_name);
   /*---(open png file)------------------*/
   DEBUG_YGLTEX    yLOG_char    ("a_mode"    , a_mode);
   switch (a_mode) {
   case 'r' :
      DEBUG_YGLTEX    yLOG_note    ("selected read-binary mode");
      s_file = fopen (a_name, "rb");
      break;
   case 'w' :
      DEBUG_YGLTEX    yLOG_note    ("selected write-binary mode");
      s_file = fopen (a_name, "wb");
      break;
   default  :
      DEBUG_YGLTEX    yLOG_warn    ("a_mode"   , "open mode must be 'r' or 'w'");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
      break;
   }
   DEBUG_YGLTEX    yLOG_point   ("s_file"    , s_file);
   --rce;  if (s_file == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("s_file"   , "texture file could not be openned");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_note    ("file open and confirmed");
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char               /* PURPOSE : make a png image into a texture --------------*/
yGLTEX__file_close   (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(destroy pointers)---------------*/
   DEBUG_YGLTEX    yLOG_note    ("destroying png pointers");
   png_destroy_read_struct (&s_png, &s_info, NULL);
   /*---(clear memory)-------------------*/
   DEBUG_YGLTEX    yLOG_point   ("s_image"   , s_image);
   --rce;  if (s_image != NULL) {
      DEBUG_YGLTEX    yLOG_note    ("free and null pointer");
      free     (s_image);
      s_image = NULL;
   }
   DEBUG_YGLTEX    yLOG_point   ("s_rows"    , s_rows);
   --rce;  if (s_rows  != NULL) {
      DEBUG_YGLTEX    yLOG_note    ("free and null pointer");
      free     (s_rows);
      s_rows  = NULL;
   }
   /*---(close file)---------------------*/
   DEBUG_YGLTEX    yLOG_point   ("s_file"    , s_file);
   --rce;  if (s_file  != NULL) {
      DEBUG_YGLTEX    yLOG_note    ("close and null pointer");
      fclose   (s_file);
      s_file  = NULL;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yGLTEX__file_alloc   (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   /*---(allocate image)-----------------*/
   s_image = (unsigned char*) malloc (sizeof (png_byte) * s_rowbyte * s_height);
   --rce;  if (!s_image) {
      URG_VERB   printf("s_image error\n");
      yGLTEX__file_close ();
      return  rce;
   }
   /*---(row pointers)-------------------*/
   s_rows = (png_bytepp)  malloc (sizeof (png_bytep) * s_height);
   --rce;  if (s_rows == NULL) {
      URG_VERB   printf("s_rows error\n");
      yGLTEX__file_close ();
      return  rce;
   }
   URG_VERB   printf("   - row pointers are good\n");
   uint i, j;
   for (i = 0; i < s_height; ++i) {
      s_rows [s_height - 1 - i] = s_image + (i * s_rowbyte);
   }
   return 0;
}



/*============================----end-of-source---============================*/
