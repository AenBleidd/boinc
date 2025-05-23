ifdef ANDROID
  DOCKERWRAPPER_RELEASE_SUFFIX =
else
  ifdef RELEASE_ARCH
    DOCKERWRAPPER_RELEASE_SUFFIX = _$(DOCKERWRAPPER_RELEASE_VERSION)_$(RELEASE_ARCH)-pc-linux-gnu
  else
    DOCKERWRAPPER_RELEASE_SUFFIX = _$(DOCKERWRAPPER_RELEASE_VERSION)_x86_64-pc-linux-gnu
  endif
endif

BOINC_DIR = ../..
BOINC_SOURCE_API_DIR = $(BOINC_DIR)/api
BOINC_SOURCE_LIB_DIR = $(BOINC_DIR)/lib
BOINC_SOURCE_ZIP_DIR = $(BOINC_DIR)/zip

BOINC_API_DIR = $(BOINC_SOURCE_API_DIR)
BOINC_LIB_DIR = $(BOINC_SOURCE_LIB_DIR)
BOINC_ZIP_DIR = $(BOINC_SOURCE_ZIP_DIR)

MAKEFILE_LDFLAGS = -lpthread libstdc++.a
MAKEFILE_STDLIB  = libstdc++.a

CXXFLAGS += -g \
	-Wall -W -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -fno-common \
    -I$(BOINC_DIR) \
    -I$(BOINC_SOURCE_API_DIR) \
    -I$(BOINC_SOURCE_LIB_DIR) \
    -I$(BOINC_SOURCE_ZIP_DIR) \
    -L$(BOINC_API_DIR) \
    -L$(BOINC_LIB_DIR) \
    -L.

ifdef BUILD_APPS_WITH_VCPKG
  BUILD_DIR     = $(BOINC_DIR)/3rdParty/linux
  VCPKG_DIR     ?= $(BUILD_DIR)/vcpkg/installed/x64-linux

  CXXFLAGS += \
    -I$(VCPKG_DIR)/include \
    -L$(VCPKG_DIR)/lib
endif

ifdef BUILD_WITH_MINGW
  MAKEFILE_LDFLAGS += \
    -lws2_32
endif

PROGS = docker_wrapper$(DOCKERWRAPPER_RELEASE_SUFFIX)
all: $(PROGS)

libstdc++.a:
	ln -s `$(CXX) $(CXXFLAGS) -print-file-name=libstdc++.a`

clean: distclean

distclean:
	/bin/rm -f $(PROGS) $(addsuffix .exe, $(PROGS)) *.o libstdc++.a

install: all

docker_wrapper$(DOCKERWRAPPER_RELEASE_SUFFIX): docker_wrapper.o $(MAKEFILE_STDLIB) $(BOINC_API_DIR)/libboinc_api.a $(BOINC_LIB_DIR)/libboinc.a
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o docker_wrapper$(DOCKERWRAPPER_RELEASE_SUFFIX) docker_wrapper.o \
	-lboinc_api -lboinc $(MAKEFILE_LDFLAGS) \
	$(STDCPPTC)
