#####################################  Init ######################################
# Check SMPAPI_DIR
ifndef SMPAPI_DIR
$(error Error: SMPAPI_DIR is not defined, please source build.env in the SAPI tree)
endif

LIBS_APP = libs

include $(SMPAPI_DIR)/smpapi.defs

LIBRARY_SIGMA_DIR = $(CBOX_MAIN_DIR)/../sigma_extension
TARGET= VNExpress
##################################### Main #####################################
SRCS  = VNExpress.cpp \
		src/VNExpressModel.cpp \
		$(LIBS_APP)/requestdata/requestdata.cpp \
 		$(LIBS_APP)/jsoncpp-1.7.7/src/lib_json/json_reader.cpp \
        $(LIBS_APP)/jsoncpp-1.7.7/src/lib_json/json_value.cpp \
        $(LIBS_APP)/jsoncpp-1.7.7/src/lib_json/json_writer.cpp


###############################################################################
CURL_LIBDIR = $(SMP86XX_ROOTFS_PATH)/cross_rootfs
DIRECTFB_LIBDIR=$(DIRECTFB_DIR)/install/lib
DIRECTFB_INCDIR=$(DIRECTFB_DIR)/install/include

CFLAGS  += -Wall -I$(SMPAPI_INCDIR)

CFLAGS  += \
	-I$(DIRECTFB_INCDIR)/directfb -I$(DIRECTFB_INCDIR)/sawman \
	-I$(DIRECTFB_DIR)/external-libs/linux-fusion-8.7.0/linux/include \
	-I$(DIRECTFB_INCDIR)/divine -I$(SMPAPI_DIR)/include -I$(SMPAPI_DIR)/userspace/include \
	-DUSE_GFX_ONLY
	
LDFLAGS += \
	-Wl,-rpath-link -Wl,$(SMP86XX_ROOTFS_PATH)/cross_rootfs/lib

RMCFLAGS += \
	-D_FILE_OFFSET_BITS=64 \
	-DLLAD_DIRECT \
	-DALLOW_OS_CODE	\
	-D_REENTRANT \
	-I. -I./include \
	-I./remote \
	-DXMD_H=1 \
	-I$(RUA_DIR) -I$(RUA_DIR)/samples
	
##################################### link sdk lib
INCLUDES += \
	-I$(CBOX_MAIN_DIR)/include \
	-I$(CURL_LIBDIR)/include \
	-I$(LIBS_APP)/jsoncpp-1.7.7/include \
	-I$(LIBS_APP)/requestdata
	
INCLUDES += \
	-I$(GSTREAMER_DIR) \
	-I$(GSTREAMER_INSTALL_DIR) \
	-I$(GSTREAMER_INSTALL_DIR)/include/gstreamer-1.0 \
	-I$(GSTREAMER_INSTALL_DIR)/include/glib-2.0 \
	-I$(GSTREAMER_INSTALL_DIR)/lib/glib-2.0/include
	
LDFLAGS += -L$(CURL_LIBDIR)/lib -lcurl
LDFLAGS += -L$(SMPAPI_LIBDIR) -lsmpapi -lsmpdfb
LDFLAGS += -L$(DIRECTFB_DIR)/install/lib -ldirectfb -lfusion -ldirect -lm -lsawman -ldivine

LDFLAGS += \
	-Wl,-rpath-link -Wl,$(GSTREAMER_INSTALL_DIR)/lib `pkg-config --cflags --libs gstreamer-1.0` \
	-Wl,-rpath-link -Wl,$(RUA_DIR)/build_system/lib


##################################### Apps #####################################
include $(LIBRARY_SIGMA_DIR)/Makefile.inc

##################################### Build #####################################
CXXFLAGS = $(CFLAGS)

OBJS=$(addsuffix .o, $(basename $(SRCS)))
DEPS=$(addsuffix .d, $(basename $(SRCS)))	
	
.PHONY: all
all: install

.PHONY: install
install: $(TARGET)

$(TARGET): $(OBJS)
	$(QUIET)echo "  [LINK]    $@"
	$(CC) -o $@ -g $(CFLAGS) $^ $(LDFLAGS)

include $(SMPAPI_DIR)/smpapi.rules
	
clean::
	$(Q)$(foreach target,$(TARGET),rm -f *.o;)
	$(Q)$(foreach target,$(TARGET),rm -f $(SMPAPI_BINDIR)/$(target) $(target);)

distclean::
	$(Q)$(foreach target,$(TARGET),rm -f $(SMPAPI_BINDIR)/$(target) $(target);)
	
-include $(DEPS)
