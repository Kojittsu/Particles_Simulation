# Executable name
EXEC = ExecuteSimu

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Compilator and options
CXX = g++
CXXFLAGS = -Wall -I$(INC_DIR) -std=c++11
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Source and objects files list
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default rule
all: $(OBJ_DIR) $(EXEC)

# Executable creation
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Object files creation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# obj directory creation if needed
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

# Phony targets
.PHONY: all clean
