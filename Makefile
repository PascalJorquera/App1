CC = gcc
SRC = main.c metrics.c orders.c
OUT = app1

start:
	$(CC)  $(SRC) -o $(OUT)




clean:
	rm -f app1 test
