SHELL := /usr/bin/env bash

CFLAGS := -std=c11 -Wall -Wextra
CPPFLAGS := -MD -MP -I./include

# # TODO checkout these flags
# CXXFLAGS += -Wextra -Wwrite-strings -Wno-parentheses
# CXXFLAGS += -Wpedantic -Warray-bounds -Weffc++

LDFLAGS :=
LDLIBS :=

SRC := $(shell find src -name *.c)
TEST := $(shell find tests -name *.c)

SRC_OBJ := $(patsubst %.c,build/%.o,$(SRC))
TEST_OBJ := $(patsubst %.c,build/%.o,$(TEST)) $(SRC_OBJ)

OBJ := $(sort $(SRC_OBJ) $(TEST_OBJ))

TEST_BIN := bin/test

.PHONY: all
all: $(TEST_BIN)

.PHONY: clean
clean:
	@rm -rf bin build

$(TEST_BIN): $(TEST_OBJ)
	@mkdir -p $(@D)
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(OBJ): build/%.o : %.c
	@mkdir -p $(@D)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

