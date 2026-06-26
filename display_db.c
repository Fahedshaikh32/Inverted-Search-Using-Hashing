#include "hash.h"

int display_db(hash_t *arr)
{
    int flag = 0; // check if database has any data

    for (int i = 0; i < 27; i++) // traverse all hash indexes
    {
        if (arr[i].link != NULL) // check if index is not empty
        {
            flag = 1; // database has data
            main_t *temp = arr[i].link; // get main list
            int n = 0; // control index printing

            while (temp) // traverse main list
            {
                if (n == 0) // print index only first time
                {
                    printf("[%d]  [%s] %d ", i, temp->str, temp->count); // print index, word and count
                    n = 1; // avoid printing index again
                }
                else
                {
                    printf("[%s] %d ", temp->str, temp->count); // print next word at same index
                }

                sub_t *temp1 = temp->sublink; // get sub list
                printf("file/s:"); // print file label

                while (temp1) // traverse sub list
                {
                    printf("File:%s %d times", temp1->file, temp1->w_count); // print file name and count
                    temp1 = temp1->sub_link; // move to next sub node
                }

                temp = temp->mainlink; // move to next main node
            }
        }
        else
        {
            continue; // skip empty index
        }

        printf("\n"); // new line after each index
    }

    if (flag == 0) // if no data found
    {
        printf("Database is empty\n"); // print empty message
    }

    return SUCCESS; // return success
}