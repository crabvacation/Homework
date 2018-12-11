/*Nicco Bravata
 *COP 3223C-18Fall 0R06
 *Project 8 - 12/2/18
 *This program tests a ninja's stealth and observation abilities, and the lucky ninjas who pass will graduate from the ninja academy!
 version: 1.0
 */

//pre-processor directives
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//declare the structures used to store information about the map and the ninjas
struct map {
    int searchval;
    int item;
    int found;
};

struct ninja {
    int search;
    int stealth;
};

void printninja(struct ninja *);

int main(int argc, char **argv) {
    FILE *ifp = NULL;
    char mapname[20];
    //declare arrays to store information on individual attributes of each ninja and the map
    struct map temple[3][3];
    struct ninja skills[4];
    //declare lots and lots of variables so you don't run out
    int h, i, j, k, l, m, n, evasion, flag, foundit, chance, caught, wincounter = 0, condition = 0;

    printf("You have arrived at the Temple!\n");

    //establish while loop to make sure you get the right name of the file you need
    while (ifp == NULL) {
        printf("What is the name of your map?\n");
        scanf("%s", (char *) &mapname);

        ifp = fopen(mapname, "r");

        if (!ifp) {
            perror("Failed to open your map file: ");
        }
    }

    //populate the structure arrays with the numbers from the file
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            fscanf(ifp, "%d", &temple[i][j].searchval);
            fscanf(ifp, "%d", &temple[i][j].item);
        }
    }

    for (i = 0; i < 4; i++) {
        fscanf(ifp, "%d", &skills[i].search);
        fscanf(ifp, "%d", &skills[i].stealth);
    }

    //close the file
    fclose(ifp);

    //establish the time limit and print the initial ninja stat menu
    printf("You have 2 hours left to collect the relics.\n");
    printf("Ninja  Search  Stealth\n");

    for (i = 0; i < 4; i++) {
        printf("%d\t", i + 1);
        printf("%d\t", skills[i].search);
        printf("%d\n", skills[i].stealth);
    }

    //make a for loop that calls each ninja once during the first hour
    for (h = 0; h < 4; h++) {
        printf("Where would you like to send ninja %d?\n", h + 1);
        //use an if statement in a nested for loop to determine what is revealed on the map
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (temple[i][j].searchval < 0) {
                    if (temple[i][j].searchval < -6)
                        printf("TRAP\t");
                    else if(temple[i][j].searchval < -5 && temple[i][j].searchval > -9)
                        printf("NOTHING\t");
                    else if (temple[i][j].searchval < 0)
                        printf("RELIC\t");
                } else {
                    printf("%d", temple[i][j].searchval);
                    printf("s\t");
                }
            }

            printf("\n");
        }

        //scan player input
        scanf("%d %d", &k, &l);

        //use time as the seed and calculate evasion
        evasion = skills[h].stealth;
        srand(time(0));
        chance = rand() % (evasion + 1);

        if (chance == evasion)
            caught = 1;
        else
            caught = 0;

        flag = caught;

        if (flag == 1)
            printf("Your ninja has been caught!\n");
        else {
            foundit = temple[k - 1][l - 1].item;
            //if your ninja's evasion is high enough, determine what they find
            //also change the search value so the map know what to reveal when printed
            if (foundit == 0) {
                printf("Your ninja fell into a trap!\n");
                skills[h].stealth--;
                temple[k - 1][l - 1].searchval = -10;
            } else if (foundit == 5) {
                printf("You have found NOTHING!\n");
                temple[k - 1][l - 1].searchval = -6;
            } else if (foundit == 4) {
                printf("You have found a SPOOKY MASK!\n");
                temple[k - 1][l - 1].searchval = -4;
            } else if (foundit == 3) {
                printf("You have found a JADE STATUE!\n");
                temple[k - 1][l - 1].searchval = -3;
            } else if (foundit == 2) {
                printf("You have found an ANCIENT SCROLL!\n");
                temple[k - 1][l - 1].searchval = -2;
            } else if (foundit == 1) {
                printf("You have found the KATANA OF LEGEND!\n");
                temple[k - 1][l - 1].searchval = -1;
            }
        }

        //for each relic you find, increase a win counter
        for (m = 0; m < 3; m++) {
            for (n = 0; n < 3; n++) {
                if (temple[m][n].searchval < 0 && temple[m][n].searchval > -5)
                    wincounter++;
            }
        }

        //if the win counter reaches 4, you've found all the relics and you win!
        if (wincounter == 4)
        {
            printf("You have retrieved all the relics!\n");
            h = 5;
            //if you've won the game, set a win flag so the game doesn't continue
            condition++;
        }
        //if the win counter doesn't reach 4, you haven't won yet and the counter is reset
        else
            wincounter = 0;

    }

    //start the 2nd hour if the win flag is false
    if (condition == 0) {
        printf("You have 1 hour left to collect the relics.\n");
        printf("Ninja  Search  Stealth\n");

        for (i = 0; i < 4; i++) {
            printf("%d\t", i + 1);
            printf("%d\t", skills[i].search);
            printf("%d\n", skills[i].stealth);
        }

        //rinse and repeat from hour 1
        for (h = 0; h < 4; h++) {
            printf("Where would you like to send ninja %d?\n", h + 1);

            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    if (temple[i][j].searchval < 0) {
                        if( temple[i][j].searchval < -6)
                            printf("TRAP\t");
                        else if (temple[i][j].searchval < -5 && temple[i][j].searchval > -9)
                            printf("NOTHING\t");
                        else if (temple[i][j].searchval < 0)
                            printf("RELIC\t");
                    } else {
                        printf("%d", temple[i][j].searchval);
                        printf("s\t");
                    }
                }
                printf("\n");
            }

            scanf("%d %d", &k, &l);
            evasion = skills[h].stealth;

            srand(time(0));
            chance = rand() % (evasion + 1);

            if (chance == evasion)
                caught = 1;
            else
                caught = 0;

            flag = caught;

            if (flag == 1)
                printf("Your ninja has been caught!\n");
            else {
                foundit = temple[k - 1][l - 1].item;

                if (foundit == 0) {
                    printf("Your ninja fell into a trap!\n");
                    skills[h].stealth--;
                    temple[k - 1][l - 1].searchval = -10;
                } else if (foundit == 5) {
                    printf("You have found NOTHING!\n");
                    temple[k - 1][l - 1].searchval = -6;
                } else if (foundit == 4) {
                    printf("You have found a SPOOKY MASK!\n");
                    temple[k - 1][l - 1].searchval = -4;
                } else if (foundit == 3) {
                    printf("You have found a JADE STATUE!\n");
                    temple[k - 1][l - 1].searchval = -3;
                } else if (foundit == 2) {
                    printf("You have found an ANCIENT SCROLL!\n");
                    temple[k - 1][l - 1].searchval = -2;
                } else if (foundit == 1) {
                    printf("You have found the KATANA OF LEGEND!\n");
                    temple[k - 1][l - 1].searchval = -1;
                }
            }

            for (m = 0; m < 3; m++) {
                for (n = 0; n < 3; n++) {
                    if (temple[m][n].searchval < 0 && temple[m][n].searchval > -5)
                        wincounter++;
                }
            }

            if (wincounter == 4) {
                printf("You have retrieved all the relics!\n");
                h = 5;
                condition++;
            } else
                wincounter = 0;

        }

    }

    //use the wincounter to determine how many relics you've found
    for (m = 0; m < 3; m++) {
        for (n = 0; n < 3; n++) {
            if (temple[m][n].searchval < 0 && temple[m][n].searchval > -5)
                wincounter++;
        }
    }

    //end the game and notify the player of how many relics they retrieved
    printf("You are forced to leave the temple. You retrieved %d relic(s) for the Ninja Academy!", wincounter);

    //end the code
    return 0;
}

