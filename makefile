all: horse_race

horse_race: horse_race.c
	gcc -pthread -lncurses horse_race.c -o horse_race

clean:
	rm -f horse_race
