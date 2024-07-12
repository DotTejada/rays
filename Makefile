FLAGS ?= -lraylib
RAYLIB_PATH ?= /usr/local

ifeq ($(OS),Windows_NT)
    FLAGS += -lgdi32 -lwinmm
else
    FLAGS += -lGL -lm
endif

all:
	gcc -o rlife rlife.c -I$(RAYLIB_PATH)/include -L$(RAYLIB_PATH)/lib $(FLAGS)
