cyan = /bin/echo -e "\x1b[36m\#\# $1\x1b[0m"

# Project Root
override HOME = ../..

# Project Resources
SYSROOT = $(HOME)/../../../sysroot
INCLUDE = $(SYSROOT)/usr/include
SOURCE = $(HOME)/source
TOOLS = $(HOME)/../../tools
BIN = bin/system/init
LIB = lib

# Tools Config
CFLAGS = 

LDFLAGS = -Wall \
		  -lc

# Recursive Wild Card
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# Source Files
C_SRC = $(call rwildcard,$(SOURCE),*.c)

OBJS = $(patsubst $(SOURCE)/%.c,$(LIB)/%_c.o,$(C_SRC))

get_wad:
ifeq ("$(wildcard DOOM_wads)","")
	@ git clone https://github.com/Akbar30Bill/DOOM_wads
endif

build: get_wad
	@ mkdir -m 777 -p bin/usr/bin/doom
	@ cp DOOM_wads/doom.wad bin/usr/bin/doom
	@ cd ../../doomgeneric && make -f Makefile.kot
