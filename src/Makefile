CFLAGS=-Wall
LDFLAGS=-lalleg
OBJS=main.o Exception.o TutorialGame.o Game.o Spriter.o Map.o TutorialMap.o Point.o
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

.PHONY: clean
