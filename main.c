/*====================================================================

                        PROJECT DOCUMENT

Name            : Fahed Akil Shaikh
Start Date      : 24/02/2026
End Date        : 01/03/2026
Project Title   : Inverted Search

----------------------------------------------------------------------
PROJECT OVERVIEW
----------------------------------------------------------------------

Searching a particular word manually inside multiple text files is 
slow and inefficient. When the number of files increases, it becomes 
difficult to track in which file a word appears and how many times 
it occurs.

To solve this issue, this project implements an Inverted Search 
application using a hash table. The program builds an indexed 
database of words from multiple files, allowing fast search and 
efficient retrieval of file names and word frequency.

----------------------------------------------------------------------
PROJECT OBJECTIVES
----------------------------------------------------------------------

• Develop an application to perform inverted search on multiple files.  
• Store and manage words efficiently using hashing technique.  
• Maintain the list of files where each word appears.  
• Store the frequency of every word in each file.  
• Provide a menu-driven interface for user interaction.  
• Display database contents in a clean and readable format.

----------------------------------------------------------------------
SYSTEM REQUIREMENTS
----------------------------------------------------------------------

• The user provides multiple text file names as command-line arguments.  
• The program validates whether files exist and are readable.  
• Each file is processed word by word.  
• Case differences and special characters are handled properly.  
• Words are stored in a hash table based on their first character.  

For every unique word:
• The program stores the number of files containing the word.  
• The program stores how many times the word appears in each file.  

Menu options available in the program:

1. Create Database  
2. Display Database  
3. Search Word  
4. Update Database from Backup File  
5. Save Database to File  
6. Exit  

When displaying the database, the program shows:

• Hash table index  
• Word  
• Number of files containing the word  
• File names along with occurrence count  

All output is shown in a structured and user-friendly format 
on the terminal.

----------------------------------------------------------------------
SAMPLE INPUT / OUTPUT
----------------------------------------------------------------------

2

[5]  [Fahed] 2 file/s:File:file.txt 3 timesFile:file1.txt 1 times
[6]  [Gopal] 1 file/s:File:file1.txt 1 times
[25] [z] 1 file/s:File:file.txt 1 times
[26] [&] 1 file/s:File:file.txt 1 times[|] 1 file/s:File:file.txt 1 times

======================================================================*/
#include "hash.h"

int main(int argc, char *argv[])
{
    if (argc < 2) // check if file names are given
    {
        printf("Please provide the file name as a command line argument.\n");
        return FAILURE; // return if no file given
    }

    node_t *head = NULL; // initialize file list head
    inputvalidation(argc, argv, &head); // validate input files

    hash_t arr[27]; // create hash table array

    for (int i = 0; i < 27; i++) // initialize hash table
    {
        arr[i].index = i; // set index number
        arr[i].link = NULL; // set link to NULL
    }

    int choice; // store user choice
    int flag = 0; // check database created
    int flag1 = 0; // check database updated

    while (1) // infinite loop for menu
    {
        printf("Select your choice among following options:\n");
        printf("1. Create DATABASE\n");
        printf("2. Display Database\n");
        printf("3. Update DATABASE\n");
        printf("4. Search\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("Enter your choice:\n");

        scanf("%d", &choice); // read user choice

        switch (choice)
        {
        case 1:
            if (flag == 0) // check if database not created
            {
                create_db(arr, head); // create database
                flag = 1; // set created flag
            }
            else
            {
                printf("\nDatabase already created\n\n"); // print message
            }
            break;

        case 2:
            display_db(arr); // display database
            break;

        case 3:
            if (flag == 1 || flag1 == 1) // check if already created or updated
            {
                printf("\nDatabase already created\n\n");
            }
            else
            {
                if (update_db(arr, head) == FAILURE) // update from backup
                {
                    printf("Error updating database\n");
                    return FAILURE; // return on failure
                }
                flag1 = 1; // set updated flag
            }
            break;

        case 4:
            printf("Enter the word you want search: "); // ask word
            char arr3[100]; // buffer for search word
            scanf(" %s", arr3); // read word

            if (search_db(arr, arr3) == DATA_NOT_FOUND) // check if not found
            {
                printf("\n%s is not present in the database\n\n", arr3);
            }
            break;

        case 5:
            char arr4[100]; // buffer for save file name
            printf("Enter the file name to save data:");
            scanf("%s", arr4); // read file name
            save_db(arr, arr4); // save database
            break;

        case 6:
            printf("Exiting...\n"); // exit message
            exit(0); // terminate program
            break;

        default:
            break; // invalid choice
        }
    }
}