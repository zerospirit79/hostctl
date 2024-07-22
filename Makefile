 ```makefile
    CC = gcc
    CFLAGS = -Wall -g
    LDFLAGS = -lstdc++

    all: hosts

    hosts: hosts.o
        $(CC) $(LDFLAGS) hosts.o -o hosts

    hosts.o: hosts.c hosts.h
        $(CC) $(CFLAGS) -c hosts.c

    clean:
        rm -f hosts *.o
    ```
