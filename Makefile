CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2

SRCS = main.cpp ParseUtils.cpp REPL.cpp Registers.cpp VM.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = Instruction.h ParseUtils.h REPL.h Registers.h VM.h

TARGET = slave16

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
