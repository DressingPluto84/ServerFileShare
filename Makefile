CFLAGS := -Wall -g

all: mainProg serverForFileSharing clean

mainProg: mainProg.o parseUtils.o userHasher.o centralList.o
	gcc $(CFLAGS) -o $@ $^
	
serverForFileSharing: serverForFileSharing.o centralList.o userHasher.o
	gcc $(CFLAGS) -o $@ $^

%.o: %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o
