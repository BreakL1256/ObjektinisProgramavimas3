# Compiler and flags
CXX = g++
CXXFLAGS = -O3 -std=c++20
RM = rm -f

# Source files
SRCS = gradeVector.cpp duomenuGeneravimas.cpp duomenuSkaiciavimai.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable
EXECUTABLE = gradeVector

# Main target
all: $(EXECUTABLE)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files to generate the executable
$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean rule
clean:
	$(RM) $(OBJS) $(EXECUTABLE)