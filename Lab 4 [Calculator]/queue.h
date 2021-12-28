#pragma once

#include <assert.h>

#define MAX_INPUT_LEN 1000

typedef int QueueElement;

struct Queue {
    QueueElement data[MAX_INPUT_LEN];
    int first, last;
};

void init_queue(struct Queue* q) {
    assert(q != NULL);

    q->first = 0;
    q->last = 0;
}

void push_queue(struct Queue* q, QueueElement value) {
    assert(q != NULL);

    q->data[q->last] = value;
    q->last++;
}

QueueElement pop_queue(struct Queue* q) {
    assert(q != NULL);

    QueueElement value = q->data[q->first];
    q->first++;

    return value;
}
