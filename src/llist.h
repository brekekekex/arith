#ifndef LLIST_H
#define LLIST_H
#define OPERAND 0
#define OPERATOR 1

struct ll_node {
    unsigned int state;
    int datum;
    struct ll_node *next;
};

struct ll_node *ll_node_new(const unsigned int s, const int d);
void ll_node_destroy(struct ll_node **n);
struct ll_node *ll_node_prepend(struct ll_node *n, const unsigned int s, const int d);
void ll_node_append(struct ll_node *n, const unsigned int s, const int d);
void ll_print(const struct ll_node *n); 

#endif