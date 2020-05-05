#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "string.h"
#include <stdio.h>
#include "executor/spi.h"       /* this is what you need to work with SPI */

PG_MODULE_MAGIC;


/* luhn.c - Luhn algorithm test program */
int check_number(const char *number);
int calc_digit(const char *number);
int main(int argc, char **argv);

#include <stdio.h>

int check_number(const char *number)
{
    int i, sum, ch, num, twoup, len;

    len = strlen(number);
    sum = 0;
    twoup = 0;
    for (i = len - 1; i >= 0; --i) {
        ch = number[i];
        num = (ch >= '0' && ch <= '9') ? ch - '0' : 0;
        if (twoup) {
            num += num;
            if (num > 9) num = (num % 10) + 1;
        }
        sum += num;
        ++twoup; 
        twoup = twoup & 1;
    }
    sum = 10 - (sum % 10);
    if (sum == 10) sum = 0;
    return (sum == 0) ? 1 : 0;
}

int calc_digit(const char *number)
{
    int i, sum, ch, num, twoup, len;

    len = strlen(number);
    sum = 0;
    twoup = 1;
    for (i = len - 1; i >= 0; --i) {
        ch = number[i];
        num = (ch >= '0' && ch <= '9') ? ch - '0' : 0;
        if (twoup) {
            num += num;
            if (num > 9) num = (num % 10) + 1;
        }
        sum += num;
        ++twoup;
        twoup = twoup & 1;
    }
    sum = 10 - (sum % 10);
    if (sum == 10) sum = 0;
    return sum;
}

int main(int argc, char **argv)
{
    int ok, check_digit;
    char *number;

    if (argc <= 1) {
        printf("usage: %s number ...\n", *argv);
        exit(1);
    }
    while (--argc) {
        ++argv;
        number = *argv;
        ok = check_number(number);
        check_digit = calc_digit(number);
        printf("%s %s check\n", number, (ok) ? "passes" : "fails");
        printf("%s needs check-digit '%d'\n", number, check_digit);
    }
    exit(0);
}

PG_FUNCTION_INFO_V1(isluhn);
Datum isluhn(PG_FUNCTION_ARGS) {
  const char *number;
  int32 result;
  bool b0 = PG_ARGISNULL(0);
  if (b0) {
    PG_RETURN_NULL();
  }
  number = text_to_cstring(PG_GETARG_TEXT_P(0));
  result = check_number(number);
  PG_RETURN_INT32(result);
}


PG_FUNCTION_INFO_V1(luhnval);
Datum luhnval(PG_FUNCTION_ARGS) {
  const char *number;
  int32 result;
  bool b0 = PG_ARGISNULL(0);
  if (b0) {
    PG_RETURN_NULL();
  }
  number = text_to_cstring(PG_GETARG_TEXT_P(0));
  result = calc_digit(number);
  PG_RETURN_INT32(result);
}

PG_FUNCTION_INFO_V1(mapcount);
Datum mapcount(PG_FUNCTION_ARGS) {
  int ret, i;
  int32 i32;
  char sql[60];
  const char *tname;
  bool isnull;
/*  elog(INFO, "start mapcount()");*/
  isnull = PG_ARGISNULL(0);
  if (isnull) {
    PG_RETURN_NULL();
  }

    /* connect to SPI manager */
    if ((ret = SPI_connect()) < 0)
        elog(ERROR, "SPI_connect returned %d", ret);

    /* get number of rows in table */
    tname = text_to_cstring(PG_GETARG_TEXT_P(0));
    sprintf(sql, "select count(*) from %s", tname);
/*    elog(INFO, "tname=%s", tname);*/
    ret = SPI_exec(sql, 0);

    if (ret < 0)
        elog(ERROR, "SPI_exec returned %d", ret);

    /* count(*) returns int8, so be careful to convert */
    i = DatumGetInt64(SPI_getbinval(SPI_tuptable->vals[0],
                                    SPI_tuptable->tupdesc,
                                    1,
                                    &isnull));

    elog (INFO, "there are %d rows in %s", i, tname);
    i32 = i;

    SPI_finish();
    PG_RETURN_INT32(i32);

}
