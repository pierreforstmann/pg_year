-- pg_year--0.0.1.sql

CREATE TYPE year;


CREATE FUNCTION year_in(cstring)
RETURNS year 
AS '$libdir/pg_year'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION year_out(year)
RETURNS cstring 
AS '$libdir/pg_year'
LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE year (
  INPUT          = year_in,
  OUTPUT         = year_out,
  LIKE           = char,
  INTERNALLENGTH = 1,
  ALIGNMENT      = char,
  PASSEDBYVALUE,
  STORAGE        = PLAIN
);

CREATE FUNCTION year_add(year, int)
    RETURNS year 
    AS '$libdir/pg_year'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR + (
    leftarg = year,
    rightarg = int,
    function = year_add,
    commutator = +
);


CREATE FUNCTION year_minus(year, int)
    RETURNS year 
    AS '$libdir/pg_year'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR - (
    leftarg = year,
    rightarg = int,
    function = year_minus
);

CREATE CAST(int AS year)
WITH INOUT
AS IMPLICIT;

CREATE CAST(text AS year)
WITH INOUT
AS IMPLICIT;


CREATE FUNCTION year_eq(year, year)
RETURNS boolean LANGUAGE C IMMUTABLE AS '$libdir/pg_year';

CREATE FUNCTION year_ne(year, year)
RETURNS boolean LANGUAGE C IMMUTABLE AS '$libdir/pg_year';

CREATE FUNCTION year_lt(year, year)
RETURNS boolean LANGUAGE C IMMUTABLE AS '$libdir/pg_year';

CREATE FUNCTION year_le(year, year)
RETURNS boolean LANGUAGE C IMMUTABLE AS '$libdir/pg_year';

CREATE FUNCTION year_gt(year, year)
RETURNS boolean LANGUAGE C IMMUTABLE AS '$libdir/pg_year';

CREATE FUNCTION year_ge(year, year)
RETURNS boolean LANGUAGE C IMMUTABLE AS '$libdir/pg_year';

CREATE FUNCTION year_cmp(year, year)
RETURNS integer LANGUAGE C IMMUTABLE AS '$libdir/pg_year';

CREATE FUNCTION hash_year(year)
RETURNS integer LANGUAGE C IMMUTABLE AS '$libdir/pg_year';


CREATE OPERATOR = (
	LEFTARG = year,
	RIGHTARG = year,
	PROCEDURE = year_eq,
	COMMUTATOR = '=',
	NEGATOR = '<>',
	RESTRICT = eqsel,
	JOIN = eqjoinsel
);
COMMENT ON OPERATOR =(year, year) IS 'equals?';

CREATE OPERATOR <> (
	LEFTARG = year,
	RIGHTARG = year,
	PROCEDURE = year_ne,
	COMMUTATOR = '<>',
	NEGATOR = '=',
	RESTRICT = neqsel,
	JOIN = neqjoinsel
);
COMMENT ON OPERATOR <>(year, year) IS 'not equals?';

CREATE OPERATOR < (
	LEFTARG = year,
	RIGHTARG = year,
	PROCEDURE = year_lt,
	COMMUTATOR = > ,
	NEGATOR = >= ,
   	RESTRICT = scalarltsel,
	JOIN = scalarltjoinsel
);
COMMENT ON OPERATOR <(year, year) IS 'less-than';

CREATE OPERATOR <= (
	LEFTARG = year,
	RIGHTARG = year,
	PROCEDURE = year_le,
	COMMUTATOR = >= ,
	NEGATOR = > ,
   	RESTRICT = scalarltsel,
	JOIN = scalarltjoinsel
);
COMMENT ON OPERATOR <=(year, year) IS 'less-than-or-equal';

CREATE OPERATOR > (
	LEFTARG = year,
	RIGHTARG = year,
	PROCEDURE = year_gt,
	COMMUTATOR = < ,
	NEGATOR = <= ,
   	RESTRICT = scalargtsel,
	JOIN = scalargtjoinsel
);
COMMENT ON OPERATOR >(year, year) IS 'greater-than';

CREATE OPERATOR >= (
	LEFTARG = year,
	RIGHTARG = year,
	PROCEDURE = year_ge,
	COMMUTATOR = <= ,
	NEGATOR = < ,
   	RESTRICT = scalargtsel,
	JOIN = scalargtjoinsel
);
COMMENT ON OPERATOR >=(year, year) IS 'greater-than-or-equal';

CREATE OPERATOR CLASS btree_year_ops
DEFAULT FOR TYPE year USING btree
AS
        OPERATOR        1       <  ,
        OPERATOR        2       <= ,
        OPERATOR        3       =  ,
        OPERATOR        4       >= ,
        OPERATOR        5       >  ,
        FUNCTION        1       year_cmp(year, year);

CREATE OPERATOR CLASS hash_year_ops
DEFAULT FOR TYPE year USING hash AS
        OPERATOR        1       = ,
        FUNCTION        1       hash_year(year);
