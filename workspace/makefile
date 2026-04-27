# workspace (all)

###########################################################

ifeq (,$(PLATFORM))
PLATFORM=$(UNION_PLATFORM)
endif

ifeq (,$(PLATFORM))
$(error please specify PLATFORM, eg. PLATFORM=trimui make)
endif

###########################################################

.PHONY: all fetch

all:
	cd ./$(PLATFORM)/libmsettings && make
	cd ./$(PLATFORM) && make early # eg. other libs
	cd ./$(PLATFORM)/keymon && make
	cd ./all/unuos/ && make
	cd ./all/minarch/ && make
	cd ./all/clock/ && make
	cd ./all/minput/ && make
	cd ./all/syncsettings/ && make
	cd ./all/say/ && make
	cd ./$(PLATFORM)/cores && make
	cd ./$(PLATFORM) && make

fetch:
	cd ./$(PLATFORM) && make fetch
	cd ./all/minarch && make fetch
	cd ./$(PLATFORM)/cores && make fetch

clean:
	cd ./$(PLATFORM)/libmsettings && make clean
	cd ./$(PLATFORM)/keymon && make clean
	cd ./all/unuos/ && make clean
	cd ./all/minarch/ && make clean
	cd ./all/clock/ && make clean
	cd ./all/minput/ && make clean
	cd ./all/syncsettings/ && make clean
	cd ./all/say/ && make clean
	cd ./$(PLATFORM) && make clean
