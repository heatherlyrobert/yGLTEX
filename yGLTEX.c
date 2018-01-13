/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char        yGLTEX_ver     [500];

char*      /* ---- : return library versioning information -------------------*/
yGLTEX_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strlcpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strlcpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 15);
#else
   strlcpy (t, "[unknown    ]", 15);
#endif
   snprintf (yGLTEX_ver, 100, "%s   %s : %s", t, YGLTEX_VER_NUM, YGLTEX_VER_TXT);
   return yGLTEX_ver;
}

char
yGLTEX_init          (void)
{
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_senter  (__FUNCTION__);
   /*---(color)--------------------------*/
   DEBUG_YGLTEX    yLOG_snote   ("color");
   glClearColor    (0.50f, 0.50f, 0.50f, 1.00f);
   glClearDepth    (1.00f);
   /*---(textures)-----------------------*/
   DEBUG_YGLTEX    yLOG_snote   ("texture");
   glShadeModel    (GL_SMOOTH);
   glEnable        (GL_TEXTURE_2D);    /* NEW */
   /*---(blending)-----------------------*/
   DEBUG_YGLTEX    yLOG_snote   ("blending");
   glEnable        (GL_DEPTH_TEST);
   glEnable        (GL_ALPHA_TEST);
   glEnable        (GL_BLEND);
   glAlphaFunc     (GL_GEQUAL, 0.0125);
   glBlendFunc     (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   /*---(anti-aliasing)------------------*/
   DEBUG_YGLTEX    yLOG_snote   ("antialias" );
   glHint          (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glPolygonMode   (GL_FRONT_AND_BACK, GL_FILL);
   glEnable        (GL_POLYGON_SMOOTH);
   glHint          (GL_POLYGON_SMOOTH_HINT, GL_NICEST);
   /*---(simple defaulting)--------------*/
   DEBUG_YGLTEX    yLOG_snote   ("defaults" );
   glLineWidth     (0.50f);
   glPointSize     (2.00f);
   /*---(flush)--------------------------*/
   DEBUG_YGLTEX    yLOG_snote   ("flush" );
   glFlush         ();
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*--> create a new texture ------------------[ leaf-- [ ------ ]-*/
yGLTEX_new         (uint *a_tex, uint *a_fbo, uint *a_depth, cint a_wide, cint a_tall)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(generate fbo)-------------------*/
   DEBUG_YGLTEX    yLOG_point   ("&a_fbo"    , a_fbo);
   --rce;  if (a_fbo == NULL) {
      DEBUG_YGLTEX    yLOG_note    ("can not be null");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   glGenFramebuffersEXT         (1, a_fbo);
   DEBUG_YGLTEX    yLOG_value   ("a_fbo"     , *a_fbo);
   /*---(generate texture)---------------*/
   DEBUG_YGLTEX    yLOG_point   ("&a_tex"    , a_tex);
   --rce;  if (a_tex == NULL) {
      DEBUG_YGLTEX    yLOG_note    ("can not be null");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   glGenTextures                (1, a_tex);
   DEBUG_YGLTEX    yLOG_value   ("a_tex"     , *a_tex);
   /*---(generate depth)-----------------*/
   DEBUG_YGLTEX    yLOG_point   ("&a_depth"  , a_depth);
   --rce;  if (a_depth == NULL) {
      DEBUG_YGLTEX    yLOG_note    ("can not be null");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   glGenRenderbuffersEXT        (1, a_depth);
   DEBUG_YGLTEX    yLOG_value   ("a_depth"   , *a_depth);
   /*---(bind)---------------------------*/
   DEBUG_YGLTEX    yLOG_info    ("bind"      , "a_fbo framebuffer and a_tex texture");
   glBindFramebufferEXT         (GL_FRAMEBUFFER_EXT,  *a_fbo);
   glBindTexture                (GL_TEXTURE_2D,       *a_tex);
   /*---(settings)-----------------------*/
   DEBUG_YGLTEX    yLOG_info    ("settings"  , "filters, wraps, and mipmaps");
   glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexEnvi                    (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
   glTexParameteri              (GL_TEXTURE_2D,  GL_GENERATE_MIPMAP, GL_TRUE);
   /*---(copy)---------------------------*/
   DEBUG_YGLTEX    yLOG_info    ("copy"      , "glTexImage2D and Framebuffer");
   glTexImage2D                 (GL_TEXTURE_2D, 0, GL_RGBA, a_wide, a_tall, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
   glFramebufferTexture2DEXT    (GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, *a_tex, 0);
   /*---(depth)--------------------------*/
   DEBUG_YGLTEX    yLOG_info    ("bind"      , "a_depth depth buffer");
   glBindRenderbufferEXT        (GL_RENDERBUFFER_EXT, *a_depth);
   glRenderbufferStorageEXT     (GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, a_wide, a_tall);
   glFramebufferRenderbufferEXT (GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, *a_depth);
   /*---(unbind)-------------------------*/
   DEBUG_YGLTEX    yLOG_info    ("unbind"    , "a_fbo framebuffer");
   glBindFramebufferEXT         (GL_FRAMEBUFFER_EXT, 0);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> free an existing texture --------------[ leaf-- [ ------ ]-*/
yGLTEX_free        (uint *a_tex, uint *a_fbo, uint *a_depth)
{
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_senter  (__FUNCTION__);
   /*---(generate)-----------------------*/
   glDeleteTextures             (1, a_tex);
   DEBUG_YGLTEX    yLOG_svalue  ("a_tex"     , *a_tex);
   glDeleteRenderbuffersEXT     (1, a_depth);
   DEBUG_YGLTEX    yLOG_svalue  ("a_depth"   , *a_depth);
   glDeleteFramebuffersEXT      (1, a_fbo);
   DEBUG_YGLTEX    yLOG_svalue  ("a_fbo"     , *a_fbo);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*--> set-up drawing window -----------------[ ------ [ ------ ]-*/
yGLTEX_draw_start  (cuint a_fbo, cchar a_pos, cint a_wide, cint a_tall, cfloat a_scale)
{
   /*---(locals)-----------+-----------+-*/
   float     x_wide        =  0.0;
   float     x_tall        =  0.0;
   float     x_top         =  0.0;
   float     x_bot         =  0.0;
   float     x_lef         =  0.0;
   float     x_rig         =  0.0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_value   ("a_pos"     , a_pos);
   /*---(scaling)------------------------*/
   x_wide    = a_wide / a_scale;
   x_tall    = a_tall / a_scale;
   /*---(vertical setup)-----------------*/
   switch (a_pos) {
   case  YGLTEX_GREGG  :
      x_top =  125.0;
      x_bot = x_top - x_tall;
      break;
   case  YGLTEX_TOPLEF : case  YGLTEX_TOPCEN : case  YGLTEX_TOPRIG :
      x_top =   0.0;
      x_bot = -(x_tall);
      break;
   case  YGLTEX_MIDLEF : case  YGLTEX_MIDRIG : case  YGLTEX_MIDCEN :
      x_top =  (x_tall / 2.0);
      x_bot = -(x_tall / 2.0);
      break;
   case  YGLTEX_BOTLEF : case  YGLTEX_BOTCEN : case  YGLTEX_BOTRIG : default :
      x_top =  (x_tall);
      x_bot =   0.0;
      break;
   }
   DEBUG_YGLTEX    yLOG_value   ("x_top"     , x_top);
   DEBUG_YGLTEX    yLOG_value   ("x_bot"     , x_bot);
   /*---(setup)--------------------------*/
   switch (a_pos) {
   case  YGLTEX_GREGG  :
      x_lef = -125.0;
      x_rig = x_lef + x_wide;
      break;
   case  YGLTEX_TOPRIG : case  YGLTEX_MIDRIG : case  YGLTEX_BOTRIG :
      x_rig =   0.0;
      x_lef = -(x_wide);
      break;
   case  YGLTEX_TOPCEN : case  YGLTEX_MIDCEN : case  YGLTEX_BOTCEN :
      x_rig =  (x_wide / 2.0);
      x_lef = -(x_wide / 2.0);
      break;
   case  YGLTEX_TOPLEF : case  YGLTEX_MIDLEF : case  YGLTEX_BOTLEF : default :
      x_rig =  (x_wide);
      x_lef =   0.0;
      break;
   }
   DEBUG_YGLTEX    yLOG_value   ("x_rig"     , x_rig);
   DEBUG_YGLTEX    yLOG_value   ("x_lef"     , x_lef);
   /*---(setup)--------------------------*/
   DEBUG_YGLTEX    yLOG_note    ("setup viewport");
   glViewport            (0.0, 0.0, a_wide, a_tall);
   glMatrixMode          (GL_PROJECTION);
   glLoadIdentity        ();
   glOrtho               (x_lef, x_rig, x_bot, x_top, -500.0,  500.0);
   /*---(bind)---------------------------*/
   glMatrixMode          (GL_MODELVIEW);
   DEBUG_YGLTEX    yLOG_note    ("bind and clear");
   glBindTexture         (GL_TEXTURE_2D, 0);
   glBindFramebufferEXT  (GL_FRAMEBUFFER_EXT,  a_fbo);
   glClear               (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> free an existing texture --------------[ leaf-- [ ------ ]-*/
yGLTEX_draw_end    (cuint a_tex)
{
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_senter  (__FUNCTION__);
   /*---(create mipmaps)-----------------*/
   DEBUG_YGLTEX    yLOG_snote   ("unbind fbo");
   glBindFramebufferEXT  (GL_FRAMEBUFFER_EXT, 0);
   DEBUG_YGLTEX    yLOG_snote   ("bind tex");
   glBindTexture         (GL_TEXTURE_2D, a_tex);
   DEBUG_YGLTEX    yLOG_snote   ("mipmaps");
   glGenerateMipmapEXT   (GL_TEXTURE_2D);
   DEBUG_YGLTEX    yLOG_snote   ("unbind tex");
   glBindTexture         (GL_TEXTURE_2D, 0);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_sexit   (__FUNCTION__);
   /*---(complete)-----------------------*/
   return 0;
}

char
yGLTEX_get_size      (int *a_wide, int *a_tall)
{
   if (a_wide != NULL)  *a_wide = s_width;
   if (a_tall != NULL)  *a_tall = s_height;
   return 0;
}

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
   DEBUG_YGLTEX    yLOG_value   ("rc"        , rc);
   if (rc < 0) return rc;
   DEBUG_YGLTEX    yLOG_value   ("s_tex"     , s_tex);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return s_tex;
}

char
yGLTEX_scr2png       (cchar *a_name, cint a_width, cint a_height)
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
