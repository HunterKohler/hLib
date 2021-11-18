SHELL = bash

# -Wno-sign-compare \
# -Wno-implicit-fallthrough \

CXXFLAGS := \
	-std=c++20 \
	-Wall \
	-Wextra \
	-Wno-sign-compare \
	-fanalyzer \
	-O2 \
	-I./build/include

CPPFLAGS := -MD -MP

LDFLAGS :=
LDLIBS :=

SRC := $(shell find src -name *.cpp)
SRC_OBJ := $(patsubst %.cpp,build/%.o,$(SRC))

TEST := $(shell find test -name *.cpp)
TEST_OBJ := $(patsubst %.cpp,build/%.o,$(TEST))
TEST_BIN := $(patsubst %.cpp,bin/%,$(TEST))

OBJ := $(SRC_OBJ) $(TEST_OBJ)
BIN := $(TEST_BIN)

CATCH2_H := build/include/catch2.h

.PHONY: all clean test tree

all: $(BIN) $(OBJ)

clean:
	@rm -rf bin build

test: $(TEST_BIN)
	@for i in $(TEST_BIN); do printf "$$i: "; ./$$i ; done

%/:
	@mkdir -p $@

$(CATCH2_H): build/include/
	./scripts/getcatch2 > $(CATCH2_H)

$(SRC_OBJ): | build/src/

$(TEST_OBJ): $(CATCH2_H) | build/test/
$(TEST_BIN): bin/% : build/%.o | bin/test/

$(BIN):
	$(CXX) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(OBJ): build/%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

-include $(shell find build -name *.d 2>/dev/null)i
