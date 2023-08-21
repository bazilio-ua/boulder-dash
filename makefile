INC=-I/opt/local/include

CFLAGS = -g -Wall $(INC)

LIBS=-L/opt/local/lib -lallegro -lallegro_main -lallegro_font -lallegro_primitives -lallegro_audio -lallegro_acodec -lallegro_image -lallegro_dialog

OBJECTS = utils.o sprite.o rockford.o amoeba.o boulder.o brick-wall.o butterfly.o diamond.o dirt.o exit.o firefly.o magic-wall.o map.o steel-wall.o explosion.o scoreboard.o audio.o game.o display.o keyboard.o main.o

all: boulder-dash

boulder-dash: $(OBJECTS)
	gcc $(OBJECTS) -o boulder-dash $(LIBS)

main.o: main.c
	gcc -c main.c $(CFLAGS);

utils.o: ./libs/utils.c ./libs/utils.h
	gcc -c ./libs/utils.c $(CFLAGS);

amoeba.o: ./libs/amoeba.c ./libs/amoeba.h
	gcc -c ./libs/amoeba.c $(CFLAGS);

boulder.o: ./libs/boulder.c ./libs/boulder.h
	gcc -c ./libs/boulder.c $(CFLAGS);

brick-wall.o: ./libs/brick-wall.c ./libs/brick-wall.h
	gcc -c ./libs/brick-wall.c $(CFLAGS);

butterfly.o: ./libs/butterfly.c ./libs/butterfly.h
	gcc -c ./libs/butterfly.c $(CFLAGS);

diamond.o: ./libs/diamond.c ./libs/diamond.h
	gcc -c ./libs/diamond.c $(CFLAGS);

dirt.o: ./libs/dirt.c ./libs/dirt.h
	gcc -c ./libs/dirt.c $(CFLAGS);

exit.o: ./libs/exit.c ./libs/exit.h
	gcc -c ./libs/exit.c $(CFLAGS);

firefly.o: ./libs/firefly.c ./libs/firefly.h
	gcc -c ./libs/firefly.c $(CFLAGS);

magic-wall.o: ./libs/magic-wall.c ./libs/magic-wall.h
	gcc -c ./libs/magic-wall.c $(CFLAGS);

map.o: ./libs/map.c ./libs/map.h
	gcc -c ./libs/map.c $(CFLAGS);

steel-wall.o: ./libs/steel-wall.c ./libs/steel-wall.h
	gcc -c ./libs/steel-wall.c $(CFLAGS);

explosion.o: ./libs/explosion.c ./libs/explosion.h
	gcc -c ./libs/explosion.c $(CFLAGS);

sprite.o: ./libs/sprite.c ./libs/sprite.h
	gcc -c ./libs/sprite.c $(CFLAGS);

rockford.o: ./libs/rockford.c ./libs/rockford.h
	gcc -c ./libs/rockford.c $(CFLAGS);

scoreboard.o: ./libs/scoreboard.c ./libs/scoreboard.h
	gcc -c ./libs/scoreboard.c $(CFLAGS);

audio.o: ./libs/audio.c ./libs/audio.h
	gcc -c ./libs/audio.c $(CFLAGS);

game.o: ./libs/game.c ./libs/game.h
	gcc -c ./libs/game.c $(CFLAGS);

display.o: ./libs/display.c ./libs/display.h
	gcc -c ./libs/display.c $(CFLAGS);

keyboard.o: ./libs/keyboard.c ./libs/keyboard.h
	gcc -c ./libs/keyboard.c $(CFLAGS);

clean:
	rm -f *.o

purge:	clean
	rm -f boulder-dash
