#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "core.h"
#include "stack.h"

#define DEBUG 0

int expo(const int base, const int power)
{
    if (power < 0) {
        return 0;
    } else {
        int res = 1;
        for (int i = 0; i < power; i++) {
            res *= base;
        }
        return res;
    }
}

int min(const int a, const int b)
{
    return (a <= b) ? a : b;
}

int max(const int a, const int b)
{
    return (a >= b) ? a : b;
}

int rpn_reduce(const struct expr *e)
{
    assert(e != NULL);
    struct stk *k = stk_new();
    int a, b;
    int op;
    for (struct ll_node *i = e->head; i != NULL; i = i->next) {
        if (i->state == OPERAND){
            stk_push(k, i->state, i->datum);
        } else {
            b = stk_peek(k);
            stk_pop(k);
            a = stk_peek(k);
            stk_pop(k);
            op = i->datum;
            switch (op) {
                case '+':
                    stk_push(k, OPERAND, a + b);
                    break;
                case '-':    
                    stk_push(k, OPERAND, a - b);
                    break;
                case '*': 
                    stk_push(k, OPERAND, a * b);
                    break;
                case '/':
                    stk_push(k, OPERAND, a / b);
                    break;
                case '^':
                    stk_push(k, OPERAND, expo(a, b));
                    break;
                case 'm':
                    stk_push(k, OPERAND, min(a, b));
                    break;
                case 'M':
                    stk_push(k, OPERAND, max(a, b));
                    break;
                default: 
                    assert(0);
            }

        }
    }
    assert((k->depth) == 1);
    int res = stk_peek(k);
    stk_destroy(&k);
    return res;
}

