#############################################
## Makefile for avr ave/gcc dudde          ##
## 28/Jun/2021                             ##
## made by FATHI MAHDI (Aptex96)           ##
#############################################


###########################################################################
# 1- Setting target configurations

# controller name
MCU = atmega328p

# short name
S_MCU = m328p

# port name
PORT_NAME = /dev/ttyACM1

# clock rate
CLK=1000000UL

# CLK select (default)
CLK_SELECT = lfuse:w:0x62:m

# programmer name
PROGRAMMER = avrisp

#baud rate (default = 19200)
BAUDRATE=19200

########################################################################
# 2- Source file configuration

#code name
SRC = deepsleep
# main source files
SRC_MAIN = $(SRC).c
# add others if available

# target object file
TARGET_OBJ = $(SRC).o

# target file name

TARGET = blink

# hex file
TARGET_HEX = $(TARGET).hex

###################################################################
#3- compiler configuration

#compiler name
COMPILER = avr-gcc

#object copy
AVRCOPY = avr-objcopy

#avrdude
AVRDUDE = avrdude

#remove
REMOVE = rm -f


#C flags
CFLAGS = -Wall -Os -DF_CPU=$(CLK) -c$(SRC_MAIN) -o$(TARGET_OBJ) -mmcu=$(MCU)



#cpp flags




#linker

#############################################################
# 4- create target file

TARGET:
	$(COMPILER) -mmcu=$(MCU) $(TARGET_OBJ) -o $(TARGET)
	@echo "\nTarget file generated!!\n"

##############################################################
# 5- obj copy

HEX:
	$(AVRCOPY) -O ihex -R .eeprom $(TARGET_HEX)
	@echo "Hex file generated!!" 	

##############################################################
# 6- Burn into target 

flash:
	$(AVRDUDE) -F -V -c $(PROGRAMMER) -p $(S_MCU) -P $(PORT_NAME) -b $(BAUDRATE) -U flas:w:$(TARGET_HEX)

#################################################################
# make all

all:
	$(COMPILER) -Os -g -DF_CPU=$(CLK) -mmcu=$(MCU) -c $(SRC_MAIN) -o $(TARGET_OBJ)
	@echo "\nDone compiling!!\n"
	$(COMPILER) -mmcu=$(MCU) $(TARGET_OBJ) -o $(TARGET)
	$(AVRCOPY) -O ihex -R .eeprom $(TARGET) $(TARGET_HEX)
	@echo "\nGenerating hex file....\n"
	$(AVRDUDE) -F -V -c $(PROGRAMMER) -p $(S_MCU) -P $(PORT_NAME) -b $(BAUDRATE) -U $(CLK_SELECT) -U flas:w:$(TARGET_HEX)
	@echo "\nDone flasing!!\n"
        	
#########################################################################################################
# compile
#
CC:
	$(COMPILER) -Os -g -DF_CPU=$(CLK) -mmcu=$(MCU) -c $(SRC_MAIN) -o $(TARGET_OBJ)

#####################################################################################################
# 8- clean the useless files

clean:
	@echo "Cleaning files...."
	$(REMOVE) $(TARGET_OBJ)
	$(REMOVE) $(TARGET)
	$(REMOVE) $(TARGET).lst 
###################################################################
