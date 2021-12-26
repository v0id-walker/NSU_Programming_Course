#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct Node {

    size_t value;
    struct Node* next;
    struct Node* previous;
};

struct Node* NewNode(size_t value) {

    struct Node* result = (struct Node*) malloc(sizeof(struct Node));
    assert(result != NULL);

    result->value = value;
    result->next = NULL;
    result->previous = NULL;

    return result;
}

struct DoublyLinkedList {

    struct Node* first_node;
    struct Node* last_node;
    size_t length;
};

struct DoublyLinkedList* CreateList() {

    struct DoublyLinkedList* result = (struct DoublyLinkedList*) malloc(sizeof(struct DoublyLinkedList));
    assert(result != NULL);

    result->first_node = NULL;
    result->last_node = NULL;
    result->length = 0;

    return result;
}

void push(struct DoublyLinkedList* list, size_t value) {
    assert(list != NULL);

    struct Node* newNode = NewNode(value);
    list->length++;

    if (list->first_node == NULL) {
        list->first_node = newNode;
        list->last_node = newNode;
        return;
    }

    list->last_node->next = newNode;
    newNode->previous = list->last_node;
    list->last_node = newNode;
}

void remove_node(struct DoublyLinkedList* list, struct Node* removing_node) {
    assert(list != NULL);
    assert(removing_node != NULL);

    struct Node* current = list->first_node;
    while (current != removing_node) {
        current = current->next;
    }

    if (list->first_node == removing_node) {
        list->first_node = removing_node->next;
    }
    else if (list->last_node == removing_node) {
        list->last_node = removing_node->previous;
    }

    current->previous->next = current->next;
    current->next->previous = current->previous;

    free(current);
}

void print_list(struct DoublyLinkedList* list) {
    assert(list != NULL);

    if (list->first_node == NULL) {
        printf("List is empty!\n");
        return;
    }

    struct Node* CurrentNode = list->first_node;

    while (CurrentNode != NULL) {
        printf("%zu ", CurrentNode->value);
        CurrentNode = CurrentNode->next;
    }
    
    printf("\n");
}

void free_list(struct DoublyLinkedList* list) {
    assert(list != NULL);

    struct Node* CurrentNode = list->first_node;

    while (CurrentNode != NULL) {
        struct Node* nextNode = CurrentNode->next;
        free(CurrentNode);
        CurrentNode = nextNode;
    }

    free(list);
}
