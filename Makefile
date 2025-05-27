CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2

SRCS = main.cpp ParseUtils.cpp REPL.cpp Registers.cpp VM.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = Instruction.h ParseUtils.h REPL.h Registers.h VM.h

TARGET = slave16
DEBUG_TARGET = slave16_debug
DEBUG_OBJS = $(SRCS:.cpp=.debug.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

debug: CXXFLAGS := -std=c++20 -Wall -Wextra -g -DDEBUG
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(DEBUG_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.debug.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(DEBUG_OBJS) $(TARGET) $(DEBUG_TARGET)

.PHONY: all clean debug
