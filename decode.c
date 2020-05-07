#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "string.h"

PG_MODULE_MAGIC;
/*
PG_FUNCTION_INFO_V1(idecode);
Datum idecode(PG_FUNCTION_ARGS) {
 short nargs = PG_NARGS();
 short i;
 int32 v1 = PG_GETARG_INT32(0);
 for (i=1; i<nargs; i++, i++) {
   if (PG_GETARG_INT32(i) == v1) PG_RETURN_INT32(PG_GETARG_INT32(i+1)); 
 }
 PG_RETURN_NULL();
}
*/
PG_FUNCTION_INFO_V1(sdecode);
Datum sdecode(PG_FUNCTION_ARGS) {
 int i;
 text *v1;
 const char *p1;
 short nargs = PG_NARGS();
 elog(NOTICE, "nargs=%d", nargs);
 v1 = PG_GETARG_TEXT_P(0);
 p1 = text_to_cstring(v1);
 elog(NOTICE, "VAL=%s", p1);
 for (i=1; i<nargs; i++, i++) {
   const char *p2 = text_to_cstring(PG_GETARG_TEXT_P(i));
   elog(NOTICE, "CMP=%s", p2);
   if (strcmp(p2,p1)==0) PG_RETURN_TEXT_P(PG_GETARG_TEXT_P(i+1));
   PG_RETURN_TEXT_P(cstring_to_text("Xa-Xa"));
 }
 
 elog(NOTICE, "Rturn NULL");
 PG_RETURN_NULL();
}

