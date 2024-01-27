/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"



static  char  s_anchor = 0;

static  float s_lef    = 0;
static  float s_rig    = 0;
static  float s_wide   = 0;

static  float s_bot    = 0;
static  float s_top    = 0;
static  float s_tall   = 0;



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
   ystrlcpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   ystrlcpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 15);
#else
   ystrlcpy (t, "[unknown    ]", 15);
#endif
   snprintf (yGLTEX_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yGLTEX_ver;
}

char
yGLTEX_config        (void)
{
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_senter  (__FUNCTION__);
   /*---(color)--------------------------*/
   DEBUG_YGLTEX    yLOG_snote   ("color");
   glClearColor    (1.00f, 1.00f, 1.00f, 1.00f);
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
ygltex__new        (GLuint *a_tex, GLuint *a_fbo, GLuint *a_depth, cint a_wide, cint a_tall, char a_type)
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
   --rce;  if ((int) *a_fbo < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(generate texture)---------------*/
   DEBUG_YGLTEX    yLOG_point   ("&a_tex"    , a_tex);
   --rce;  if (a_tex == NULL) {
      DEBUG_YGLTEX    yLOG_note    ("can not be null");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   glGenTextures                (1, a_tex);
   DEBUG_YGLTEX    yLOG_value   ("a_tex"     , *a_tex);
   --rce;  if ((int) *a_tex < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(generate depth)-----------------*/
   if (a_type == 'n') {
      DEBUG_YGLTEX    yLOG_point   ("&a_depth"  , a_depth);
      --rce;  if (a_depth == NULL) {
         DEBUG_YGLTEX    yLOG_note    ("can not be null");
         DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      glGenRenderbuffersEXT        (1, a_depth);
      DEBUG_YGLTEX    yLOG_value   ("a_depth"   , *a_depth);
      --rce;  if ((int) *a_depth < 0) {
         DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(bind)---------------------------*/
   DEBUG_YGLTEX    yLOG_info    ("bind"      , "a_fbo framebuffer and a_tex texture");
   glBindFramebufferEXT  (GL_FRAMEBUFFER_EXT,  *a_fbo);
   glBindTexture    (GL_TEXTURE_2D,       *a_tex);
   /*---(settings)-----------------------*/
   DEBUG_YGLTEX    yLOG_info    ("settings"  , "filters, wraps, and mipmaps");
   glTexParameteri  (GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri  (GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   /*---(select wrapping to not fuzz edges)-----*/
   glTexParameteri  (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri  (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   if (a_type == 'n') {
      glTexEnvi     (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
   } else {
      glTexEnvi     (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   }
   glTexParameteri  (GL_TEXTURE_2D,  GL_GENERATE_MIPMAP, GL_TRUE);
   /*---(copy)---------------------------*/
   DEBUG_YGLTEX    yLOG_info    ("copy"      , "glTexImage2D and Framebuffer");
   if (a_type == 'n') {
      glTexImage2D  (GL_TEXTURE_2D, 0, GL_RGBA , a_wide, a_tall, 0, GL_RGBA , GL_UNSIGNED_BYTE, 0);
      glFramebufferTexture2DEXT    (GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, *a_tex, 0);
   } else {
      glTexImage2D  (GL_TEXTURE_2D, 0, GL_ALPHA, a_wide, a_tall, 0, GL_ALPHA, GL_UNSIGNED_BYTE, *a_tex);
   }
   /*---(depth)--------------------------*/
   if (a_type == 'n') {
      DEBUG_YGLTEX    yLOG_info    ("bind"      , "a_depth depth buffer");
      glBindRenderbufferEXT        (GL_RENDERBUFFER_EXT, *a_depth);
      glRenderbufferStorageEXT     (GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, a_wide, a_tall);
      glFramebufferRenderbufferEXT (GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, *a_depth);
   }
   /*---(unbind)-------------------------*/
   DEBUG_YGLTEX    yLOG_info    ("unbind"    , "a_fbo framebuffer");
   glBindFramebufferEXT         (GL_FRAMEBUFFER_EXT, 0);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> create a new texture ------------------[ leaf-- [ ------ ]-*/
yGLTEX_new         (GLuint *a_tex, GLuint *a_fbo, GLuint *a_depth, cint a_wide, cint a_tall)
{
   return ygltex__new (a_tex, a_fbo, a_depth, a_wide, a_tall, 'n');
}

char         /*--> free an existing texture --------------[ leaf-- [ ------ ]-*/
ygltex__free       (GLuint *a_tex, GLuint *a_fbo, GLuint *a_depth, char a_type)
{
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_senter  (__FUNCTION__);
   /*---(generate)-----------------------*/
   glDeleteTextures             (1, a_tex);
   DEBUG_YGLTEX    yLOG_svalue  ("a_tex"     , *a_tex);
   if (a_type == 'n') {
      glDeleteRenderbuffersEXT     (1, a_depth);
      DEBUG_YGLTEX    yLOG_svalue  ("a_depth"   , *a_depth);
   }
   glDeleteFramebuffersEXT      (1, a_fbo);
   DEBUG_YGLTEX    yLOG_svalue  ("a_fbo"     , *a_fbo);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yGLTEX_free        (GLuint *a_tex, GLuint *a_fbo, GLuint *a_depth)
{
   return ygltex__free (a_tex, a_fbo, a_depth, 'n');
}

char         /*--> set-up drawing window -----------------[ ------ [ ------ ]-*/
yGLTEX_draw        (GLuint a_tex, GLuint a_fbo, cchar a_anchor, cint a_wide, cint a_tall, cfloat a_scale)
{
   char        rce         =   -10;
   int         x_status    =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_value   ("a_text"    , a_tex);
   DEBUG_YGLTEX    yLOG_value   ("a_fbo"     , a_fbo);
   DEBUG_YGLTEX    yLOG_value   ("a_anchor"  , a_anchor);
   /*---(scaling)------------------------*/
   s_wide    = a_wide / a_scale;
   s_tall    = a_tall / a_scale;
   /*---(vertical setup)-----------------*/
   switch (a_anchor) {
   case  YGLTEX_GREGG  :
      s_top =  125.0;
      s_bot = s_top - s_tall;
      break;
   case  YGLTEX_TOPLEF : case  YGLTEX_TOPCEN : case  YGLTEX_TOPRIG :
      s_top =   0.0;
      s_bot = -(s_tall);
      break;
   case  YGLTEX_MIDLEF : case  YGLTEX_MIDRIG : case  YGLTEX_MIDCEN :
      s_top =  (s_tall / 2.0);
      s_bot = -(s_tall / 2.0);
      break;
   case  YGLTEX_BOTLEF : case  YGLTEX_BOTCEN : case  YGLTEX_BOTRIG : default :
      s_top =  (s_tall);
      s_bot =   0.0;
      break;
   }
   DEBUG_YGLTEX    yLOG_value   ("s_bot"     , s_bot);
   DEBUG_YGLTEX    yLOG_value   ("s_top"     , s_top);
   /*---(horizontal setup)---------------*/
   switch (a_anchor) {
   case  YGLTEX_GREGG  :
      s_lef = -125.0;
      s_rig = s_lef + s_wide;
      break;
   case  YGLTEX_TOPRIG : case  YGLTEX_MIDRIG : case  YGLTEX_BOTRIG :
      s_rig =   0.0;
      s_lef = -(s_wide);
      break;
   case  YGLTEX_TOPCEN : case  YGLTEX_MIDCEN : case  YGLTEX_BOTCEN :
      s_rig =  (s_wide / 2.0);
      s_lef = -(s_wide / 2.0);
      break;
   case  YGLTEX_TOPLEF : case  YGLTEX_MIDLEF : case  YGLTEX_BOTLEF : default :
      s_rig =  (s_wide);
      s_lef =   0.0;
      break;
   }
   DEBUG_YGLTEX    yLOG_value   ("s_lef"     , s_lef);
   DEBUG_YGLTEX    yLOG_value   ("s_rig"     , s_rig);
   /*---(setup)--------------------------*/
   DEBUG_YGLTEX    yLOG_note    ("setup viewport");
   glViewport            (0.0, 0.0, a_wide, a_tall);
   glMatrixMode          (GL_PROJECTION);
   glLoadIdentity        ();
   glOrtho               (s_lef, s_rig, s_bot, s_top, -500.0,  500.0);
   /*---(bind)---------------------------*/
   glMatrixMode          (GL_MODELVIEW);
   DEBUG_YGLTEX    yLOG_note    ("bind and clear");
   glBindTexture         (GL_TEXTURE_2D, a_tex);
   glBindFramebufferEXT  (GL_FRAMEBUFFER_EXT,  a_fbo);
   glClear               (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   /*---(framebuffer ready)--------------*/
   x_status  = glCheckFramebufferStatus (GL_FRAMEBUFFER_EXT);
   DEBUG_YGLTEX    yLOG_value   ("x_status"  , x_status);
   switch (x_status) {
   case GL_FRAMEBUFFER_COMPLETE :
      DEBUG_YGLTEX    yLOG_note    ("framebuffer checks as complete");
      break;
   case GL_FRAMEBUFFER_UNDEFINED :
      DEBUG_YGLTEX    yLOG_note    ("framebuffer does not exist");
      break;
   case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT :
      DEBUG_YGLTEX    yLOG_note    ("one of the framebuffer attachment points is incomplete");
      break;
   case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT :
      DEBUG_YGLTEX    yLOG_note    ("framebuffer does not have at least one image attached");
      break;
   case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER :
      DEBUG_YGLTEX    yLOG_note    ("at least one color attachment is GL_NONE");
      break;
   case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER :
      DEBUG_YGLTEX    yLOG_note    ("read buffers do not match object types");
      break;
   case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE :
      DEBUG_YGLTEX    yLOG_note    ("value for render samples do not match for all textures");
      break;
   case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS :
      DEBUG_YGLTEX    yLOG_note    ("overall layering and attachment layering do not match");
      break;
   case GL_FRAMEBUFFER_UNSUPPORTED :
      DEBUG_YGLTEX    yLOG_note    ("combination of internal formats not supported/illegal");
      break;
   }
   if (x_status != GL_FRAMEBUFFER_COMPLETE) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(texture ready)------------------*/
   --rce;  if (!glIsTexture (a_tex)) {
      DEBUG_YGLTEX    yLOG_note    ("texture is not legal/valid");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_note    ("texture confirmed as bound");
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yGLTEX_bounds           (char *r_anchor, short *r_xmin, short *r_xmax, short *r_wide, short *r_ymin, short *r_ymax, short *r_tall)
{
   if (r_anchor != NULL)  *r_anchor = s_anchor;
   if (r_xmin   != NULL)  *r_xmin   = s_lef;
   if (r_xmax   != NULL)  *r_xmax   = s_rig;
   if (r_wide   != NULL)  *r_wide   = s_wide;
   if (r_ymin   != NULL)  *r_ymin   = s_bot;
   if (r_ymax   != NULL)  *r_ymax   = s_top;
   if (r_tall   != NULL)  *r_tall   = s_tall;
   return 0;
}

char         /*--> free an existing texture --------------[ leaf-- [ ------ ]-*/
yGLTEX_done        (GLuint a_tex)
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

uint               /* PURPOSE : make a png image into a texture --------------*/
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

uint               /* PURPOSE : make a png image into a texture --------------*/
yGLTEX_tile2tex      (cchar *a_name, void *e_title, void *e_header)
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
   if (rc == 0)  rc = yGLTEX__save_image   ('w');
   yGLTEX__file_close    ();
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yGLTEX_tex2png       (cchar *a_name, cint a_width, cint a_height)
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
   if (rc == 0)  rc = yGLTEX__save_image   ('t');
   yGLTEX__file_close    ();
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}


/*============================----end-of-source---============================*/
