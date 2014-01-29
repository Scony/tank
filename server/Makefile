CFLAGS=-Wall
LDFLAGS=-lPocoNet -lPocoFoundation
OBJS=main.o Tank.o Game.o Map.o
EXE=main.out

all: $(EXE)

main.out: $(OBJS)
	g++ $(OBJS) -o $(EXE) $(LDFLAGS)

.SUFFIXES:
.SUFFIXES: .o .cpp

.cpp.o:
	g++ $(CFLAGS) -c $<

clean:
	rm -f *~ *.o $(EXE)

size:
	wc -l *.*pp *.dat *.map

todo:
	ack-grep todo

mapgen:
	g++ mapgen.cpp -o mapgen.out

.PHONY: clean
