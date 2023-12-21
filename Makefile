CC = gcc -g
CFLAGS = -Wall -Wextra -std=c99
OBJ = main.o connect.o hero.o flyer.o escape.o hollow.o utils.o

a5: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o a5 

main.o: main.c escape.h
	$(CC) $(CFLAGS) -c main.c

connect.o: connect.c connect.h escape.h
	$(CC) $(CFLAGS) -c connect.c

hero.o: hero.c escape.h utils.h flyer.h
	$(CC) $(CFLAGS) -c hero.c

flyer.o: flyer.c escape.h
	$(CC) $(CFLAGS) -c flyer.c

escape.o: escape.c escape.h connect.h utils.h flyer.h hero.h
	$(CC) $(CFLAGS) -c escape.c

hollow.o: hollow.c escape.h
	$(CC) $(CFLAGS) -c hollow.c

utils.o: utils.c escape.h utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f $(OBJ) a5