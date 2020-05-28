#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

#define DEBUG 0

struct stk *stk_new(void)
{
    struct stk *k = malloc(sizeof(*k));
    assert(k != NULL);
    k->depth = 0;
    k->top = NULL;
    return k;
}

void stk_destroy(struct stk **k)
{
    assert((*k) != NULL);
    struct ll_node *tmp;
    for (struct ll_node *i = (*k)->top; i != NULL; i = tmp) {
        tmp = i->next;
        ll_node_destroy(&i);
        (*k)->depth--;
    }
    assert(((*k)->depth) == 0);
    free(*k);
    (*k) == NULL;
}

void stk_push(struct stk *k, const unsigned int s, const int d)
{
    assert(k != NULL);
    if (k->depth > 0) {
        k->top = ll_node_prepend(k->top, s, d);
    } else {
        k->top = ll_node_new(s, d);
    }
    (k->depth)++;
}

void stk_pop(struct stk *k)
{
    assert(k != NULL);
    assert(k->depth > 0);
    struct ll_node *tmp = k->top->next;
    ll_node_destroy(&(k->top));
    k->top = tmp;
    (k->depth)--;
}

void stk_print(const struct stk *k)
{
    assert(k != NULL);
    printf("@%p\tSTK\n", k);
    ll_print(k->top);
    printf("\n");
}

int stk_peek(const struct stk *k)
{
    assert(k != NULL);
    return k->top->datum;
}