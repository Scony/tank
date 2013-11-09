CFLAGS=-Wall
LDFLAGS=-lalleg
OBJS=main.o Exception.o TutorialGame.o Game.o Spriter.o Map.o TutorialMap.o Point.o Terrain.o BrickTerrain.o ConcreteTerrain.o
OBJS+=PavementTerrain.o BushTerrain.o WaterTerrain.o Tank.o PlayerTank.o Player2Tank.o Wrapper.o TankWrapper.o
OBJS+=WrapperBox.o Bullet.o LineBullet.o BulletWrapper.o PolicyManager.o Bang.o SimpleBang.o BangWrapper.o LittleBang.o
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
