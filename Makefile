CC = gcc
CCFLAGS = -Wall -std=c11 -g -O2
LDFLAGS  = -lm
APP_BIN = hovercraft
SRC_PATH = src
OBJ_PATH = obj
INC_PATH = include
BIN_PATH = bin
LIB_PATH = lib
MKDIR_CMD = mkdir
TEST_DIR = if

SRC_FILES = $(wildcard src/*.c) $(wildcard src/*/*.c)
OBJ_FILES = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o, $(SRC_FILES))

ifeq ($(OS),Windows_NT)
    CCFLAGS += -D WIN32
		LDFLAGS += -lSDL -lSDL_image
		W_OBJ_FILES = $(subst /,\,$(OBJ_FILES))
		RM_CMD = for %%x in ($(W_OBJ_FILES)) do (if exist %%x (del /q %%x))
		LDFLAGS += -lmingw32 -lSDLmain  -lSDL_image -lopengl32 -lglu32
    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        CCFLAGS += -D AMD64
    endif
    ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        CCFLAGS += -D IA32
    endif
else
		MKDIR_CMD+= -p
		RM_CMD = rm $(OBJ_FILES) $(BIN_PATH)/$(APP_BIN)
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
				LDFLAGS += -lGL -lGLU
				LDFLAGS += -lSDL -lSDL_image -lSDL_mixer
        CCFLAGS += -D LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
				LDFLAGS += -I/Library/Frameworks/SDL.framework/Headers -I/opt/local/include `sdl-config --libs` -framework Cocoa -framework OpenGL
				CCFLAGS += `sdl-config --cflags`
        CCFLAGS += -D OSX
    endif
    UNAME_P := $(shell uname -p)

endif

all: $(APP_BIN)
	@echo "$(APP_BIN) has been created"
ifeq ($(OS),Windows_NT)
$(APP_BIN): $(OBJ_FILES)
	@echo "------------COMPILATION FINALE---------------"
	if not exist "$(BIN_PATH)" $(MKDIR_CMD) $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(APP_BIN) $(OBJ_FILES) $(CCFLAGS) $(LDFLAGS) -I $(INC_PATH)
else
$(APP_BIN): $(OBJ_FILES)
	@echo "------------COMPILATION FINALE---------------"
	$(MKDIR_CMD) $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(APP_BIN) $(OBJ_FILES) $(CCFLAGS) $(LDFLAGS) -I $(INC_PATH)
endif

ifeq ($(OS),Windows_NT)
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@echo "------------COMPILATION $< -> $@q---------------------"
	if not exist "$(OBJ_PATH)" $(MKDIR_CMD) $(OBJ_PATH)
	$(CC) -c $< -o $@ $(CCFLAGS) $(LDFLAGS) -I $(INC_PATH)
else
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@echo "------------COMPILATION $< -> $@q---------------------"
	$(MKDIR_CMD) $(OBJ_PATH)
	$(CC) -c $< -o $@ $(CCFLAGS) $(LDFLAGS) -I $(INC_PATH)
endif

clean:
		$(RM_CMD)

