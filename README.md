# arith
## Overview
Evaluating an algebraic expression is fairly trivial provided it has been serialized. In particular, postfix-notation strings may be evaluated through a judicious (yet simple) use of pushdown stacks. This repository details the implementation of such a stack-based calculator for simple (integer) expressions.

I have personally found [reverse Polish notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation) (RPN), however computationally tractable, to be highly unpleasant to read and write. Therefore, this calculator only relies on RPN as an internal representation&mdash;the user may input a normal, infix expression if they so desire. This is summarily parsed to postfix/RPN via Dijkstra's [shunting yard algorithm](http://www.cs.utexas.edu/~EWD/MCReps/MR35.PDF) prior to evaluation.

## Design
This project is for self-learning, which entails some constraints as well as some liberties. As concerns the former, I have hand-rolled the relevant data structures and algorithms in C while avoiding its standard library (*libc*) as much as possible.
Regarding the latter, my implementation is more theoretical than practical&mdash;cache locality and other 'real' considerations have been completely ignored.

The *arith* program runs almost entirely on linked lists: both the *struct stk* type (operator and operand stacks) and the *struct expr* type (symbol queues) are wrappers for the primitive *struct ll_node* type. User expressions (either infix or postfix) are converted from character arrays to dynamically-allocated *struct expr*s via *expr_from_array*. This yields an infix *struct expr* which either may be converted to an RPN expression (with *expr_shunt*) or is a natively-postfix *struct expr*. RPN expressions are fed to the *core* of the calculator, which computes their values via *rpn_reduce*.

As of now, malformed expressions will cause an immediate segmentation fault within *expr_from_array*, *expr_shunt*, or *rpn_reduce*. The calculator features integer addition ('+'), subtraction ('-'), multiplication ('*'), division ('/'), and exponentiation ('^') with support for positive and negative constants as well as precedence-overriding (parentheses). 

## Usage
Clone the repository to your local machine with

```linux
git clone https://github.com/brekekekex/arith
```

In */src*, compile with 

```linux
make
```

For usage, run *./arith* with the *--help* flag, which should yield
```linux
usage: ./arith 'EXPRESSION' [-r] [-v]
        -r: EXPRESSION is postfix
        -v: print verbose output

Print the value of an arithmetic EXPRESSION to standard output. 
Note that EXPRESSION should be bookmarked by single or double quotes 
if it contains the precedence operators '(' and ')': 
e.g., to evaluate the EXPRESSION (1-3)*5^(20/(4+6)), enter 
        ./arith '(1-3)*5^(20/(4+6))'

The following symbols are supported: 
        +: addition
        -: subtraction
        *: multiplication
        /: (truncated) division
        ^: exponentiation
        (: precedence
        ): precedence
        [0-9]: integral constants (which may be negative)

Note that whitespace is illegal (unless in an EXPRESSION specified in postfix).
```

## Examples
A simple expression featuring all supported operations, evaluated with the verbose output flag:

![alt text](https://github.com/brekekekex/arith/blob/master/img/example.png)


