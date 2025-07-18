# Compiler and flags
CXX = g++
# UPDATED: C++ standard is now c++17
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -static-libstdc++
LDFLAGS =

# Source and object files
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = build-iso

# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS)

# Compiling source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
