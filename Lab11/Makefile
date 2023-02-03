# Makefile z ChatGPT :)

# Define directories
SDIR = src/
IDIR = include/

# Define the compiler to use
CXX = g++

# Define the flags to pass to the compiler
CXXFLAGS = -I$(IDIR)

# Define the target
TARGET = Scheduler_sim

# Define the sources
SOURCES = $(SDIR)main.cpp $(SDIR)scheduler.cpp

# Define the objects
OBJECTS = $(SOURCES:.cpp=.o)

# Define the default target
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Define a pattern rule for building objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Define a target to clean up the build directory
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)
