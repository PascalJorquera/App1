CC = gcc
# CFLAGS = -InombreCarpeta 
SRC = test.c metrics.c orders.c
OUT = 1

work:
	$(CC)  $(SRC) -o $(OUT)

test:
	gcc -o test test.c orders.c metrics.c




clean:
	rm -f app1 test
