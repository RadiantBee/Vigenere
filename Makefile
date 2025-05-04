# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -pedantic -std=c++23

# Target executable
TARGET = main

# Source dir
SOURCEDIR = src

# Build dir
BUILDDIR = build

# Source files
SOURCES := main.cpp $(wildcard $(SOURCEDIR)/*.cpp)

# Object files
OBJECTS = $(patsubst %.cpp, $(BUILDDIR)/%.o, $(notdir $(SOURCES)))

# Build target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile each .cpp to .o
$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Same to main.cpp
$(BUILDDIR)/main.o: main.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build dir
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Clean up
clean:
	rm -rf $(BUILDDIR) $(TARGET)

# Phony targets
.PHONY: clean

