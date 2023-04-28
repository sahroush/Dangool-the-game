CXX = g++
CXXFLAGS = -std=c++11 -Wall -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio #-fsanitize=address -fsanitize=undefined
SRCDIR = src
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)
MAIN = bin/turtix.out
HDRS := $(wildcard $(SRCDIR)/*.hpp)

.PHONY: clean

all: $(MAIN)

$(MAIN): $(OBJS) $(HDRS)
	$(CXX) $ $(OBJS) $(CXXFLAGS) -o $(MAIN)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MAIN)