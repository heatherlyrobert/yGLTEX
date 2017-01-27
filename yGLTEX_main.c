/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"


GLuint             /* PURPOSE : make a png image into a texture --------------*/
yGLTEX_png2tex       (cchar *a_name)
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
   if (rc == 0)  rc = yGLTEX__read_tex     ();
   yGLTEX__file_close    ();
   DEBUG_YGLTEX    yLOG_point   ("s_tex"     , s_tex);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return s_tex;
}

char
yGLTEX_scr2png       (cchar *a_name, int a_width, int a_height)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;             /* simple return code             */
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(open png file)------------------*/
   if (rc == 0)  rc = yGLTEX__file_open    (a_name, 'w');
   if (rc == 0)  rc = yGLTEX__save_header  ();
   if (rc == 0)  rc = yGLTEX__save_attrib  (a_width, a_height);
   if (rc == 0)  rc = yGLTEX__file_alloc   ();
   if (rc == 0)  rc = yGLTEX__save_image   ();
   yGLTEX__file_close    ();
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}


/*============================----end-of-source---============================*/
