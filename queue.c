#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(*head));
    if (!head)
        return NULL;
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head)
        return;

    struct list_head *current, *tmp;
    list_for_each_safe (current, tmp, head) {
        list_del(current);
        free(current);
    }

    free(head);
}

/* Helper function to create a new element with a copied string */
static element_t *create_element(char *s)
{
    if (!s)
        return NULL;

    element_t *new_element = malloc(sizeof(element_t));
    if (!new_element)
        return NULL;

    /*Allocate memery for the string*/
    size_t len = strlen(s);
    new_element->value = malloc(len + 1);
    if (!new_element->value) {
        free(new_element);
        return NULL;
    }

    strncpy(new_element->value, s, len);
    new_element->value[len] = '\0';  // ensure that it ends with '\0'
    return new_element;
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *new_element = create_element(s);
    if (!new_element)
        return false;

    list_add(&new_element->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *new_element = create_element(s);
    if (!new_element)
        return false;

    list_add_tail(&new_element->list, head);
    return true;
}

/* Helper function to remove an element from the queue (head or tail) */
static element_t *remove_element(struct list_head *head,
                                 char *sp,
                                 size_t bufsize,
                                 bool from_head)
{
    if (!head || list_empty(head))
        return NULL;

    /*Get the target element (either head or tail)*/
    struct list_head *target = from_head ? head->next : head->prev;
    element_t *removed_element = list_entry(target, element_t, list);

    /*Copy the string to the provided buffer,
    ensuring we do not exceed bufsize*/
    size_t len = strlen(removed_element->value);
    if (len < bufsize)
        strncpy(sp, removed_element->value, len + 1);
    else
        strncpy(sp, removed_element->value, bufsize - 1);

    list_del(target);  // no memory free

    return removed_element;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    return remove_element(head, sp, bufsize, true);  // remove head
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    return remove_element(head, sp, bufsize, false);  // remove tail
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return -1;

    int count = 0;
    struct list_head *current;

    list_for_each (current, head) {
        count++;
    }
    return count;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
