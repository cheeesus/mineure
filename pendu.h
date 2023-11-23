#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

FILE *words;
#define MAX_WORDS 10
#define MAX_WORD_LENGTH 10
int wordsCount = 0;
void Open_Dictionary_File(){
    words = fopen("/home/hiba/mineure/words.txt", "r+");
    if (words == NULL){
        printf("Error opening file.");
        exit(1); // Exit the program if the file can't be opened.
    }

    // Count the words in the file.
    char ch;
    while ((ch = fgetc(words)) != EOF){
        if (ch == '\n'){
            wordsCount++;
        }
    }
}

void Add_New_Word()
{
    if (wordsCount >= MAX_WORDS)
    {
        printf("Maximum word count reached.\n");
        return;
    }

    char newWord[MAX_WORD_LENGTH + 1];
    printf("Enter a new word of maximum 10 letters:\n");
    scanf("%10s", newWord);

    if (strlen(newWord) > MAX_WORD_LENGTH)
    {
        printf("Word exceeds the maximum length!\n");
        return;
    }

    fprintf(words, "%s\n", newWord);

    wordsCount++;
    printf("Word count: %d\n", wordsCount);
}

char *Select_Random_Word()
{
    rewind(words);
    if (wordsCount == 0){
        printf("No words in the file.\n");
        return NULL;
    }
    srand(time(NULL));
    int index = rand() % wordsCount;
    char wordSelected[MAX_WORD_LENGTH];
    int ch;
    while (index > 0){
        ch = fgetc(words);
        if (ch == '\n'){
            index--;
        }
    }
    fgets(wordSelected, sizeof(wordSelected), words);
    wordSelected[strcspn(wordSelected, "\n")] = '\0';
    // Dynamically allocate memory for the selected word
    char *selectedWord = (char *)malloc(strlen(wordSelected) + 1);
    if (selectedWord != NULL){
        strcpy(selectedWord, wordSelected);
    }
    return selectedWord;
}
void mask_word(char *word, int *pos)
{
    // system("clear");
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        if (pos[i] == 1)
        {
            printf("%c ", word[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}
void Init_LettersFoundPos(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = 0;
    }
}
void Pendu(char *word)
{
    int n = 10;
    char letter;
    int lettersFound = 0;
    int wordLen = strlen(word);
    int lettersFoundPos[wordLen];
    Init_LettersFoundPos(lettersFoundPos, wordLen);
    for (int i = n; i > 0 && lettersFound < wordLen; i--){
        mask_word(word, lettersFoundPos);
        printf("Enter a letter: ");
        scanf(" %c", &letter);
        printf("\n");
        int found = 0;
        for (int j = 0; j < wordLen; j++){
            if (word[j] == letter && lettersFoundPos[j] == 0){
                found = 1;
                lettersFoundPos[j] = 1;
                lettersFound++;
            }
        }if (!found){
            printf("TRY AGAIN\n");
        }
        if (lettersFound == wordLen){
            printf("BRAVO!! the word was: %s\n", word);
            break;
        }
    } 
    if (lettersFound < wordLen){
        printf("ECHEC! the word was: %s\n", word);
    }
}
void Play_With_Computer()
{
    system("clear");
    printf("you are playing with computer\n");
    char *wordSelected = Select_Random_Word();
    Pendu(wordSelected);
}

void Play_With_Friend()
{
    char wordSelected[MAX_WORD_LENGTH + 1];
    printf("Ask your friend to enter a word of max 10 letters for you to guess:\n");
    scanf("%10s", wordSelected);
    if (strlen(wordSelected) > MAX_WORD_LENGTH)
    {
        printf("Word exceeds the maximum length!\n");
        return;
    }
    Pendu(wordSelected);
}

void play_pendu()
{
    Open_Dictionary_File();
    system("clear");
    int choix;
    printf("0 - Enter a new word to dictionary.\n1 - Play with computer.\n2 - Play with friend.\n");
    scanf("%d", &choix);
    if (choix == 0)
    {
        Add_New_Word();
    }
    else if (choix == 1)
    {
        Play_With_Computer();
    }
    else if (choix == 2)
    {
        Play_With_Friend();
    }
}