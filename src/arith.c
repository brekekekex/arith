#include <stdio.h>
#include <string.h>
#include "core.h"

void missing_arg_handler(char *argv0)
{
    printf("%s: missing operand\nTry '%s --help' for more information.\n", argv0, argv0);
}

void syntax_err_handler(char *argv0)
{
    printf("%s: syntax error\nTry '%s --help' for more information.\n", argv0, argv0);
}

void help_handler(char *argv0)
{
    printf("usage: %s 'EXPRESSION' [-r] [-v]\n"
    "\t-r: EXPRESSION is postfix\n"
    "\t-v: print verbose output\n\n"
    "Print the value of an arithmetic EXPRESSION to standard output. \n"
    "Note that EXPRESSION should be bookmarked by single or double quotes \nif it contains the precedence operators '(' and ')': \n"
    "e.g., to evaluate the EXPRESSION (1-3)*5^(20/(4+6)), enter \n"
    "\t%s '(1-3)*5^(20/(4+6))'\n"
    "\n"
    "The following symbols are supported: \n"
    "\t+: addition\n"
    "\t-: subtraction\n"
    "\t*: multiplication\n"
    "\t/: (truncated) division\n"
    "\t^: exponentiation\n"
    "\t(: precedence\n"
    "\t): precedence\n"
    "\t[0-9]: integral constants (which may be negative)\n\n"
    "Note that whitespace is illegal (unless in an EXPRESSION specified in postfix).\n", argv0, argv0);       
}

void core_handler(unsigned int r, unsigned int v, char *e_arr) {
    struct expr *infix;
    struct expr *postfix;
    if (!r && !v) {
        infix = expr_from_array(e_arr);
        postfix = expr_shunt(infix);
        printf("%d\n", rpn_reduce(postfix));
    } else if (!r && v) {
        printf("parsing input...\n");
        printf("generating tokens...\n");
        infix = expr_from_array(e_arr);
        printf("EXPRESSION (infix): \n");
        expr_print(infix);
        printf("converting to postfix...\n");
        postfix = expr_shunt(infix);
        printf("EXPRESSION (postfix): \n");
        expr_print(postfix);
        printf("evaluating...\n");
        printf("result:\t%d\n", rpn_reduce(postfix));
    } else if (r && !v) {
        postfix = expr_from_array(e_arr);
        printf("%d\n", rpn_reduce(postfix));
    } else if (r && v) {
        printf("parsing input...\n");
        printf("generating tokens...\n");
        postfix = expr_from_array(e_arr);
        printf("EXPRESSION (postfix): \n");
        expr_print(postfix);
        printf("evaluating...\n");
        printf("result:\t%d\n", rpn_reduce(postfix));
    }
}

int main(int argc, char *argv[]){
    struct expr *infix;
    struct expr *postfix;
    unsigned int r_flag = 0;
    unsigned int v_flag = 0;
    unsigned int e_flag = 0;
    char *expr_in;

    if (argc > 4) {
        syntax_err_handler(argv[0]);
        return 0;
    }
    for (int a = 1; a < argc; a++) {
        if (!strcmp(argv[a], "--help")) {
            help_handler(argv[0]);
            return 0;
        } else if (!strcmp(argv[a], "-r")) {
            if (r_flag) {
                syntax_err_handler(argv[0]);
                return 0;
            } else {
                r_flag = 1;
            }
        } else if (!strcmp(argv[a], "-v")) {
            if (v_flag) {
                syntax_err_handler(argv[0]);
                return 0;
            } else {
                v_flag = 1;
            }

        } else {
            if (e_flag) {
                syntax_err_handler(argv[0]);
                return 0;
            } else {
                e_flag = 1;
                expr_in = argv[a];
            }
        }
    }
    if (!e_flag) {
        missing_arg_handler(argv[0]);
        return 0;
    }
    core_handler(r_flag, v_flag, expr_in);
    return 0;
}