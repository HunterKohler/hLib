SHELL = bash

# -Wno-sign-compare \
# -Wno-implicit-fallthrough \

CXXFLAGS := \
	-std=c++20 \
	-Wall \
	-Wextra \
	-fanalyzer \
	-O2

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

TREE := $(foreach dir,build/ bin/, \
	$(patsubst %,$(dir)%,$(shell find src test -type d)))

.PHONY: all clean test tree

all: $(BIN) $(OBJ)

clean:
	@rm -rf bin build

test: $(TEST_BIN)
	@for i in $(TEST_BIN); do printf "$$i: "; ./$$i ; done

tree:
	@mkdir -p $(TREE)

$(TARGET_BIN): bin/% : build/src/%.o $(SRC_OBJ)
$(TEST_BIN): bin/% : build/%.o

$(BIN): | tree
	$(CXX) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(OBJ): build/%.o : %.cpp | tree
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

-include $(shell find build -name *.d 2>/dev/null)i
