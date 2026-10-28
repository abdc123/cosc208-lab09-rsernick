/****
 * Lab 09: Cache simulator
 * COSC 208, Introduction to Computer Systems, Fall 2026
 ****/

#ifndef __LIST_H__
#define __LIST_H__

struct node {
    int value;
    struct node *next;
};

struct list {
    struct node *head;
    struct node *tail;
    unsigned int length;
};

struct list* list_new();
void list_prepend(struct list *, int);
void list_append(struct list *, int);
int list_index(struct list *, int);
void list_free(struct list *);
void list_remove(struct list *, int);
void list_insert(struct list *, int, unsigned int);
int list_pop(struct list *, unsigned int);
unsigned int list_length(struct list *);

#endif // __LIST_H__
