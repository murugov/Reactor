CC = clang++

FLAGS = -DDEBUG -D_DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-align \
		-Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral \
		-Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked \
		-Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=2 \
		-Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros \
		-Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new \
		-fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -fPIE \
		-Werror=vla -fsanitize=address,undefined,float-divide-by-zero,integer-divide-by-zero,vptr

LDFLAGS = -isystem /opt/homebrew/include -L/opt/homebrew/lib -lraylib \
          -framework OpenGL -framework Cocoa -framework IOKit

COMMON_INCLUDES = -I./include

COMMON_FILES = src/Colors.cpp src/Adapter.cpp src/Canvas.cpp src/Scene.cpp src/Camera.cpp src/Button.cpp
GAME_OBJECTS = src/Valve.cpp

WORK_DIR = ./work
BUILD_DIR = ./work/build
RUN_DIR = ./work/run
TARGET = $(RUN_DIR)/react_program

all: react

react: main.cpp $(COMMON_FILES) $(GAME_OBJECTS)
	@mkdir -p $(WORK_DIR)
	@mkdir -p $(BUILD_DIR) $(RUN_DIR)
	@echo "-----------------------------------------------------------------------------------------"
	$(CC) -o $(BUILD_DIR)/react_program $(FLAGS) $(LDFLAGS) main.cpp $(COMMON_INCLUDES) $(COMMON_FILES) $(GAME_OBJECTS)
	@mv $(BUILD_DIR)/react_program $(TARGET)
	@echo "-----------------------------------------------------------------------------------------"


run-react: react
	$(TARGET)

run: run-react

clean:
	rm -rf $(WORK_DIR)

help:
	@echo "Available commands:"
	@echo ""
	@echo "  make react                   - compile a react"
	@echo "  make run-react               - compile and run react"
	@echo "  make run                     - compile and run react"
	@echo ""
	@echo "  make clean                   - remove compiled programs"

.PHONY: react run-react run clean help
