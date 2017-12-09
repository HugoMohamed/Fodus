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

fodus: main.o map.o personnage.o jeux.o sauvegarde.o ia.o menu.o knight.o archer.o
	$(CC) main.o map.o personnage.o jeux.o sauvegarde.o ia.o menu.o knight.o archer.o -o fodus $(LDFLAGS) $(LDLIBS)

archer.o: archer.c archer.h
	$(CC) $(CFLAGS) -c archer.c
	
knight.o: knight.c knight.h
	$(CC) $(CFLAGS) -c knight.c

map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

personnage.o: personnage.c personnage.h
	$(CC) $(CFLAGS) -c personnage.c

jeux.o: jeux.c jeux.h
	$(CC) $(CFLAGS) -c jeux.c

sauvegarde.o: sauvegarde.c sauvegarde.h
	$(CC) $(CFLAGS) -c sauvegarde.c

ia.o: ia.c ia.h
	$(CC) $(CFLAGS) -c ia.c

menu.o: menu.c menu.h
	$(CC) $(CFLAGS) -c menu.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -rf *.o *.~ fodus
