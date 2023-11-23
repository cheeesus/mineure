#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define MAX 36
#define FACILE 12
#define MOYEN 16
#define DIFFICILE 24
#define EXPERT 36

int indx = 0;
int matched_cells[MAX][MAX];
void initialize_matched_cells(int numRows, int numCols)
{
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            matched_cells[row][col] = 0;
        }
    }
}

void Shuffle_Table_1D(int *array, int niveau)
{
    for (int i = 0; i < niveau; i++)
    {
        int j = rand() % (niveau);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void Fill_Table_1D(int niveau, int *numbers)
{
    int num = 1;
    for (int i = 0; i < niveau; i++)
    {
        numbers[i] = num;
        numbers[++i] = num;
        num++;
    }
}

void Fill_Table_2D(int numRows, int numCols, int niveau, int *table, int *numbers)
{
    int numbersIndex = 0;
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            table[row * numCols + col] = numbers[numbersIndex++];

            if (row > 0 && table[row * numCols + col] == table[row * numCols + col - 1])
            {
                int nextIndex = (numbersIndex < (niveau)-1) ? numbersIndex : numbersIndex - 2;
                int temp = table[row * numCols + col];
                table[row * numCols + col] = numbers[nextIndex];
                numbers[nextIndex] = temp;
            }
        }
    }
}
void Display_Header(int niv, int rows, int cols)
{
    system("clear");
    printf("******************************************************\n");
    printf("*  Niveau (%d) => %d Lignes x %d Colonnes = (%d)Cases  *\n", niv, rows, cols, cols * rows);
    printf("******************************************************\n");
    printf("**********************  GTILLE ***********************\n");
    printf("******************************************************\n");
}
void Display_Table_2D(int niv, int numRows, int numCols, int *table)
{
    Display_Header(niv, numRows, numCols);
    printf("\n Colonne>");
    for (int i = 0; i < numCols; i++)
    {
        printf("%6d", i);
    }
    printf("\n Lignes |");
    for (int i = 1; i <= numCols; i++)
    {
        printf("    __");
    }
    printf("\n");
    for (int row = 0; row < numRows; row++)
    {
        printf("\n    %c   |", 'A' + row);
        for (int col = 0; col < numCols; col++)
        {
            printf("%6d", table[row * numCols + col]);
        }
        printf("\n");
    }
}
void Hide_table_2D(int niv, int numRows, int numCols, int *table)
{
    int cst = 88;
    Display_Header(niv, numRows, numCols);
    printf("\n Colonne>");
    for (int i = 0; i < numCols; i++)
    {
        printf("    %d ", i);
    }
    printf("\n Lignes |");
    for (int i = 1; i <= numCols; i++)
    {
        printf("   __ ");
    }
    printf("\n");
    for (int row = 0; row < numRows; row++)
    {
        printf("\n    %c   |", 'A' + row);
        for (int col = 0; col < numCols; col++)
        {
            if (matched_cells[row][col])
            {
                printf("    %d ", table[row * numCols + col]);
            }
            else
            {
                printf("   %d ", cst);
            }
        }
        printf("\n");
    }
    printf("\n");
}
void Display_selected(int niv, int numRows, int numCols, int *table, int row1, int col1, int row2, int col2){
    int cst = 88;
    Display_Header(niv, numRows, numCols);
    printf("\n Colonne>");
    for (int i = 0; i < numCols; i++){
        printf("    %d ", i);
    }
    printf("\n Lignes |");
    for (int i = 1; i <= numCols; i++){
        printf("   __ ");
    }
    printf("\n");
    for (int row = 0; row < numRows; row++){
        printf("\n    %c   |", 'A' + row);
        for (int col = 0; col < numCols; col++){
            if (matched_cells[row][col]){
                printf("    %d ", table[row * numCols + col]);
            } else if ((row == row1 && col == col1) || (row == row2 && col == col2)) {
                printf("    %d ", table[row * numCols + col]);
            } else {
                printf("    %d ", cst);
            }
        }
        printf("\n");
    }
}
void Display_Memory_Rules()
{
    system("clear");
    printf("/***********************************************************************/\n");
    printf("/* But du jeu : retrouver toutes les paires de cartes                  */\n");
    printf("/* Deroulement:                                                        */\n");
    printf("/*  (1) Vous aurez 5 secondes pour visulaiser toutes les cartes        */\n");
    printf("/*  (2) Retourner 2 cartes de votre choix                              */\n");
    printf("/*    -> Si les cartes sont identiques, on les laisse, et on rejoue    */\n");
    printf("/*    -> Si les cartes sont differents, on les retourne, et on rejoue  */\n");
    printf("/* La partie se termine lorsqu'il n'y a plus de carte a retourner      */\n");
    printf("/***********************************************************************/\n");
}

int getGameLevelChoice()
{
    int level;
    printf("*******************************\n");
    printf("*  CHOIX NIVEAU DE JEU MEMORY *\n");
    printf("*******************************\n");
    printf(" ----> Facile    :1 <---- \n");
    printf(" ----> Moyen     :2 <---- \n");
    printf(" ----> Difficile :3 <---- \n");
    printf(" ----> Expert    :4 <---- \n");
    printf(" CHOIX DE NIVEAU DE JEU: ");
    scanf("%d", &level);
    return level;
}
void play_memory()
{
    Display_Memory_Rules();
    int level, cells, numRows, numCols, pairs = 0;
    level = getGameLevelChoice();
    switch (level){
    case 1:
        cells = FACILE;
        numRows = 3;
        numCols = 4;
        break;
    case 2:
        cells = MOYEN;
        numRows = 4;
        numCols = 4;
        break;
    case 3:
        cells = DIFFICILE;
        numRows = 6;
        numCols = 4;
        break;
    case 4:
        cells = EXPERT;
        numRows = 6;
        numCols = 6;
        break;
    default:
        cells = MAX;
        numRows = 6;
        numCols = 6;
    }
    int numbers[cells], table[numRows][numCols], totalpairs = cells / 2;
    initialize_matched_cells(numRows, numCols);
    Fill_Table_1D(cells, numbers);
    srand(time(NULL));
    Shuffle_Table_1D(numbers, cells);
    Fill_Table_2D(numRows, numCols, cells, &table[0][0], numbers);
    Display_Table_2D(level, numRows, numCols, &table[0][0]);
    printf("\n");
    sleep(5);
    Hide_table_2D(level, numRows, numCols, &table[0][0]);
    char case1[3], case2[3];
    while (pairs < totalpairs){
        printf("1ere case a visualiser (Ligne/colonne) ? : ");
        scanf("%s", case1);
        int row1 = case1[0] - 'A';
        int col1 = case1[2] - '0';
        printf("2eme case a visualiser (Ligne/colonne) ? : ");
        scanf("%s", case2);
        int row2 = case2[0] - 'A';
        int col2 = case2[2] - '0';
        if (table[row1][col1] == table[row2][col2]){
            matched_cells[row1][col1] = 1;
            matched_cells[row2][col2] = 1;
            pairs++;
            Display_selected(level, numRows, numCols, &table[0][0], row1, col1, row2, col2);
        } else {
            Display_selected(level, numRows, numCols, &table[0][0], row1, col1, row2, col2);
            sleep(3);
            Hide_table_2D(level, numRows, numCols, &table[0][0]);
        }
    }
    printf(" *******************************\n ************ BRAVO ************\n *******************************\n");
}