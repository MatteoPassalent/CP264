#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"
#include "stack.h"
#include "expression.h"

/*
 * auxiliary function
 */
int get_priority(char op)
{
    if (op == '/' || op == '*' || op == '%')
        return 1;
    else if (op == '+' || op == '-')
        return 0;
    else
        return -1;
}

/*
 * auxiliary function
 */
int type(char c)
{
    if (c >= '0' && c <= '9')
        return 0;
    else if (c == '/' || c == '*' || c == '%' || c == '+' || c == '-')
        return 1;
    else if (c == '(')
        return 2;
    else if (c == ')')
        return 3;
    else
        return 4;
}

QUEUE infix_to_postfix(char *infixstr)
{
    char *p = infixstr;
    QUEUE queue = {0};
    STACK stack = {0};
    int sign = 1;
    int num = 0;
    while (*p)
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
        else if (type(*p) == 1)
        {
            push(&stack, new_node(*p, 1));
        }
        p++;
    }
    while (stack.top)
    {
        enqueue(&queue, pop(&stack));
    }
    return queue;
}

int evaluate_postfix(QUEUE queue)
{
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

int evaluate_infix(char *infixstr)
{
    QUEUE queue = {0};
    queue = infix_to_postfix(infixstr);
    evaluate_postfix(queue);
}