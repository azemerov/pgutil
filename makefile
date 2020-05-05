EXTENSION = pgutil
#DATA = $(wildcard *--*.sql)
DATA = pgutil--0.0.1.sql
TESTS         = $(wildcard test/sql/*.sql)
REGRESS_OPTS  = --inputdir=test         \
                --load-extension=pgutil \
                --load-language=plpgsql
REGRESS       = $(patsubst test/sql/%.sql,%,$(TESTS))
MODULES = nvl decode luhn

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

