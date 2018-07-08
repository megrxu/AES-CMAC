CXX ?= g++

# path
SRC_PATH = src
BUILD_PATH = build/obj
BIN_PATH = build/bin

# executable
BIN_NAME = aes-cmac.out

# extensions
SRC_EXT = cpp

# code lists
SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
DEPS = $(OBJECTS:.o=.d)

# flags
COMPILE_FLAGS = -std=c++11 -Wall -Wextra -g -w
INCLUDES = -I include/ -I /usr/local/include
LIBS = 

# colors
ACCENTCOLOR = \033[1;33m
CLEAN = \033[1;32m
DEFAULT = \033[0m

.PHONY: default_target
default_target: release

.PHONY: release
release: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS)
release: dirs
	@$(MAKE) all

.PHONY: dirs
dirs:
	@echo "$(ACCENTCOLOR)Creating directories$(DEFAULT)"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)

.PHONY: clean
clean:
	@echo "$(CLEAN)Deleting $(BIN_NAME) symlink$(DEFAULT)"
	@$(RM) $(BIN_NAME)
	@echo "$(CLEAN)Deleting directories$(DEFAULT)"
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BIN_PATH)

# checks the executable and symlinks to the output
.PHONY: all
all: $(BIN_PATH)/$(BIN_NAME)
	@echo "$(ACCENTCOLOR)Making symlink: $(BIN_NAME) -> $<$(DEFAULT)"
	@$(RM) $(BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

# Creation of the executable
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "$(ACCENTCOLOR)Linking: $@$(DEFAULT)"
	$(CXX) $(OBJECTS) -o $@ $(LIBS)

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "$(ACCENTCOLOR)Compiling: $< -> $@$(DEFAULT)"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
