CC=g++
CFLAGS=-I.
LIBS=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

%.o: %.c ${wildcard ./*.h}
	$(CC) -c -o $@ $< $(CFLAGS)

tank-battle: tank-battle.o ${wildcard ./*.o}
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o 
	rm tank-battle
