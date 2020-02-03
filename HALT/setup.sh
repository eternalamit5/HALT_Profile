#!/bin/bash

IDF=/home/karsh/Work/IDFRepo/LPG_esp_idf
echo "Setting IDF_PATH with $IDF"
export "IDF_PATH=$IDF"
export "PATH=$PATH:/home/karsh/esp/xtensa-esp32-elf/bin"
##echo "Enter command: flash, menuconfig, all, clean, erase_flash"
##read variable

if [ "$1" = "m" ];then
	echo "Running:  make monitor"
	make monitor
elif [ "$1" = "c" ];then 
	echo "Running:  make menuconfig"
	make menuconfig
elif [ "$1" = "f" ];then
	echo "Running:  make flash"
	make flash
elif [ "$1" = "b" ];then
	echo "Running:  make all"
	make all
elif [ "$1" = "m8" ];then
	echo "Running:  make -j8 monitor"
	make -j8 monitor
elif [ "$1" = "c8" ];then 
	echo "Running:  make -j8 menuconfig"
	make -j8 menuconfig
elif [ "$1" = "f8" ];then
	echo "Running:  make -j8 flash"
	make -j8 flash
elif [ "$1" = "b8" ];then
	echo "Running:  make -j8 all"
	make -j8 all
else
	echo "Running:  make $variable"
	make $1
fi
