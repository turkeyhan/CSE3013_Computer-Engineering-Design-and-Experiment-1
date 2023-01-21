cc = g++
cflags = -W -g
target = main

objects = main.o rangearray.o array.o

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)

%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

main.o rangearray.o : RangeArray.h
main.o array.o RangeArray.h : Array.h

.PHONY : clean
clean :
	rm $(target) $(objects)
