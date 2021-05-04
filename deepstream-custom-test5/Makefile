CUDA_VER?=
ifeq ($(CUDA_VER),)
  $(error "CUDA_VER is not set")
endif

APP:= deepstream-test5-app

TARGET_DEVICE = $(shell gcc -dumpmachine | cut -f1 -d -)

NVDS_VERSION:=5.1

LIB_INSTALL_DIR?=/opt/nvidia/deepstream/deepstream-$(NVDS_VERSION)/lib/
APP_INSTALL_DIR?=/opt/nvidia/deepstream/deepstream-$(NVDS_VERSION)/bin/

ifeq ($(TARGET_DEVICE),aarch64)
  CFLAGS:= -DPLATFORM_TEGRA
endif

SRCS:= deepstream_test5_app_main.c deepstream_utc.c
SRCS+= ../deepstream-app/deepstream_app.c ../deepstream-app/deepstream_app_config_parser.c
SRCS+= $(wildcard ../../apps-common/src/*.c)

INCS:= $(wildcard *.h)

PKGS:= gstreamer-1.0 gstreamer-video-1.0 x11 json-glib-1.0

OBJS:= $(SRCS:.c=.o)

#------------------------ CUSTOM CODE ------------------------------#
OBJS+= deepstream_sgie_meta.o
#-------------------------------------------------------------------#

CFLAGS+= -I../../apps-common/includes \
		 -I../../../includes \
		 -I../deepstream-app/ -DDS_VERSION_MINOR=0 -DDS_VERSION_MAJOR=5 \
		 -I /usr/local/cuda-$(CUDA_VER)/include

LIBS:= -L/usr/local/cuda-$(CUDA_VER)/lib64/ -lcudart

LIBS+= -L$(LIB_INSTALL_DIR) -lnvdsgst_meta -lnvds_meta -lnvdsgst_helper -lnvdsgst_smartrecord -lnvds_utils -lnvds_msgbroker -lm \
       -lcuda -lgstrtspserver-1.0 -ldl -Wl,-rpath,$(LIB_INSTALL_DIR)

CFLAGS+= $(shell pkg-config --cflags $(PKGS))

LIBS+= $(shell pkg-config --libs $(PKGS))

all: $(APP)

#------------------------ CUSTOM CODE ------------------------------#
deepstream_sgie_meta.o: deepstream_sgie_meta.cpp $(INCS) Makefile
	$(CXX) -c -o $@ -Wall -Werror $(CFLAGS) $<
#-------------------------------------------------------------------#

%.o: %.c $(INCS) Makefile
	$(CC) -c -o $@ $(CFLAGS) $<

#------------------------ CUSTOM CODE ------------------------------#
# aca solo se cambio la forma de compilar, se cambio el flag $(CC) por $(CXX)
$(APP): $(OBJS) Makefile
	$(CXX) -o $(APP) $(OBJS) $(LIBS)
#-------------------------------------------------------------------#

install: $(APP)
	cp -rv $(APP) $(APP_INSTALL_DIR)

clean:
	rm -rf $(OBJS) $(APP)

