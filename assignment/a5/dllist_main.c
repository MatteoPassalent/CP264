/*--------------------------------------------------
Project: cp264oc-a5q2
File:    dllist_main.c  public test driver
Author:  HBF
Version: 2023-06-06
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "dllist.h"

void display_forward(DLL *dllp)
{
    NODE *np = dllp->start;
    while (np != NULL)
    {
        printf("%c", np->data);
        np = np->next;
    }
}

void display_backward(DLL *dllp)
{
    NODE *np = dllp->end;
    while (np != NULL)
    {
        printf("%c", np->data);
        np = np->prev;
    }
}

int main(int argc, char *args[])
{
    DLL dllist = {0};
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        dll_insert_start(&dllist, new_node('0' + i));
    }
    printf("display_forward1:");
    display_forward(&dllist);
    printf("\n");
    printf("display_backward1:");
    display_backward(&dllist);
    printf("\nlength1:%d\n", dllist.length);

    dll_delete_start(&dllist);
    dll_delete_end(&dllist);
    printf("display_forward2:");
    display_forward(&dllist);
    printf("\n");
    printf("display_backward2:");
    display_backward(&dllist);
    printf("\nlength2:%d\n", dllist.length);
    dll_clean(&dllist);

    for (i = 0; i < 10; i++)
    {
        dll_insert_end(&dllist, new_node('a' + i));
    }
    printf("display_forward3:");
    display_forward(&dllist);
    printf("\n");
    printf("display_backward3:");
    display_backward(&dllist);
    printf("\nlength3:%d", dllist.length);
    dll_clean(&dllist);
    printf("\nlength4:%d\n", dllist.length);
    return 0;
}
