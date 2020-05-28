#ifndef STACK_H
#define STACK_H
#include "llist.h"

struct stk {
    unsigned int depth;
    struct ll_node *top;
};

struct stk *stk_new(void);
void stk_destroy(struct stk **k);
void stk_push(struct stk *k, const unsigned int s, const int d);
void stk_pop(struct stk *k);
void stk_print(const struct stk *k);
int stk_peek(const struct stk *k);


#endif


