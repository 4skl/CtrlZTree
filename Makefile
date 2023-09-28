CC=gcc
CFLAGS=-I. -static
INPUT_C=main.c
OUTPUT=CtrlZTree.exe
LIBS=-lcrypto

main:
	$(CC) $(CFLAGS) -o $(OUTPUT) $(INPUT_C) $(LIBS)

run: main
	$(OUTPUT)