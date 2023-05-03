CXX = g++
CXXFLAGS = -std=c++11 -w #-fsanitize=address -fsanitize=undefined
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRC_FILES = $(wildcard ./src/*.cpp)
OBJ_FILES = $(SRC_FILES:./src/%.cpp=./obj/%.o)
BIN_NAME = bin/turtix.out
HDR_FILES := $(wildcard ./src/*.hpp)
MEDIA_PATH = ./files/
SCRIPT = ./files/pics/bg/gif_to_png.py

.PHONY: clean
.PHONY: run

$(BIN_NAME): $(OBJ_FILES) $(HDR_FILES)
	mkdir -p ./bin
	$(CXX) $(OBJ_FILES) $(CXXFLAGS) $(LFLAGS) -o $(BIN_NAME) -L$(MEDIA_PATH)

./obj/%.o: ./src/%.cpp
	mkdir -p ./obj
	$(CXX) $(CXXFLAGS) $(LFLAGS) -c $< -o $@ -I$(MEDIA_PATH)

init:
	pip install pillow
	python3 $(SCRIPT)

clean:
	rm -rf ./obj $(BIN_NAME)
	#rm -rf ./files/pics/bg/*.png

run: $(BIN_NAME)
	$(BIN_NAME) #|| clear