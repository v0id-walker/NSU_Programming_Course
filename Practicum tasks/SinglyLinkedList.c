#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define LIST_SIZE 100

struct Node {

    size_t value;
    struct Node* next;
};

struct Node* NewNode(size_t value) {
    struct Node* result = (struct Node*) malloc(sizeof(struct Node));
    assert(result != NULL);

    result->value = value;
    result->next = NULL;

    return result;
}

struct SinglyLinkedList {

    struct Node* first_node;
    struct Node* last_node;

    size_t length;
};

struct SinglyLinkedList* CreateList() {

    struct SinglyLinkedList* result = (struct SinglyLinkedList*) malloc(sizeof(struct SinglyLinkedList));
    assert(result != NULL);

    result->first_node = NULL;
    result->last_node = NULL;
    result->length = 0;

    return result;
}

void push(struct SinglyLinkedList* list, size_t value) {
    assert(list != NULL);

    struct Node* newNode = NewNode(value);
    list->length++;

    if (list->first_node == NULL) {
        list->first_node = newNode;
        list->last_node = newNode;
        return;
    }

    list->last_node->next = newNode;
    list->last_node = newNode;
}

void print_list(struct SinglyLinkedList* list) {
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

void free_list(struct SinglyLinkedList* list) {
    assert(list != NULL);

    struct Node* CurrentNode = list->first_node;

    while (CurrentNode != NULL) {
        struct Node* nextNode = CurrentNode->next;
        free(CurrentNode);
        CurrentNode = nextNode;
    }

    free(list);
}

int main() {

    struct SinglyLinkedList* list = CreateList();

    for (size_t i = 1; i <= LIST_SIZE; i++)
        push(list, i);

    print_list(list);

    free_list(list);

    return 0;
}
