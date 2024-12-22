GCC = gcc

C_FLAGS =
L_FLAGS =

main: main.c
	$(GCC) -o main main.c $(C_FLAGS) ${L_FLAGS}