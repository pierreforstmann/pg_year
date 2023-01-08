-- pg_year--0.0.1.sql

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
  LIKE           = int2,
  INTERNALLENGTH = 2,
  STORAGE        = PLAIN,
  PASSEDBYVALUE
);

