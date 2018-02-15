# Which compiler to use
CC = clang

# Compiler flags go here.
CFLAGS = -g -Wall

# Linker flags go here.
LDFLAGS = -lcomedi -lm

# list of sources
ELEVSRC = main.c elev.c io.c prioritizer.c orders.c assorted_funcs.c

# program executable file name.
TARGET = heis

# top-level rule, to compile everything.
all: $(TARGET)

# Define all object files.
ELEVOBJ = $(ELEVSRC:.c=.o)

# rule to link the program
$(TARGET): $(ELEVOBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile: create object files from C source files.
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

# rule for cleaning re-compilable files.
clean:
	rm -f $(TARGET) $(ELEVOBJ)

rebuild:	clean all

.PHONY: all rebuild clean


#Martin Korsgaard, 2006