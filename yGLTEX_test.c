/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"



char           unit_answer [LEN_FULL];

char       /*----: set up program urgents/debugging --------------------------*/
ygltex__unit_quiet      (void)
{
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ygltex__unit_loud       (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yGLTEX_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_by_name  ("ygltex"       , YURG_ON);
   DEBUG_YGLTEX  yLOG_info     ("yGLTEX"    , yGLTEX_version   ());
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ygltex__unit_end        (void)
{
   DEBUG_YGLTEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX  yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}
