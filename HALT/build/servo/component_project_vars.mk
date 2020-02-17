# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(PROJECT_PATH)/components/servo $(PROJECT_PATH)/components/servo/Test $(PROJECT_PATH)/components/servo/PCA9685Test $(PROJECT_PATH)/components/servo/Oscillator
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/servo -lservo
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += servo
COMPONENT_LDFRAGMENTS += 
component-servo-build: 
