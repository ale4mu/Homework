# Compiler
CXX = g++
 
# Compiler flags
#CXXFLAGS = -Wall -std=c++17
 
# Source files
SRCS = test.cpp
 
# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)
 
# Output executable name
TARGET = test
 
# Default rule to build the target
all: $(TARGET)
 
# Rule to link object files into the executable
$(TARGET): $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -O2
# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -O2
run:$(TARGET)
	./test
report:
	xelatex report.tex 
# Clean rule to remove object files and executable
clean:
	rm -f $(OBJS) $(TARGET)
 
# Phony targets to avoid conflicts with file names
.PHONY: all clean

