#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "llist.h"

#define DEBUG 0

struct ll_node *ll_node_new(const unsigned int s, const int d)
{
    struct ll_node *n = malloc(sizeof(*n));
    assert(n != NULL);
    assert(s == OPERAND || s == OPERATOR);
    n->state = s;
    n->datum = d;
    n->next = NULL;
    return n;
}

void ll_node_destroy(struct ll_node **n)
{
    assert((*n) != NULL);
    free(*n);
    (*n) = NULL;
}

struct ll_node *ll_node_prepend(struct ll_node *n, const unsigned int s, const int d)
{
    assert(n != NULL);
    struct ll_node *m = ll_node_new(s, d);
    m->next = n;
    return m;
}

void ll_node_append(struct ll_node *n, const unsigned int s, const int d)
{
    assert(n != NULL);
    struct ll_node *o = ll_node_new(s, d);
    for (; n->next != NULL; n = n->next);
    n->next = o;
}

void ll_print(const struct ll_node *n)
{
    assert(n != NULL);
    if (DEBUG) {
        for (; n != NULL; n = n->next) {
            if (n->state == OPERAND) {
                printf("@%p\t%d\n", n, n->datum);
            } else {
                printf("@%p\t%c\n", n, n->datum);
            }
        }
    } else {
        for (; n != NULL; n = n->next) {
            if (n->state == OPERAND) {
                printf("%d ", n->datum);
            } else {
                printf("%c ", n->datum);
            }
        }
    }
}