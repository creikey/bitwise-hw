CFILES=*.c

.PHONY: clean

main: ofiles
	gcc *.o -lctesting

debug:
	gcc -c $(CFILES) -Wall -g
	gcc *.o -g -lctesting

ofiles: $(CFILES)
	gcc -c $(CFILES) -Wall

clean:
	-rm *.o
	-rm *.gch
	-rm a.out
