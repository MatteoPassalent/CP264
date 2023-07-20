/*
 * your program signature
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_queue_stack.h"
#include "expression_symbol.h"

int get_priority(char op)
{
    if (op == '/' || op == '*' || op == '%')
        return 1;
    else if (op == '+' || op == '-')
        return 0;
    else
        return -1;
}

QUEUE infix_to_postfix_symbol(char *infixstr, HASHTABLE *ht)
{
    // your implementation
    char *p = infixstr;
    QUEUE queue = {0};
    STACK stack = {0};
    int sign = 1;
    int num = 0;
    char symbol[11] = {0};
    while (*p != '\0')
    {
        if (*p == '-' && (p == infixstr || *(p - 1) == '('))
        {
            sign = -1;
        }
        else if (*p >= '0' && *p <= '9')
        {
            num = *p - '0';
            while ((*(p + 1) >= '0' && *(p + 1) <= '9'))
            {
                num = num * 10 + (*(p + 1) - '0');
                p++;
            }
            enqueue(&queue, new_node(sign * num, 0));
            sign = 1;
        }
        else if (*p == '(')
        {
            push(&stack, new_node('(', 2));
        }
        else if (*p == ')')
        {
            while (stack.top->type == 1)
            {
                enqueue(&queue, pop(&stack));
            }
            pop(&stack);
        }
        else if (*p == '/' || *p == '*' || *p == '%' || *p == '+' || *p == '-')
        {
            push(&stack, new_node(*p, 1));
        }
        else
        {
            int i = 0;
            char *c = p;
            while ((*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z'))
            {
                symbol[i] = *c;
                i++;
                c++;
            }
            HSNODE *node = search(ht, symbol);
            if (node)
            {
                num = node->value;
                enqueue(&queue, new_node(sign * num, 0));
                sign = 1;
            }
        }
        p++;
    }
    while (stack.top)
    {
        enqueue(&queue, pop(&stack));
    }
    return queue;
}

int evaluate_infix_symbol(char *infixstr, HASHTABLE *ht)
{
    // your implementation
    QUEUE q = infix_to_postfix_symbol(infixstr, ht);
    int val = evaluate_postfix(q);
    return val;
}

int evaluate_postfix(QUEUE queue)
{
    // your implementation, same as A6Q3
    STACK stack = {0};
    NODE *x;
    NODE *a;
    NODE *b;
    NODE *c;
    while (queue.front != NULL)
    {
        x = dequeue(&queue);
        if (x->type == 0)
        {
            push(&stack, x);
        }
        else if (x->type == 1)
        {
            a = pop(&stack);
            b = pop(&stack);
            if (x->data == 47)
            { // "/"
                c = new_node(b->data / a->data, 0);
            }
            else if (x->data == 42)
            { // *
                c = new_node(b->data * a->data, 0);
            }
            else if (x->data == 37)
            { // %
                c = new_node(b->data % a->data, 0);
            }
            else if (x->data == 43)
            { // +
                c = new_node(b->data + a->data, 0);
            }
            else if (x->data == 45)
            { // -
                c = new_node(b->data - a->data, 0);
            }
            push(&stack, c);
        }
    }
    return stack.top->data;
}
