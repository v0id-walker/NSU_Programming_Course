#include <stdio.h>
#include <assert.h>

#define MAX_STACK_SIZE 100

typedef int StackElement;

struct Stack {

    StackElement data[MAX_STACK_SIZE];
    int top;
};

void stack_init(struct Stack* s) {
    assert(s != NULL);

    s->top = 0;
}

size_t stack_size(struct Stack* s) {
    assert(s != NULL);

    return s->top;
}

StackElement stack_peek(struct Stack* s) {
    assert(s != NULL);

    if ((s->top) > 0) {
        return s->data[s->top - 1];
    }
    else {
        printf("Stack is empty!\n");
        return 0;
    }
}

void stack_push(struct Stack* s, StackElement x) {
    assert(s != NULL);

    if (s->top < MAX_STACK_SIZE) {
        s->data[s->top] = x;
        s->top++;
    } else {
        printf("Stack is full, total elements: %d!\n", s->top);
    }
}

StackElement stack_pop(struct Stack* s) {
    assert(s != NULL);

    StackElement elem;

    if ((s->top) > 0) {
        s->top--;
        elem = s->data[s->top];
        return elem;
    } else {
        printf("Stack is empty!\n");
        return 0;
    }
}
