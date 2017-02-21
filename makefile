# Variables
CC = g++
CC_FLAGS = -w

# Names
EXEC = lagrange_polynomial
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)
	
# Object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# Clean
clean:
	rm -f $(OBJECTS)
