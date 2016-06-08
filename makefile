CC = gcc
LD = gcc
CCFLAGS = -std=c99
OBJ = my_stack.o 26.o stack_s.o sort.o
26: $(OBJ)
	$(LD) -o 26 $(OBJ) -lm
26.o: 26.c my_stack.h stack_s.h
	$(CC) $(CCFLAGS) -c 26.c
my_stack.o: my_stack.c my_stack.h
	$(CC) $(CCFLAGS) -c my_stack.c
stack_s.o: stack_s.c stack_s.h
	$(CC) $(CCFLAGS) -c stack_s.c
sort.o: sort.c stack_s.h my_stack.h
	$(CC) $(CCFLAGS) -c sort.c
