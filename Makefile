CXX = g++
CXXFLAGS = -std=c++11 -Wall #-fsanitize=address -fsanitize=undefined
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRC_FILES = $(wildcard ./src/*.cpp)
OBJ_FILES = $(SRC_FILES:./src/%.cpp=./obj/%.o)
BIN_NAME = bin/turtix.out
HDR_FILES := $(wildcard ./src/*.hpp)
MEDIA_PATH = ./files/

.PHONY: clean
.PHONY: run

$(BIN_NAME): $(OBJ_FILES) $(HDR_FILES)
	$(CXX) $(OBJ_FILES) $(CXXFLAGS) $(LFLAGS) -o $(BIN_NAME) -L$(MEDIA_PATH)

./obj/%.o: ./src/%.cpp
	mkdir -p ./obj
	$(CXX) $(CXXFLAGS) $(LFLAGS) -c $< -o $@ -I$(MEDIA_PATH)

clean:
	rm -rf ./obj $(BIN_NAME)

run: $(BIN_NAME)
	$(BIN_NAME)