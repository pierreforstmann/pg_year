/*-------------------------------------------------------------------------
 *  
 * pg_year is a PostgreSQL extension implementing the YEAR data type. 
 * 
 * This program is open source, licensed under the PostgreSQL license.
 * For license terms, see the LICENSE file.
 *          
 * Copyright (c) 2023, Pierre Forstmann.
 *            
 *-------------------------------------------------------------------------
*/
#include "postgres.h"

#include "catalog/pg_type.h"
#include "utils/builtins.h"
#include "access/hash.h"

PG_MODULE_MAGIC;

/*---- Function declarations ----*/

void		_PG_init(void);
void		_PG_fini(void);

PG_FUNCTION_INFO_V1(year_in);
PG_FUNCTION_INFO_V1(year_out);
PG_FUNCTION_INFO_V1(year_add);
PG_FUNCTION_INFO_V1(year_minus);
/*     -------------------      */
PG_FUNCTION_INFO_V1(year_eq);
PG_FUNCTION_INFO_V1(year_ne);
PG_FUNCTION_INFO_V1(year_lt);
PG_FUNCTION_INFO_V1(year_le);
PG_FUNCTION_INFO_V1(year_gt);
PG_FUNCTION_INFO_V1(year_ge);
PG_FUNCTION_INFO_V1(year_cmp);
PG_FUNCTION_INFO_V1(hash_year);


/*---- Global variable declarations ----*/

/*
 * Module load callback
 */
void
_PG_init(void)
{


	elog(DEBUG5, "pg_year:_PG_init():entry");

	/* get the configuration */

	/* currently no GUC parameter */

	elog(DEBUG5, "pg_year:_PG_init():exit");
}

/*
 *  Module unload callback
 */
void
_PG_fini(void)
{
	elog(DEBUG5, "pg_year:_PG_fini():entry");

	elog(DEBUG5, "pg_year:_PG_fini():exit");
}
/* --- ---- */


Datum year_in(PG_FUNCTION_ARGS)
{
	uint16 result;

	char *str = PG_GETARG_CSTRING(0);
	result = strtol(str, NULL, 10);
	if (result < 1901) {
	      ereport(ERROR,
               (
                errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
                errmsg("year cannot be lower than 1901"),
                errdetail("value %d is lower than 1901", result),
                errhint("make it greater or equal than 1901")
               )
	      );
	} else if (result > 2155) {
	      ereport(ERROR,
               (
                errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
                errmsg("year cannot be greater than 2155"),
                errdetail("value %d is greater than 2155", result),
                errhint("make it lower or equal than 2155")
               )
	      );
	}
	PG_RETURN_UINT16((result - 1901));
}

Datum year_out(PG_FUNCTION_ARGS)
{
	uint16 arg = (uint8)PG_GETARG_UINT16(0);
	char *buffer = palloc(5 * sizeof(char));
	arg = arg + 1901;
	sprintf(buffer, "%d", arg);

	PG_RETURN_CSTRING(buffer);
}


Datum year_add(PG_FUNCTION_ARGS)
{
	uint32	result;
	uint8 	arg1 = PG_GETARG_UINT16(0);
	uint8 	arg2 = PG_GETARG_UINT16(1);

	result = arg1 + 1901 + arg2; 
	if (result > 2155) {
	      ereport(ERROR,
               (
                errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
                errmsg("year cannot be greater than 2155"),
                errdetail("value %d is greater than 2155", result),
                errhint("make it lower or equal than 2155")
               )
	      );
	}
	
	result = result - 1901;
	PG_RETURN_UINT16((uint8)result);
}

Datum year_minus(PG_FUNCTION_ARGS)
{
	uint32	result;
	uint8 	arg1 = PG_GETARG_UINT16(0);
	uint8 	arg2 = PG_GETARG_UINT16(1);
	
	result = arg1 + 1901 - arg2; 
	if (result < 1901) {
	      ereport(ERROR,
               (
                errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
                errmsg("year cannot be lower than 1901"),
                errdetail("value %d is lower than 1901", result),
                errhint("make it greater or equal than 1901")
               )
	      );
	} else if (result > 2155) {
	      ereport(ERROR,
               (
                errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
                errmsg("year cannot be greater than 2155"),
                errdetail("value %d is greater than 2155", result),
                errhint("make it lower or equal than 2155")
               )
	      );
	}

	result = result - 1901;
	PG_RETURN_UINT16((uint8)result);
}

Datum year_eq(PG_FUNCTION_ARGS)
{
	uint8	arg1 = PG_GETARG_UINT16(0);
	uint8	arg2 = PG_GETARG_UINT16(1);

	PG_RETURN_BOOL(arg1 == arg2);
}

Datum year_ne(PG_FUNCTION_ARGS)
{
	uint8	arg1 = PG_GETARG_UINT16(0);
	uint8	arg2 = PG_GETARG_UINT16(1);

	PG_RETURN_BOOL(arg1 != arg2);
}

Datum year_lt(PG_FUNCTION_ARGS)
{
	uint8	arg1 = PG_GETARG_UINT16(0);
	uint8	arg2 = PG_GETARG_UINT16(1);

	PG_RETURN_BOOL(arg1 < arg2);
}

Datum year_le(PG_FUNCTION_ARGS)
{
	uint8	arg1 = PG_GETARG_UINT16(0);
	uint8	arg2 = PG_GETARG_UINT16(1);

	PG_RETURN_BOOL(arg1 <= arg2);
}

Datum year_gt(PG_FUNCTION_ARGS)
{
	uint8	arg1 = PG_GETARG_UINT16(0);
	uint8	arg2 = PG_GETARG_UINT16(1);

	PG_RETURN_BOOL(arg1 > arg2);
}

Datum year_ge(PG_FUNCTION_ARGS)
{
	uint8	arg1 = PG_GETARG_UINT16(0);
	uint8	arg2 = PG_GETARG_UINT16(1);

	PG_RETURN_BOOL(arg1 >= arg2);
}

Datum year_cmp(PG_FUNCTION_ARGS)
{
	uint8	arg1 = PG_GETARG_UINT16(0);
	uint8	arg2 = PG_GETARG_UINT16(1);

	PG_RETURN_UINT16(arg1 - arg2);
}


Datum hash_year(PG_FUNCTION_ARGS)
{

	return(hash_uint32((uint32)PG_GETARG_UINT16(0)));
}
