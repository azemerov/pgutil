#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "string.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(nvl);
Datum nvl(PG_FUNCTION_ARGS) {
  bool b0 = PG_ARGISNULL(0);
  bool b1 = PG_ARGISNULL(1);
  if (b0) {
    if (b1) PG_RETURN_NULL();
    else PG_RETURN_TEXT_P(PG_GETARG_TEXT_P(1));
  }
  PG_RETURN_TEXT_P(PG_GETARG_TEXT_P(0));
  /*
  text* arg1 = PG_GETARG_TEXT_P(0);
  text *arg2 = PG_GETARG_TEXT_P(1);
  if (PG_ARGISNULL(0)) PG_RETURN_TEXT_P(arg2); else PG_RETURN_TEXT_P(arg1);
*/
/*  if (arg1->length==0) PG_RETURN_TEXT_P(arg2); else PG_RETURN_TEXT_P(arg1);
*/
  PG_RETURN_TEXT_P(PG_GETARG_TEXT_P(1));
}

/*PG_FUNCTION_INFO_V1(decode);
Datum decode(PG_FUNCTION_ARGS) {
 short nargs = PG_NARGS();
 short i;
 int32 v1 = PG_GETARG_INT32(0);
 for (i=1; i<nargs; i++, i++) {
   if (PG_GETARG_INT32(i) == v1) PG_RETURN_INT32(PG_GETARG_INT32(i+1)); 
 }
 PG_RETURN_NULL();
}
*/
