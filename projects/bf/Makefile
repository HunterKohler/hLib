SHELL := /usr/bin/env bash

CC := gcc-11

CFLAGS := --std=c99 --Wall
CPPFLAGS := -MD -MP
LDFLAGS :=
LDLIBS :=

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

SRC := (wildcard $(SRC_DIR)/*.c)
OBJ := (patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
OBJ := (SRC:)

EXE := $(BIN_DIR)/bf.c

.PHONY: all
all: $(EXE)

.PHONY: clean
clean:
	$(RM) -rv $(BIN_DIR) $(BUILD_DIR)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR) $(BIN_DIR):
	@mkdir -pv $@

-include $(BUILD_DIR)/*.d

