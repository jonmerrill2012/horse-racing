all: horse_race

horse_race: horse_race.c
	gcc -pthread  horse_race.c -lncurses -o horse_race

clean:
	rm -f horse_race
