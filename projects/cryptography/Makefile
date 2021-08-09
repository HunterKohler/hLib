SHELL := /usr/bin/env bash

CXX := g++-11
CXX_STANDARD := c++20

CXXFLAGS := --std=$(CXX_STANDARD) # -Wall
CPPFLAGS := -MP -MD
LDFLAGS :=
LDLIBS :=

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

SRC := src/main.cpp
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

EXE := $(BIN_DIR)/main

.PHONY: all
all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(BUILD_DIR) $(SRC_DIR):
	@mkdir -pv $@

.PHONY: clean
clean:
	@$(RM) -rv $(BUILD_DIR) $(BIN_DIR)

-include $(BUILD_DIR)/*.d