#ifndef EXPR_H
#define EXPR_H
#include "llist.h"

struct expr {
    unsigned int length;
    struct ll_node *head;
};

struct expr *expr_new(void);
void expr_destroy(struct expr **e); 
void expr_add_symbol(struct expr *e, const unsigned int s, const int d);
void expr_print(const struct expr *e);
struct expr *expr_shunt(const struct expr *e);
struct expr *expr_from_array(const char *a);

#endif


