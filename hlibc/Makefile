SHELL := /usr/bin/env bash

CC := gcc-11

CFLAGS := -std=c11 -Wall -Wextra
CPPFLAGS := -MD -MP -I./include

LDFLAGS :=
LDLIBS :=

SRC_DIR := src
BUILD_DIR := build

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

.PHONY: all
all: $(OBJ) temp

temp: $(OBJ)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ) -o temp

.PHONY: clean
clean:
	$(RM) -rv $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR):
	@mkdir -pv $@

-include $(BUILD_DIR)/*.d

