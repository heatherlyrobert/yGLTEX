/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"



char
ygltex_image_alloc   (int a_wide, int a_tall, int a_rowbyte, png_byte **r_image, png_bytep **r_rows)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         c           =   0;
   int         i           =   0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_complex ("a_args"    , "%4d, %4d, %5d", a_wide, a_tall, a_rowbyte);
   DEBUG_YGLTEX    yLOG_value   ("png_byte"  , sizeof (png_byte));
   DEBUG_YGLTEX    yLOG_value   ("png_bytep" , sizeof (png_bytep));
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("r_image"   , r_image);
   --rce;  if (r_image  == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("*r_image"  , *r_image);
   --rce;  if (*r_image != NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("r_rows"    , r_rows);
   --rce;  if (r_rows   == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("*r_rows"   , *r_rows);
   --rce;  if (*r_rows  != NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(alloc image)--------------------*/
   DEBUG_YGLTEX    yLOG_value   ("image"     , sizeof (png_byte) * a_rowbyte * a_tall);
   *r_image = (png_byte *) malloc (sizeof (png_byte) * a_rowbyte * a_tall);
   DEBUG_YGLTEX    yLOG_point   ("*r_image"  , *r_image);
   --rce;  if (*r_image == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("r_image could not allocate memory");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(cleanse image space)------------*/
   c = a_rowbyte * a_tall;
   for (i = 0; i < c; ++i)  (*r_image) [i] = 0;
   /*---(alloc row pointers)-------------*/
   DEBUG_YGLTEX    yLOG_value   ("rows"      , sizeof (png_bytep) * a_tall);
   *r_rows  = (png_bytep *) malloc (sizeof (png_bytep *) * a_tall);
   DEBUG_YGLTEX    yLOG_point   ("*r_rows"   , *r_rows);
   --rce;  if (*r_rows  == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("r_rows could not allocate memory");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(assign row pointers)------------*/
   DEBUG_YGLTEX    yLOG_note    ("assign r_rows to image");
   for (i = 0; i < a_tall; ++i) {
      (*r_rows) [a_tall - 1 - i] = *r_image + (i * a_rowbyte);
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_image_free       (png_byte **r_image, png_bytep **r_rows)
{
   char        rce =  -10;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("r_image"   , r_image);
   --rce;  if (r_image  == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("*r_image"  , *r_image);
   --rce;  if (*r_image == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("r_rows"    , r_rows);
   --rce;  if (r_rows   == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("*r_rows"   , *r_rows);
   --rce;  if (*r_rows  == NULL) {
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(clear row pointers)-------------*/
   DEBUG_YGLTEX    yLOG_note    ("free and null pointer");
   free     (*r_rows);
   *r_rows  = NULL;
   DEBUG_YGLTEX    yLOG_point   ("*r_rows"   , *r_rows);
   /*---(clear overall image)------------*/
   DEBUG_YGLTEX    yLOG_note    ("free and null pointer");
   free     (*r_image);
   *r_image = NULL;
   DEBUG_YGLTEX    yLOG_point   ("*r_image"  , *r_image);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}



