CC = gcc
CFLAGS = -Wall -g



# Include paths
ENG_SUB_PATHS = director renderer scout common/*
ENGINE_INC = -Iengine/include -Iengine/src \
            $(patsubst %, -Iengine/src/%, $(ENG_SUB_PATHS))

APP_SUB_PATHS = include src 
APP_INC = $(patsubst %, -Iapp/%, $(APP_SUB_PATHS))

# Directories
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Engine sources and objects
ENGINE_SRCS = $(shell find engine/src -name '*.c')
ENGINE_OBJS = $(patsubst engine/src/%.c, $(OBJ_DIR)/engine/%.o, $(ENGINE_SRCS))

# App sources and objects
APP_SRCS = $(shell find app/src -name '*.c')
APP_OBJS = $(patsubst app/src/%.c, $(OBJ_DIR)/app/%.o, $(APP_SRCS))

# Link libraries
LDFLAGS = -lglfw3 -lopengl32 -lgdi32

# Output binary
TARGET = $(BUILD_DIR)/Jackal.exe

all: $(TARGET) assets
	@echo "Build complete. Output is in $(BUILD_DIR)/"

$(TARGET): $(ENGINE_OBJS) $(APP_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Engine object compilation
$(OBJ_DIR)/engine/%.o: engine/src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(ENGINE_INC) -c $< -o $@

# App object compilation
$(OBJ_DIR)/app/%.o: app/src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(APP_INC) -c $< -o $@

# Copy assets into build/
assets:
	@mkdir -p $(BUILD_DIR)/assets/
	cp -r engine/assests/* $(BUILD_DIR)/assets/

# Debug: compile tests/main.c and link with engine
DEBUG_TARGET = $(BUILD_DIR)/debug_test.exe
debug: $(ENGINE_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(ENGINE_INC) engine/tests/main.c $^ -o $(DEBUG_TARGET) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

run: all
	cd $(BUILD_DIR) && ./Jackal.exe

.PHONY: all assets debug clean run