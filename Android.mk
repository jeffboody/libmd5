# don't include LOCAL_PATH for submodules

include $(CLEAR_VARS)
LOCAL_MODULE    := md5
LOCAL_CFLAGS    := -Wall
LOCAL_SRC_FILES := md5/md5.c
LOCAL_LDLIBS    := -Llibs/armeabi

include $(BUILD_SHARED_LIBRARY)
