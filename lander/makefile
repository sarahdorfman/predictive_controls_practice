CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra
# If the code uses Eigen, uncomment and adjust:
# CXXFLAGS += -I/usr/include/eigen3
LDFLAGS  ?=
LDLIBS   ?=

TARGET := app
SRCS   := main.cpp kalman.cpp DARE.cpp
OBJS   := $(SRCS:.cpp=.o)
DEPS   := $(OBJS:.o=.d)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

-include $(DEPS)
