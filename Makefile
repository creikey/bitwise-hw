CFILES=*.c

.PHONY: clean

main: ofiles
	gcc *.o

ofiles: $(CFILES)
	gcc -c $(CFILES) -Wall

clean:
	-rm *.o
	-rm *.gch
