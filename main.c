#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "pendu.h"
#include "memory.h"
#include "puissance4.h"

#define MEMORY 1
#define PENDU 2
#define PUISSANCE4 3
#define EXIT 0

void Text_Menu()
{
    system("clear");
    int choice;

    while (1)
    {
        printf("*******************************\n");
        printf("*********** MENU JEUX **********\n");
        printf("*******************************\n");
        printf(" 1 -----> Memory\n 2 -----> Pendu\n 3 -----> Puissance 4\n 0 -----> End\n");
        printf(" choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            // Handle non-integer input
            while (getchar() != '\n')
                continue;
            continue;
        }
        switch (choice)
        {
        case MEMORY:
            play_memory();
            break;
        case PENDU:
            play_pendu();
            break;
        case PUISSANCE4:
            play_puissance4();
            break;
        case EXIT:
            printf("Exiting...\n");
            return;
        default:
            printf("Please enter a valid choice.\n");
            break;
        }
    }
}

int main()
{
    Text_Menu();
    return 0;
}
