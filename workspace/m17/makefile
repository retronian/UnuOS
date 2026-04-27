###########################################################

ifeq (,$(PLATFORM))
PLATFORM=$(UNION_PLATFORM)
endif

ifeq (,$(PLATFORM))
$(error please specify PLATFORM, eg. PLATFORM=rgb30 make)
endif

###########################################################

.PHONY: fetch

all: readmes
	cd ./boot && ./build.sh

early: 
	# early

fetch:

clean:
	cd ./overclock && make clean

###########################################################

include ../all/readmes/makefile
