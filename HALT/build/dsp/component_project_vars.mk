# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/dsp/modules/dotprod/include $(IDF_PATH)/components/dsp/modules/support/include $(IDF_PATH)/components/dsp/modules/windows/include $(IDF_PATH)/components/dsp/modules/windows/hann/include $(IDF_PATH)/components/dsp/modules/windows/blackman/include $(IDF_PATH)/components/dsp/modules/windows/blackman_harris/include $(IDF_PATH)/components/dsp/modules/windows/blackman_nuttall/include $(IDF_PATH)/components/dsp/modules/windows/nuttall/include $(IDF_PATH)/components/dsp/modules/windows/flat_top/include $(IDF_PATH)/components/dsp/modules/iir/include $(IDF_PATH)/components/dsp/modules/fir/include $(IDF_PATH)/components/dsp/modules/math/include $(IDF_PATH)/components/dsp/modules/math/add/include $(IDF_PATH)/components/dsp/modules/math/sub/include $(IDF_PATH)/components/dsp/modules/math/mul/include $(IDF_PATH)/components/dsp/modules/math/addc/include $(IDF_PATH)/components/dsp/modules/math/mulc/include $(IDF_PATH)/components/dsp/modules/matrix/include $(IDF_PATH)/components/dsp/modules/fft/include $(IDF_PATH)/components/dsp/modules/common/include
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/dsp -ldsp
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += dsp
COMPONENT_LDFRAGMENTS += 
component-dsp-build: 
