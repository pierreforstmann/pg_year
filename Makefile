#
# Makefile
#
MODULES = pg_year 
EXTENSION = pg_year  # the extension's name
DATA = pg_year--0.0.1.sql    # script file to install


# make installcheck to run automatic test
REGRESS_OPTS =  --temp-instance=/tmp/5555 --port=5555 --temp-config pg_year.conf
REGRESS = test

# for posgres build
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

pgxn:
	git archive --format zip  --output ../pgxn/pg_year/pg_year-0.0.1.zip main
