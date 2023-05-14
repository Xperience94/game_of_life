CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, build/%.o, $(SRCS))
TARGET = bin/game_of_life

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

build/%.o: %.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rm initial_*
