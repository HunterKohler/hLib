SHELL = bash

CFLAGS := \
	-std=c11 \
	-Wall \
	-Wextra \
	-Wno-sign-compare \
	-Wno-pointer-sign \
	-Wno-implicit-fallthrough \
	-Wno-override-init \
	-fanalyzer \
	-O2 \
	-I./build/include/

# Create *.d files while compiling, then include at bottom to track changes in
# associated headers.
CPPFLAGS := -MD -MP

LDFLAGS :=
LDLIBS :=

LIB_SRC := $(shell find src -name \*.c)
LIB_OBJ := $(patsubst %.c,build/%.o,$(LIB_SRC))
LIB_ARCHIVE := ./build/lib/crypto.a
LIB_INCLUDE := \
	$(patsubst src/%,build/include/crypto/%,$(shell find src -name \*.h))

TEST_SRC := $(shell find test -name \*.c)
TEST_OBJ := $(patsubst %.c,build/%.o,$(TEST_SRC))
TEST_BIN := $(patsubst %.c,bin/%,$(TEST_SRC))

CRYPTOPALS_SRC := $(shell find cryptopals -name \*.c)
CRYPTOPALS_OBJ := $(patsubst %.c,build/%.o,$(CRYPTOPALS_SRC))
CRYPTOPALS_BIN := $(patsubst %.c,bin/%,$(CRYPTOPALS_SRC))

SRC := $(LIB_SRC) $(TEST_SRC) $(CRYPTOPALS_SRC)
OBJ := $(LIB_OBJ) $(TEST_OBJ) $(CRYPTOPALS_OBJ)
BIN := $(TEST_BIN) $(CRYPTOPALS_BIN)

# Commands
# -----------------------------------------------------------------------------
.PHONY := all clean run_tests run_cryptopals

all: $(LIB) $(OBJ) $(BIN)

run_tests: $(sort $(TEST_BIN))
	@for i in $^; do \
		name=$${i#bin/test/} \
		ret=$$($$i 2>&1) && status="Pass" || status="Fail" ; \
		printf "[Test] %s: %s\n" "$$name" "$$status" ; \
	done

run_cryptopals: $(sort $(CRYPTOPALS_BIN))
	@for i in $^; do \
		set=$${i#bin/cryptopals/set_} ; \
		set=$${set%/*} ; \
		challenge=$${i##*/challenge_} ; \
		ret=$$($$i 2>&1) && status="Pass" || status="Fail" ; \
		printf "[Challenge] %d.%d: %s\n" "$$set" "$$challenge" "$$status" ; \
	done

clean:
	@rm -rf build/ bin/

# Directories
# -----------------------------------------------------------------------------
%/:
	@mkdir -p $@

# Dependencies
# -----------------------------------------------------------------------------
$(OBJ): $(LIB_INCLUDE)

$(CRYPTOPALS_BIN): $(LIB_ARCHIVE)

# Build
# -----------------------------------------------------------------------------
$(OBJ): build/%.o : %.c | $(dir $(OBJ))
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN): bin/% : build/%.o | $(dir $(BIN))
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^

# Packaging library.
$(LIB_ARCHIVE): $(LIB_OBJ) | $(dir $(LIB_ARCHIVE))
	ar -rcs $@ $^

# Symlink include to crypto.
$(LIB_INCLUDE): build/include/crypto/%.h : src/%.h | $(dir $(LIB_INCLUDE))
	@cp $< $@

# Makefiles
# -----------------------------------------------------------------------------
-include $(shell find build -name \*.d 2>/dev/null)


