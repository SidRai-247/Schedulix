# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Executable name
EXEC = scheduler

# Default target
all: $(EXEC)

# Build the main executable
$(EXEC): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(EXEC)

# Clean build artifacts
clean:
	rm -f $(EXEC)
