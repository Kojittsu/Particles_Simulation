# Executable name
EXEC = ExecuteSimu

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
IMGUI_DIR = imgui

# ImGui sources files
IMGUI_SRC = $(IMGUI_DIR)/imgui.cpp \
            $(IMGUI_DIR)/imgui_draw.cpp \
            $(IMGUI_DIR)/imgui_widgets.cpp \
            $(IMGUI_DIR)/imgui_tables.cpp \
            $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp \
            $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

# Compiler and options
CXX = g++
CXXFLAGS = -Wall -std=c++11 -I$(INC_DIR) -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
LDFLAGS = -lGL -lGLU -lglfw -lyaml-cpp

# Source and object files list
SRCS = $(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.cpp))
IMGUI_OBJ = $(patsubst $(IMGUI_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(IMGUI_SRC))
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS)) $(IMGUI_OBJ)

# Default rule
all: $(OBJ_DIR) $(EXEC)

# Executable creation
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Object files creation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ImGui object files creation
$(OBJ_DIR)/%.o: $(IMGUI_DIR)/%.cpp
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
