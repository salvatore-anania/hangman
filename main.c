#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int start_game(const char *file_name, const char *difficulty, const char *category );

int main(int argc, char *argv[])
{
    const char *file_name = argv[1];
    const char *difficulty = argv[2];
    const char *category = argv[3];
    if(argc==4){
        return start_game(file_name, difficulty, category);
    }else if(argc==3){
        return start_game(file_name, difficulty, "all");
    }else if(argc==1){
        return start_game("dictionnaire.txt", "all", "all");
    }else{
        printf("Usage: %s file_name [facile/moyen/difficile] <category> \n", argv[0]);
        return -1;
    }
}

