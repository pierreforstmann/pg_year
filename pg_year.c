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

#include "utils/guc.h"
#include "utils/fmgrprotos.h"
#include "fmgr.h"
#include "funcapi.h"

PG_MODULE_MAGIC;

/*---- Function declarations ----*/

void		_PG_init(void);
void		_PG_fini(void);

PG_FUNCTION_INFO_V1(year_in);
PG_FUNCTION_INFO_V1(year_out);

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
	short result;

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
	PG_RETURN_INT16((result - 1901));
}


Datum year_out(PG_FUNCTION_ARGS)
{
	int16 arg = PG_GETARG_INT16(0);
	char *buffer = palloc(5 * sizeof(char));
	arg = arg + 1901;
	sprintf(buffer, "%d", arg);

	PG_RETURN_CSTRING(buffer);
}



