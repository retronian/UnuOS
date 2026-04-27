#rg35xx

###########################################################

ifeq (,$(PLATFORM))
PLATFORM=$(UNION_PLATFORM)
endif

ifeq (,$(PLATFORM))
$(error please specify PLATFORM, eg. PLATFORM=trimui make)
endif

###########################################################

REQUIRES_COMMANDER=other/DinguxCommander
FETCH_DEPS=$(REQUIRES_COMMANDER)

.PHONY: fetch

all: readmes
	cd ./overclock && make
	cd ./boot && ./build.sh

early: $(FETCH_DEPS)
	cd other/DinguxCommander && make -j

fetch: $(FETCH_DEPS)

clean:
	cd ./overclock && make clean
	cd ./boot && rm -rf ./output
	cd other/DinguxCommander && make clean
	
$(REQUIRES_COMMANDER):
	git clone --depth 1 --branch minui-rg35xx https://github.com/shauninman/DinguxCommander.git $(REQUIRES_COMMANDER)

include ../all/readmes/makefile
