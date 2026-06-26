#include "hash.h"

int search_db(hash_t *arr, char *word)
{
    int c; // store hash index

    if (word[0] >= 'a' && word[0] <= 'z') // check if lowercase
    {
        c = (word[0] - 'a') % 26; // calculate index
    }
    else if (word[0] >= 'A' && word[0] <= 'Z') // check if uppercase
    {
        c = (word[0] - 'A') % 26; // calculate index
    }
    else
    {
        c = 26; // special character index
    }

    if (arr[c].link == 0) // check if index is empty
    {
        return DATA_NOT_FOUND; // word not found
    }

    int flag = 1; // flag to check word found
    main_t *temp = arr[c].link; // get main list

    while (temp) // traverse main list
    {
        if (strcmp(temp->str, word) == 0) // compare word
        {
            flag = 0; // word found

            printf("%s is present in %d file(s):\n", temp->str, temp->count); // print word and file count

            sub_t *temp1 = temp->sublink; // get sub list

            while (temp1) // traverse sub list
            {
                printf("In File: %s  %d times(s)\n", temp1->file, temp1->w_count); // print file and count
                temp1 = temp1->sub_link; // move to next sub node
            }

            return SUCCESS; // return success
        }

        temp = temp->mainlink; // move to next main node
    }

    if (flag == 1) // if word not found
    {
        return DATA_NOT_FOUND; // return not found
    }
}