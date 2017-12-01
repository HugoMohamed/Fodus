#
# Mettre ici vos options de compilation.
#
CFLAGS= -DDEBUG -g -Wall `pkg-config --cflags MLV`

#
# Mettre ici les options qui devront être passées à l'éditeur de liens.
# Par exemple : -L/directory
#
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`

#
# Mettre ici les noms des bibliothèques et leurs locations.
# Par exemple : -lpthread
#
LDLIBS=`pkg-config --libs-only-l MLV`

###############################################################################
CC=gcc

jeux: main.o map.o personnage.o
	$(CC) main.o map.o personnage.o -o jeux $(LDFLAGS) $(LDLIBS)

map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

personnage.o: personnage.c personnage.h
	$(CC) $(CFLAGS) -c personnage.c

main.o: main.c map.h personnage.h
	$(CC) $(CFLAGS) -c main.c

map.o: map.c map.h

clean:
	rm -rf *.o *.~ main


