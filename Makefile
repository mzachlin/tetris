CC := g++
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image -lSDL2_ttf -lm -std=c++11

# Add source files here
SRCS := grid.cpp tetris.cpp piece.cpp 

# Generate names of object files
OBJS := $(SRCS:.cpp=.o)

# Name of executable
EXEC := tetris

# Default recipe
all: $(EXEC)

# Recipe for building the final executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Recipe for building object files
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

# Recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
