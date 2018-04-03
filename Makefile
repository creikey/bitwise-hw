CFILES=*.c

.PHONY: clean

main: *.o
	$(CC) $(CFLAGS) *.o -lctesting

debug: clean *.o
	$(CC) $(CFLAGS) *.o -lctesting -g

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	-rm *.o
	-rm *.gch
	-rm a.out
