# Makefile for Mandelbrot Set Generation Assignment

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O3
LDFLAGS = -lm
OMPFLAGS = -fopenmp

# Source files
MAIN_SRC = main.c
SEQ_IMPL_SRC = mandelbrot_seq.c
PAR_IMPL_SRC = mandelbrot_par.c

# Object files
MAIN_OBJ = $(MAIN_SRC:.c=.o)
SEQ_IMPL_OBJ = $(SEQ_IMPL_SRC:.c=.o)
PAR_IMPL_OBJ = $(PAR_IMPL_SRC:.c=.o)

# Executable names
SEQ_TARGET = mandelbrot_seq
PAR_TARGET = mandelbrot_par

# Default target
all: $(SEQ_TARGET) $(PAR_TARGET)

# Rule to build the sequential executable
$(SEQ_TARGET): $(MAIN_OBJ) $(SEQ_IMPL_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(OMPFLAGS)

# Rule to build the parallel executable
$(PAR_TARGET): $(MAIN_OBJ) $(PAR_IMPL_OBJ)
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $@ $^ $(LDFLAGS) $(OMPFLAGS)

# --- CORRECTED RULES FOR COMPILING OBJECT FILES ---

# Rule for standard object files (main.o, mandelbrot_seq.o)
$(MAIN_OBJ) $(SEQ_IMPL_OBJ): %.o: %.c mandelbrot.h
	$(CC) $(CFLAGS) -c $< -o $@

# Specific rule for the parallel object file that adds OMPFLAGS
$(PAR_IMPL_OBJ): $(PAR_IMPL_SRC) mandelbrot.h
	$(CC) $(CFLAGS) $(OMPFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f *.o $(SEQ_TARGET) $(PAR_TARGET)

.PHONY: all clean