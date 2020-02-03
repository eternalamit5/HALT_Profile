# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(PROJECT_PATH)/components/arduino-esp32/cores/esp32 $(PROJECT_PATH)/components/arduino-esp32/variants/esp32 $(PROJECT_PATH)/components/arduino-esp32/libraries/AsyncUDP/src $(PROJECT_PATH)/components/arduino-esp32/libraries/EEPROM/src $(PROJECT_PATH)/components/arduino-esp32/libraries/ESP32/src $(PROJECT_PATH)/components/arduino-esp32/libraries/FFat/src $(PROJECT_PATH)/components/arduino-esp32/libraries/FS/src $(PROJECT_PATH)/components/arduino-esp32/libraries/Preferences/src $(PROJECT_PATH)/components/arduino-esp32/libraries/SD_MMC/src $(PROJECT_PATH)/components/arduino-esp32/libraries/SPI/src $(PROJECT_PATH)/components/arduino-esp32/libraries/SPIFFS/src $(PROJECT_PATH)/components/arduino-esp32/libraries/SimpleBLE/src $(PROJECT_PATH)/components/arduino-esp32/libraries/Ticker/src $(PROJECT_PATH)/components/arduino-esp32/libraries/Update/src $(PROJECT_PATH)/components/arduino-esp32/libraries/Wire/src
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/arduino-esp32 -larduino-esp32
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += arduino-esp32
COMPONENT_LDFRAGMENTS += 
component-arduino-esp32-build: 
