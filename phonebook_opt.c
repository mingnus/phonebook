#include <stdlib.h>
#include <string.h>

#include "phonebook_opt.h"

entry *findName(char lastName[], entry *pHead)
{
    int ret = 0;
    while (pHead != NULL) {
        if ((ret = strcasecmp(lastName, pHead->lastName)) == 0)
            return pHead;
        else if (ret > 0)
            pHead = pHead->pRight;
        else
            pHead = pHead->pLeft;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pDetails = NULL;

    return e;
}

static entry *__convertListToBST(entry **list, int64_t start, int64_t end)
{
    if (start > end)
        return NULL;
    int64_t mid = start + (end - start) / 2;
    entry *left = __convertListToBST(list, start, mid - 1);
    entry *parent = *list;
    parent->pLeft = left;
    *list = (*list)->pNext;
    parent->pRight = __convertListToBST(list, mid + 1, end);
    return parent;
}

entry *convertListToBST(entry *pHead, int64_t listSize)
{
    return __convertListToBST(&pHead, 0, listSize - 1);
}
