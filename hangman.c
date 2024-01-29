#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "String.h"

//Global Strings
char word [50];
char guessed_letters[20];
char user_guess[] = "";
char user_continue[] = "";
char blank = '*';
char word_category[20];


//Global Integers
int random_number;
int word_len;
int attempts = 10;

//Function Declarations
int start_game( const char *file_name, const char *difficulty, const char *category);
void get_input();
void print_blanks();
void draw_platform();
int get_word(const char *difficulty, const char *category, const char *file_name);
void push_back_word(t_string *word_list, t_string *word);
void free_word_list(t_string *head);

int start_game(const char *file_name, const char *difficulty, const char *category)
{
    //Game Loop
    while(1)
    {
        if(get_word(difficulty,category, file_name)==-1){
            return -1;
        }
        word_len = strlen(word);
        printf("%d", word_len);
        memset(guessed_letters, 0, sizeof guessed_letters);
        attempts = 6;

        for(int i=0; i < word_len; i++)
        {
            if(word[i] == word[0])
            {
                guessed_letters[i] = word[0];
            }else if(word[i] == word[word_len-1])
            {
                guessed_letters[i] = word[word_len-1];
            }
        }

        while(attempts > 0)
        {
            system("cls");

            //If they have guessed all the letters they win
            if((int)strlen(guessed_letters) == word_len)
            {
                print_blanks();
                break;
            }
            //Else, print attempts and try again
            else
            {
                printf("Attempts Remaining: %i\n", attempts);
                print_blanks();
                get_input();
            }
        }

        system("cls");

        //If they won
        if(attempts > 0)
        {
            print_blanks();
            printf("You Won! Play again?(Y/N)\n");
        }
        //If they lost
        else
        {
            draw_platform();
            printf("You Lost! The word was %s, Play again?(Y/N)\n", word);
        }

        bool noChoice = true;
        while (noChoice)
        {
            scanf("%s", user_continue);
            if(!strcmp( user_continue, "n") || !strcmp( user_continue, "N"))
            {
                return 0;
            }
            else if(!strcmp( user_continue, "y") || !strcmp( user_continue, "Y"))
            {
                noChoice = false;
                continue;
            }
            else
            {
                printf("Play again?(Y/N)\n");
            }
        }
        
        
    }
    
}

void get_input()
{
    //Gets guess from user and checks
    //To see if that letter is in the word

    int i;
    int letter_hit = 0; //Used to tell if the guess letter is in the word

    printf("\nEntrez une lettre: \n");
    scanf(" %s", user_guess);

    for(i=0; i < word_len; i++)
    {
        if(user_guess[0] == word[i])
        {
            guessed_letters[i] = user_guess[0];
            letter_hit ++;
        }
    }

    if(letter_hit > 0)
    {
        return;
    }
    else
    {
        attempts --;
    }
}

void print_blanks()
{

    int i;

    draw_platform();
    printf(word_category);
    printf(" :\n");
    for(i=0; i<word_len; i++)
    {
        if(guessed_letters[i] == 0)
        {
            printf("%c", blank);
        }
        else
        {
            printf("%c", guessed_letters[i]);
        }
    }
    printf("\n");
}

void draw_platform()
{

    char *platform[]={

                     "        |\n"
                     "        |\n"
                     "        |\n"
                     "       ===\n",

                     "  |=====|\n"
                     "        |\n"
                     "        |\n"
                     "        |\n"
                     "       ===\n",

                     "  |=====|\n"
                     "  O     |\n"
                     "        |\n"
                     "        |\n"
                     "       ===\n",

                     "  |=====|\n"
                     "  O     |\n"
                     " -|-    |\n"
                     "        |\n"
                     "       ===\n",

                     "  |=====|\n"
                     "  O     |\n"
                     " -|-    |\n"
                     "  |     |\n"
                     "       ===\n",

                     "   |=====|\n"
                     "   O     |\n"
                     "  -|-    |\n"
                     "  //     |\n"
                     "       ===\n"

    };

    printf("\n\n%s\n", platform[6 - attempts]);
}

int get_word(const char *difficulty, const char *category, const char *file_name)
{

    FILE *fp;
    int line_number = 0;
    char current_line[50];
    char current_word[20];
    char current_difficulty[10];
    char current_category[20];
    t_string *categories = malloc(sizeof(t_string));
    t_string *words = malloc(sizeof(t_string));
    t_string *fisrt_word = words;
    t_string *fisrt_category = categories;
	char delim[] = ",";
    int delimCount = 1;
	

    fp = fopen(file_name,"r");

    if(fp == NULL)
    {
        perror("Error in opening file");
    }

    //While not end of file, incr line number
    while(fgets(current_line, 50, fp) != NULL)
    {
        delimCount = 1;
        if(current_line[0] != '#' && current_line[0] != '\n')
        {
            char *ptr = strtok(current_line, delim);
            strcpy(current_word, ptr);
            while(delimCount < 3)
            {
                delimCount++;
                ptr = strtok(NULL, delim);
                if(delimCount == 2)
                {
                    strcpy(current_difficulty, ptr);
                    printf("%s", current_difficulty);
                }
                else if(delimCount == 3)
                {
                    strcpy(current_category, ptr);
                    printf("%s", current_category);
                }else
                {
                    printf("%s","Error in file format");
                    return -1;
                }
            }
            
            if((!strcmp(difficulty, current_difficulty) || !strcmp(difficulty,"all")) && (!strcmp(category,"all") || !strcmp(category, current_category)))
            {
                words->chain= current_word;
                words->next = malloc(sizeof(t_string));
                categories->chain= current_category;
                categories->next = malloc(sizeof(t_string));
                line_number++;
                push_back_word(fisrt_word, words);
                push_back_word(fisrt_category, categories);
            }
        }
    }
    random_number = rand() % line_number;
    for(int i=0; i<random_number; i++)
    {
        fisrt_word = fisrt_word->next;
        fisrt_category = fisrt_category->next;
    }
    
    strcpy(word_category, categories->chain);
    strcpy(word, words->chain);
    free(words);
    free(categories);
    free_word_list(fisrt_word);
    free_word_list(fisrt_category);
    fclose(fp);
    return 0;
}

void push_back_word(t_string *word_list, t_string *word){
    while(word_list->next != NULL)
        word_list = word_list->next;
    word_list->next = word;
}

void free_word_list(t_string *head) {
    while (head != NULL) {
        t_string *temp = head;
        head = head->next;
        free(temp->chain);
        free(temp);
    }
}