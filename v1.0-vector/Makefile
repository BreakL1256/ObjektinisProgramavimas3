CXX = g++
CXXFLAGS = -O3 -std=c++20
RM = rm -f

# Source files
SRCS = gradeVector.cpp duomenuGeneravimas.cpp duomenuSkaiciavimai.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Additional TPP files
TPP_FILES = Vector.tpp

# Executable
EXECUTABLE = gradeVector

# Main target
all: $(EXECUTABLE)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile TPP files into object files
%.o: %.tpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files to generate the executable
$(EXECUTABLE): $(OBJS) $(TPP_FILES:.tpp=.o)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean rule
clean:
	$(RM) $(OBJS) $(TPP_FILES:.tpp=.o) $(EXECUTABLE)
