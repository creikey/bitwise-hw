CFILES=*.c

.PHONY: clean

main: ofiles
	gcc *.o

debug: ofiles
	gcc *.o -g

ofiles: $(CFILES)
	gcc -c $(CFILES) -Wall

clean:
	-rm *.o
	-rm *.gch
