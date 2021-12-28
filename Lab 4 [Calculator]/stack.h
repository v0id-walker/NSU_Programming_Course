#pragma once

#include <assert.h>

#define MAX_INPUT_LEN 1000

typedef int StackElement;

struct Stack {
    StackElement data[MAX_INPUT_LEN];
    int top;
};

void init_stack(struct Stack* s) {
    assert(s != NULL);
    s->top = 0;
}

StackElement get_top(struct Stack* s) {
    assert(s != NULL);

    return s->data[s->top - 1];
}

void push_stack(struct Stack* s, StackElement x) {
    assert(s != NULL);

    s->data[s->top] = x;
    s->top++;
}

StackElement pop_stack(struct Stack* s) {
    assert(s != NULL);
    StackElement elem;

    s->top--;
    elem = s->data[s->top];
    return elem;
}
