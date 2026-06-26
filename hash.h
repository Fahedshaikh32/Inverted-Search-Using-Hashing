#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

#define SUCCESS 0                // return value for success
#define FAILURE -1               // return value for failure
#define LIST_EMPTY -2            // return when list is empty
#define DATA_NOT_FOUND -3        // return when word not found

typedef struct sub
{
    char *file;                  // store file name
    int w_count;                 // store word count in that file
    struct sub *sub_link;        // pointer to next sub node
} sub_t;

typedef struct main
{
    char *str;                   // store main word
    int count;                   // store number of files word appears in
    struct sub *sublink;         // pointer to sub list
    struct main *mainlink;       // pointer to next main node
} main_t;

typedef struct node
{
    int index;                   // store hash index
    main_t *link;                // pointer to main node list
} hash_t;

typedef struct file
{
    char str[50];                // store file name from command line
    struct file *link;           // pointer to next file node
} node_t;

int inputvalidation(int argc, char *argv[], node_t **head);   // validate input files
int create_db(hash_t *arr, node_t *head);                     // create database from files
int display_db(hash_t *arr);                                  // display database content
int update_db(hash_t *arr, node_t *head);                     // update database from backup
int validation(hash_t *arr, char *name, char *filename, int i); // validate and insert word
int openfile(hash_t *arr, char *filename);                    // open and read file
int search_db(hash_t *arr, char *word);                       // search word in database
int save_db(hash_t *arr, char *file);                         // save database to file
int update_db(hash_t *arr, node_t *head);                     // update database function

#endif