#magicmini

###########################################################

ifeq (,$(PLATFORM))
PLATFORM=$(UNION_PLATFORM)
endif

ifeq (,$(PLATFORM))
$(error please specify PLATFORM, eg. PLATFORM=trimui make)
endif

###########################################################

REQUIRES_351FILES=other/351files
FETCH_DEPS=$(REQUIRES_351FILES)

.PHONY: fetch

all: readmes
	
early: $(FETCH_DEPS)
	mkdir -p other
	cd $(REQUIRES_351FILES) && make clean && START_PATH=/storage/TF2 CXX=${CROSS_COMPILE}g++ make

fetch: $(FETCH_DEPS)
	
clean:
	cd $(REQUIRES_351FILES) && make clean
	
$(REQUIRES_351FILES):
	git clone --depth 1 https://github.com/shauninman/351Files.git $(REQUIRES_351FILES)
	
include ../all/readmes/makefile
