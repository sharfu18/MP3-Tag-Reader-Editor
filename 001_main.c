/*
Description   :
Name          : Shaik Sharfuddin
Roll no       : 26012_016
Project Title : MP3 TAG READER
Start Date    : 10/08/2026
End Date      : 20/08/2026


SAMPLE OUTPUT :

You Have Selected View Menu
MP3 File Opened Successfully
ID3 TAG FOUND
ID3 Version : 2.3
Tag Size : 958 bytes

========================================
          MP3 TAG INFORMATION
========================================
TITLE    : Bahubali
Artist   : Keeravani
Album    : C Programming Album
YEAR     : 2022
Genre    : Test Genre
Composer : Test Composer
*/
#include <stdio.h>
#include<string.h>
#include "types.h"
#include "view.h"
#include "edit.h"
int main(int argc, char *argv[])
{
    // Check for minimum number of arguments
    if(argc < 2){
        printf("--------------------------------------------------------------------------------------\n");
        printf("ERROR : ./a.out : INVALID ARGUMENTS\n");
        printf("USAGE :\n");
        printf("To View Pass like       :    ./a.out -v mp3filename\n");
        printf("To Edit Pass like       :    ./a.out -e -t/-a/-A/-y/-g/-c changing_text mp3filename\n");
        printf("To Get Help Pass like   :    ./a.out --help\n");
        printf("--------------------------------------------------------------------------------------\n");
        return e_failure;
    }
    // Display help menu
    if(strcmp(argv[0],"./a.out") == 0  && strcmp(argv[1],"--help") == 0){
        printf("========================================\n");
        printf("          HELP MENU\n");
        printf("========================================\n");
        printf("1. -v -> to view mp3 file contents\n");
        printf("2. -e -> to edit mp3 file contents\n");
        printf("       2.1. -t -> to edit song title\n");
        printf("       2.2. -a -> to edit artist name\n");
        printf("       2.3. -A -> to edit album name\n");
        printf("       2.4. -y -> to edit year\n");
        printf("       2.5. -g -> to edit genre\n");
        printf("       2.6. -c -> to edit composer\n");
        return e_failure;
    }
    // Store the selected operation
    OperationType operation;
    // Identify the operation type
    operation = check_operation_type(argv[1]);
    // Handle view operation
    if(operation == e_view){
        // Check for required arguments
        if(argc < 3){
        printf("ERROR : No Enough Arguments for Viewing\n");
        return e_failure;
        }
        // Check for MP3 file extension
        if(strstr(argv[2],".mp3") == NULL){
        printf("ERROR : NOT A MP3 File\n");
        return e_failure;
        }
        printf("\nYou Have Selected View Menu\n");
        // Call view function
        if(view(argv[2]) == e_failure){
            return e_failure;
        }
    }
    
    // Handle edit operation
    else if(operation == e_edit){
        // Check for correct number of arguments
        if(argc != 5){
            printf("ERROR : Invalid Edit Format\n");
            return e_failure;
        }
        // Check for MP3 file extension
        if(strstr(argv[4],".mp3") == NULL){
        printf("ERROR : NOT A MP3 File\n");
        return e_failure;
        }
        // Check which tag needs to be edited
        printf("You Have Selected Edit Menu\n");
        if(strcmp(argv[2],"-t") == 0){
            printf("You Have Chosen To Edit TITLE\n");
        }
        else if(strcmp(argv[2],"-a") == 0){
            printf("You Have Chosen To Edit Artist Name\n");
        }
        else if(strcmp(argv[2],"-A") == 0){
            printf("You Have Chosen To Edit Album Name\n");
        }
        else if(strcmp(argv[2],"-y") == 0){
            printf("You Have Chosen To Edit Year\n");
        }
        else if(strcmp(argv[2],"-g") == 0){
            printf("You Have Chosen To Edit Genre\n");
        }
        else if(strcmp(argv[2],"-c") == 0){
            printf("You Have Chosen To Edit Composer\n");
        }
        else{
            printf("ERROR : Wrong Editing Format\n");
            return e_failure;
        }
        // Call edit function
        if(edit(argv[2],argv[3],argv[4]) == e_failure){
            return e_failure;
        }
    }
    // Handle unsupported operation
    else{
        printf("ERROR : Unsupported Operation\n");
        return e_failure;
    }
    return e_success;
}

// Identify the requested operation
OperationType check_operation_type(char *symbol){
    // Check for view operation
    if(strcmp(symbol,"-v") == 0){
        return e_view;
    }
    // Check for edit operation
    if(strcmp(symbol,"-e") == 0){
        return e_edit;
    }
    else{
        return e_unsupported;
    }
}
