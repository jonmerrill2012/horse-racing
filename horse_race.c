#include<ncurses.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int won;
int race_length;
pthread_mutex_t print_mutex;

int favorites_votes;
int money;
int races_left;
int GAME_LENGTH = 10;
int last_choice;
int last_bet;
int NEEDED_MONEY = 10000;


struct horse_t {
        char name[50];
        int pos;
        int odds;
} horses[5];

void print_finish() {
        int j;
        printw("                        |");
        for (j = 0; j < race_length; j++) {
                printw("  ");
        }
        printw("|\n");
        return;
}

int compare(const void *s1, const void *s2) {
        struct horse_t *horse1 = (struct horse_t *) s1;
        struct horse_t *horse2 = (struct horse_t *) s2;

        return horse2->pos - horse1->pos;
}

void print_standings() {
        int i;
        struct horse_t horse_list[5];

        for (i = 0; i < 5; i++) {
                strcpy(horse_list[i].name, horses[i].name);
                horse_list[i].pos = horses[i].pos;
                horse_list[i].odds = horses[i].odds;
        }

        qsort(horse_list, 5, sizeof(struct horse_t), compare);
        
        printw("Standings:\n");
        printw("1st: %s\n", horse_list[0].name);
        printw("2nd: %s\n", horse_list[1].name);
        printw("3rd: %s\n", horse_list[2].name);
        printw("4th: %s\n", horse_list[3].name);
        printw("5th: %s\n", horse_list[4].name);
}

void print_odds() {
        int i;
        printw("Odds:\n");
        for (i = 0; i < 5; i++) {
                printw("%s: %d-1\n", horses[i].name, horses[i].odds);
        }
}

void print_title() {
        printw("    __  __                        ____             _            \n");
        printw("   / / / /___  _____________     / __ \\____ ______(_)___  ____ _\n");
        printw("  / /_/ / __ \\/ ___/ ___/ _ \\   / /_/ / __ `/ ___/ / __ \\/ __ `/\n");
        printw(" / __  / /_/ / /  (__  )  __/  / _, _/ /_/ / /__/ / / / / /_/ / \n");
        printw("/_/ /_/\\____/_/  /____/\\___/  /_/ |_|\\__,_/\\___/_/_/ /_/\\__, /  \n");
        printw("                                                       /____/   \n");
        printw("-------------------------------------------------------------------------------\n");
}

void printscr(int idx) {
        int i;
        int j;

        if (won != -1){
                return;
        }

        pthread_mutex_lock(&print_mutex);

        clear();
        print_title();
        print_finish();
        for (i = 0; i < 5; i++) {

                for (j = 0; j < horses[i].pos; j++) {
                        printw("  ");
                }
                printw("%s: x\n", horses[i].name);

                print_finish();
        }
        printw("-------------------------------------------------------------------------------\n");
        printw("\n%s has been bet on with $%d!\n\n", horses[last_choice].name, last_bet);
        print_standings();
        printw("----------\n");
        print_odds();
        if(horses[idx].pos > race_length && won == -1) {
                printw("\n\n%s has won!!! (Press a key to exit)\n", horses[idx].name);
                won = idx;
                getch();
        } 
        refresh();
        
        pthread_mutex_unlock(&print_mutex);
        return;
}

void * horse(void * arg) {
        int idx = *((int *) arg);
        free(arg);

        int odds = horses[idx].odds;

        while (1) {
                if (odds % 2 == 0) {
                        sleep(rand() % (odds/2 + 1) + 1);
                } else {
                        if (rand() % 2 == 0) {
                                sleep(rand() % (odds/2 + 1) + 1);
                        } else {
                                sleep(rand() % ((odds + 1)/2 + 1) + 1);
                        }
                } 
                horses[idx].pos++;
                printscr(idx);
                if (won != -1) {
                    break;
                }
        }
}

void get_horse_name(struct horse_t * horse){
        const char *adj[47] = {
                                  "Lightning",
                                  "Bold",
                                  "Salsa",
                                  "Sunny with a",
                                  "The Only",
                                  "Georgia's",
                                  "Tennessee",
                                  "Screamin'",
                                  "Cow",
                                  "Fast",
                                  "Hairy",
                                  "Tubby",
                                  "Jumpin'",
                                  "For",
                                  "Hangin' with",
                                  "Portland",
                                  "Humboldt",
                                  "Cheesy",
                                  "Bright",
                                  "Flat",
                                  "Pancake",
                                  "Jelly-Filled",
                                  "Evil",
                                  "Nice",
                                  "Slim",
                                  "Bet on",
                                  "Don't Forget",
                                  "Sexy",
                                  "Lucky",
                                  "Lovely",
                                  "Smokey",
                                  "Handsome",
                                  "Snatchin'",
                                  "Hungry",
                                  "Fiesta",
                                  "Chips 'n",
                                  "Topdecked",
                                  "Party with",
                                  "The lonely",
                                  "Half",
                                  "Super",
                                  "Racin'",
                                  "Wrastlin'",
                                  "Kentucky",
                                  "Roses are",
                                  "Dinner with",
                                  "Bloodfury"
                              };
        const char *nouns[67] = {
                                    "Lightning",
                                    "Salsa",
                                    "Chance",
                                    "Tennessee",
                                    "Pride",
                                    "Georgia",
                                    "Bryan",
                                    "Void",
                                    "Icehowl",
                                    "Cowboy",
                                    "Git Commit",
                                    "Mexican",
                                    "Butter",
                                    "Cat Woman",
                                    "Comcast",
                                    "Anderson",
                                    "Mango",
                                    "Mouse",
                                    "America",
                                    "Body Mass",
                                    "Hippo",
                                    "Meat",
                                    "Robot",
                                    "Gary",
                                    "Scout",
                                    "Franky",
                                    "Bella",
                                    "Tank",
                                    "Gus",
                                    "Nostalgia",
                                    "Dancer",
                                    "Blue",
                                    "Pop",
                                    "Ma",
                                    "Bush",
                                    "Reagan",
                                    "Zippo",
                                    "Love",
                                    "Mario",
                                    "Red",
                                    "Dan",
                                    "Biscuit",
                                    "Superman",
                                    "Winner",
                                    "Insurance",
                                    "Lightbulb",
                                    "Morning",
                                    "Baby",
                                    "Wizard",
                                    "Diablo",
                                    "Blueberry",
                                    "Apple",
                                    "Hank",
                                    "Taco",
                                    "Honey",
                                    "Toe-jam",
                                    "Rock",
                                    "Licky",
                                    "Horse",
                                    "Banjo",
                                    "Lost Love",
                                    "Egyptian",
                                    "Vodka",
                                    "Rum",
                                    "Cider",
                                    "Trouble",
                                    "Potion"
                                };

        char name[50] = "";
        if (rand() % 3 > 0){
                strcat(name, adj[rand() % 47]);
                strcat(name, " ");
        }

        strcat(name, nouns[rand() % 67]);
        int length = strlen(name);

        int i;
        // longest name is: "Sunny with a Lightning" (22 chars) don't judge me
        char name_with_spaces[23] = "";
        for (i = 0; i < 22 - length; i++)  {
                strcat(name_with_spaces, " ");
        }
        strcat(name_with_spaces, name);
        strcpy(horse->name, name_with_spaces);
}

void print_intro() {
        clear();
        print_title();
        printw("Welcome to Horse Racing (tm)!\n");
        printw("Written by Jon Merrill\n\n\n");

        printw("Story:\n");
        printw("  You are a gambling addict whose latest fix is betting on horse racing!\n");
        printw("  Unfortunately, you've made some bad bets and taken some even worse loans.\n");
        printw("  You owe the mob a large amount of money, and you only have a few days to pay.\n");
        printw("\n  Your grandmother bailed you out again and gave you $500 to get back on your feet.\n");
        printw("  Of course, you decided to take it to the tracks.\n\n");
        printw("  You have 10 days to make $%d before the mob breaks your knee caps.\n", NEEDED_MONEY);
        printw("  Good luck!\n\n");

        printw("Instructions:\n");
        printw("  You have $500. Each day you will select 1 of 5 horses to bet on.\n");
        printw("  You must make $%d in 10 days.\n", NEEDED_MONEY);
        printw("  You can only bet on the clear favorite 3 times.\n\n");
        printw("  If you run out of money, you lose your knee caps.\n");
        printw("  If you don't have $%d after 10 days, you lose your knee caps.\n\n", NEEDED_MONEY);

        printw("There are 4 unique endings.\n");
        printw("Press any key to continue");
        refresh();

        getch();
        return;
}

void print_menu() {
        clear();
        print_title();
        printw("Day %d\n", GAME_LENGTH - races_left + 1);
        printw("Money: $%d\n", money);
        printw("Favorite bets left: %d\n\n", favorites_votes);

        print_odds();

        return;
}

// returns 0 on success, 1 on invalid option, 2 on too many favorite picks
int validate_pick(int pick){
        int i;
        int best_odds = 100;
        int illegal_bet = -1;

        // there is a better way to check this...
        if (pick != 1 && pick != 2 && pick != 3 && pick != 4 && pick != 5){
                return 1;
        }

        for (i = 0; i < 5; i++){
                if (horses[i].odds < best_odds){
                        best_odds = horses[i].odds;
                        illegal_bet = i + 1;
                } else if (horses[i].odds == best_odds){
                        illegal_bet = -1;
                }
        }


        if (illegal_bet == -1) {
                return 0;
        }

        if (pick == illegal_bet) {
                if (favorites_votes > 0) {
                        favorites_votes--;
                        return 0;
                }
                return 2;
        }

        return 0;
}

void main_menu(){
        int pick = 0;
        int pick_result = 0;
        int bet;
        int bet_result = 0;

        do {
                print_menu();
                if (pick_result == 1) {
                        printw("Invalid choice...");
                } else if (pick_result == 2) {
                        printw("\nYou have already bet on the favorite 3 times!");
                } 

                printw("\nChose a horse (1 - 5):");
                refresh();
                scanw("%d", &pick);
                pick_result = validate_pick(pick);
                
        } while (pick_result != 0);

        do {
                print_menu();
                printw("\n%s is your chosen horse!\n", horses[pick-1].name);
                if (bet_result == 1) {
                        printw("\nInvalid bet...");
                } else if (bet_result == 2) {
                        printw("\nYou don't have that much money!");
                }

                printw("\nEnter an amount to bet: $");
                refresh();
                scanw("%d", &bet);
                if (bet > money) {
                        bet_result = 2;
                } else if (bet == 0) {
                        bet_result = 1;
                } else {
                        bet_result = 0;
                }
        } while (bet_result != 0);

        last_bet = bet;
        last_choice = pick - 1;

        money = money - bet;
        }

void print_bet_win() {
        clear();
        print_title();
        printw("Congratulations! Your horse won!\n");
        printw("  You won $%d!\n", last_bet * horses[won].odds);
        printw("\n\n(press any key to continue)");
        refresh();
        getch();
}

void print_bet_loss() {
        clear();
        print_title();
        printw("Oh no... Your horse didn't win...\n");
        printw("  You lost $%d\n", last_bet);
        printw("\nThe mob is watching.\n");
        printw("\n\n(press any key to continue)");
        refresh();
        getch();
}

void print_final_win() {
        clear();
        print_title();
        printw("You hear a knock on the door, the day has come.\n");
        printw("Luckily, you managed to raise the money.\n");
        printw("\nYou pull the %d dollars out of your pocket and open the door.\n", NEEDED_MONEY);
        printw("\n\"Time's up!\" barks a mean looking Italian man as he smacks a crowbar on his hand.\n");
        printw("You slowly hand him the money and nervously smile.\n");
        printw("\nHe counts the money as he lazily turns around.\n");
        printw("\"Hope we can do business again sometime,\" he chuckles as he walks down the front steps.\n");
        printw("You close the door, relieved.\n");
        printw("\n\n(press any key to continue)");
        refresh();
        getch();

}

void print_final_loss() {
        clear();
        print_title();
        printw("You tremble in fear as you hear a knock on your door.\n");
        printw("Time's up. You don't have the money you owe the mob.\n");
        printw("\nYou open the door.\n");
        if (money == 0) {
                printw("\n\"You have NOTHING?\" yells the burly Italian man.\n");
                printw("\"You had %d days and you came up with NO MONEY?\"\n", GAME_LENGTH);
                printw("\nYou try to explain about the horse racing, but it comes out high pitched and jumbled.\n");
                printw("The man looks at you with disgust and pulls out a crow bar.\n");
                printw("Everything goes dark.");
        } else if (money < NEEDED_MONEY/2) {
                printw("\n\"How did you do?\" asks a menacing Italian man.\n");
                printw("You hand him the %d dollars you made and try to explain.\n", money);
                printw("He cuts you off with a look of disgust.\n");
                printw("\"I tipped more than this at Tuesday's dinner,\" the man mocks.\n");
                printw("\nHe sighs and pulls a crow bar from behind his back.\n");
                printw("Everything goes dark.");
        } else {
                printw("\n\"I saw you at the tracks making a big scene,\" grumbles a scarred Italian man.\n");
                printw("\"I sure hope you made enough to pay your... bill.\"\n");
                printw("You hand over the %d dollars you made and try not to make eye contact.\n", money);
                printw("He shakes his head slowly.\n");
                printw("\nHe pulls out a crow bar and smacks it against his leathery hand.\n");
                printw("\"I'm going to take this, but your debt isn't settled,\" he says.\n");
                printw("\"You have another 10 days, but this money here is your late fee.\"\n");
                printw("He chuckles as he walks off.");
        }
        printw("\n\n(press any key to continue)");
        refresh();
        getch();
}
int main(int argc, char **argv) {
        int i;
        pthread_t threads[5];
        time_t t;

        race_length = 25;
        money = 500;
        favorites_votes = 3;
        races_left = GAME_LENGTH;

        srand((unsigned) time(&t));
        pthread_mutex_init(&print_mutex, NULL);

        initscr();
        print_intro();

        while (races_left > 0 && money > 0){
                won = -1;
                for (i = 0; i < 5; i++){
                        get_horse_name(&horses[i]);
                        horses[i].odds = rand() % 6 + 2;
                        horses[i].pos = 0;
                }

                main_menu();

                printscr(-1);
                for (i = 0; i < 5; i++) {
                        int *arg = malloc(sizeof(*arg));
                        *arg = i;
                        pthread_create(&threads[i], NULL, horse, arg);
                }
                for (i = 0; i < 5; i++) {
                        pthread_join(threads[i], NULL);
                }
                if (won == last_choice) {
                        money = money + (horses[won].odds * last_bet);
                        print_bet_win();
                        if (money > NEEDED_MONEY) {
                                break;
                        }
                } else {
                        print_bet_loss();
                }
                races_left--;
        }
        if (money < NEEDED_MONEY || races_left == 0) {
                print_final_loss();
        } else {
                print_final_win();
        }
        endwin();
        pthread_mutex_destroy(&print_mutex);

        return 0;
}
