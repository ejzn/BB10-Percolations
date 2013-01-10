ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

NAME=screen
PLUGIN=yes
UTILS=no

include ../../../../meta.mk

SRCS+=screen_js.cpp

include $(MKFILES_ROOT)/qtargets.mk

LIBS+=QtCore
