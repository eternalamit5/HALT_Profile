# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/arduino-esp32_modified/cores/esp32 $(IDF_PATH)/components/arduino-esp32_modified/variants/esp32 $(IDF_PATH)/components/arduino-esp32_modified/libraries/AsyncUDP/src $(IDF_PATH)/components/arduino-esp32_modified/libraries/EEPROM/src $(IDF_PATH)/components/arduino-esp32_modified/libraries/ESP32/src $(IDF_PATH)/components/arduino-esp32_modified/libraries/FFat/src $(IDF_PATH)/components/arduino-esp32_modified/libraries/FS/src $(IDF_PATH)/components/arduino-esp32_modified/libraries/Preferences/src $(IDF_PATH)/components/arduino-esp32_modified/libraries/SD_MMC/src $(IDF_PATH)/components/arduino-esp32_modified/libraries/SPI/src $(IDF_PATH)/components/arduino-esp32_modified/libraries/SPIFFS/src $(IDF_PATH)/components/arduino-esp32_modified/libraries/SimpleBLE/src $(IDF_PATH)/components/arduino-esp32_modified/libraries/Ticker/src $(IDF_PATH)/components/arduino-esp32_modified/libraries/Update/src $(IDF_PATH)/components/arduino-esp32_modified/libraries/Wire/src
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/arduino-esp32_modified -larduino-esp32_modified
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += arduino-esp32_modified
COMPONENT_LDFRAGMENTS += 
component-arduino-esp32_modified-build: 
