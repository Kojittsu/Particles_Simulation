# Executable name
EXEC = ExecuteSimu

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Subdirectories for core and gui
SRC_SUBDIRS = $(SRC_DIR)/core $(SRC_DIR)
INC_SUBDIRS = $(INC_DIR)/core $(INC_DIR)

# Compilator and options
CXX = g++
CXXFLAGS = -Wall -I$(INC_DIR) -I$(INC_DIR) -I$(INC_DIR) -std=c++11
LDFLAGS = -lglfw -lGLU -lGL -lyaml-cpp

# Source and object files list
SRCS = $(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)/*.cpp))
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Default rule
all: $(OBJ_DIR) $(EXEC)

# Executable creation
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Object files creation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# obj directory creation if needed
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

# Phony targets
.PHONY: all clean
