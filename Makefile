BASE_DIR=/usr/local/freeswitch
CFLAGS=-I./generated -I$(BASE_DIR)/include/freeswitch -fvisibility=hidden -DSWITCH_API_VISIBILITY=1
LDFLAGS=-L$(BASE_DIR)/lib -lfreeswitch

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    CFLAGS   += -fPIC
    LDFLAGS  += -Wl,-rpath=$(BASE_DIR)/lib
endif

all:
	CFLAGS="$(CFLAGS)"" -shared" LDFLAGS="$(LDFLAGS)" so build -o mod_solod.so .

.PHONY: main
main:
	CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" so build -o main .

gen:
	so translate -o generated .

c:
	# gcc $(GCFLAGS) $(GLDFLAGS) -o mod_solod.so generated/**/*.c
	gcc $(CFLAGS) -shared -o mod_solod.so $(shell find generated -name "*.c") $(LDFLAGS)

install:
	cp mod_solod.so /usr/local/freeswitch/mod/
