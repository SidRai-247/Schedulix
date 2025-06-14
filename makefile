# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Source and headers
SRC = main.cpp
HEADERS = parser.h utils.h print.h fcfs.h rr.h spn.h srt.h hrrn.h fb1.h fb2i.h aging.h

# Executable name
EXEC = schedulix

# Default target
all: $(EXEC)

# Build the main executable
$(EXEC): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)

# Clean build artifacts
clean:
	rm -f $(EXEC)
