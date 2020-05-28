#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "expr.h"
#include "stack.h"

#define DEBUG 0

#define ADD_SCORE 1
#define SUB_SCORE 1
#define MULT_SCORE 2
#define DIV_SCORE 2
#define EXP_SCORE 3
#define L_SCORE 4
#define R_SCORE 4

struct expr *expr_new(void)
{
    struct expr *e = malloc(sizeof(*e));
    assert(e != NULL);
    e->length = 0;
    e->head = NULL;
    return e;
}

void expr_destroy(struct expr **e)
{
    assert((*e) != NULL);
    struct ll_node *tmp;
    for (struct ll_node *i = (*e)->head; i != NULL; i = tmp) {
        tmp = i->next;
        ll_node_destroy(&i);
        (*e)->length--;
    }
    assert(((*e)->length) == 0);
    free(*e);
    (*e) == NULL;
} 

void expr_add_symbol(struct expr *e, const unsigned int s, const int d)
{
    assert(e != NULL);
    if (e->length > 0) {
        ll_node_append(e->head, s, d);
    } else {
        e->head = ll_node_new(s, d);
    }
    (e->length)++;
}

void expr_print(const struct expr *e)
{
    assert(e != NULL);
    if (DEBUG) {
        printf("@%p\tEXPR\n", e);
        ll_print(e->head);
    } else {
        printf("EXPR:\t");
        ll_print(e->head);
    }
    printf("\n");
}

unsigned int precedence(const struct ll_node *n)
{
    if (n == NULL) {
        return 0;
    }
    assert(n->state == OPERATOR);
    switch (n->datum) {
        case '+':
            return ADD_SCORE;
        case '-':
            return SUB_SCORE;
        case '*':
            return MULT_SCORE;
        case '/':
            return DIV_SCORE;
        case '^':
            return EXP_SCORE;
        case '(':
            return L_SCORE;
        case ')':
            return R_SCORE;
        default: 
            assert(0);
    }
}

struct expr *expr_shunt(const struct expr* e) 
{
    assert(e != NULL);
    struct stk *opstack = stk_new();
    struct expr *rpn = expr_new();
    for (struct ll_node *i = e->head; i != NULL; i = i->next) {
        if (i->state == OPERAND) {
            expr_add_symbol(rpn, OPERAND, i->datum);
        } else if ((i->state == OPERATOR) && (i->datum == '(')) {
            stk_push(opstack, OPERATOR, i->datum);
        } else if ((i->state == OPERATOR) && (i->datum == ')')) {
            while (stk_peek(opstack) != '(') {
                expr_add_symbol(rpn, OPERATOR, stk_peek(opstack));
                stk_pop(opstack);
            }
            stk_pop(opstack);
        } else {
            while ((opstack->depth > 0) && 
            ((precedence(opstack->top) > precedence(i)) || ((precedence(opstack->top) == precedence(i)) && !(i->datum != '^'))) && 
            (opstack->top->datum != '(')) {
                expr_add_symbol(rpn, OPERATOR, stk_peek(opstack));
                stk_pop(opstack);
            }
            stk_push(opstack, OPERATOR, i->datum);
        }
    }
    while (opstack->depth > 0) {
        expr_add_symbol(rpn, OPERATOR, stk_peek(opstack));
        stk_pop(opstack);
    }
    stk_destroy(&opstack);
    return rpn;
}

int get_operand(const char *a)
{
    char buff[11] = "9999999999";
    char *b = buff;
    int sign = 1;
    if (*a == '-' || *a == '+') {
        *b = *a; 
        a++;
        b++;
    }
    while ((*a != '\0') && ((*a >= '0') && (*a <= '9'))) {
        *b = *a;
        b++;
        a++;    
    }
    *b = '\0';
    return atoi(buff);
}

struct expr *expr_from_array(const char *a)
{
    struct expr *infix = expr_new();
    if ((*a == '+') || (*a == '-')) {
        expr_add_symbol(infix, OPERAND, get_operand(a));
        a++;
        for(; (*a >= '0') && (*a <= '9') && (*a != '\0'); a++);
    }
    struct ll_node *i;
    while (*a != '\0') {
        if ((*a == '*') || (*a == '/') || (*a == '^') || (*a == '(') || (*a == ')')) {
            expr_add_symbol(infix, OPERATOR, *a);
        } else if ((*a == '+') || (*a == '-')) {
            for (i = infix->head; i->next != NULL; i = i->next);
            if (i->state == OPERATOR) {
                expr_add_symbol(infix, OPERAND, get_operand(a));
                a++;
                for(; (*a >= '0') && (*a <= '9') && (*a != '\0'); a++);
                continue;      
            } else {
                expr_add_symbol(infix, OPERATOR, *a);
                a++;
                continue;
            }
        } else if ( (*a >= '0') && (*a <= '9')) {
            expr_add_symbol(infix, OPERAND, get_operand(a));
            for(; (*a >= '0') && (*a <= '9') && (*a != '\0'); a++);
            continue;
        }
        a++;
    }   
    
    return infix;
}
