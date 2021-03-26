//Это не код а говна из жопы, работает без ошибок, но все равно говна

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 256

typedef struct Node {
    char *data = NULL;
    struct Node *next = NULL;
} Node;

void clear_list(Node *head) {
    if (head == NULL) {
        return;
    } else {
        clear_list(head->next);
    }

    free(head->data);
    free(head);
}

void insert_string(Node *head, char *string) {
    if (head == NULL) {
        return;
    }
    Node *tmp = head;

    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

    tmp->next = (Node *)malloc(sizeof(Node));
    tmp->data = string;
}

char *read_string() {
    char *tmp = NULL;
    char buffer[BUFFER_LENGTH];
    fgets(buffer, BUFFER_LENGTH, stdin);

    if (buffer[0] == '.') {
        if (strlen(buffer) == 2) {
            return NULL;
        }
    }

    tmp = (char *)calloc((strlen(buffer) + 1), sizeof(char));
    memcpy(tmp, buffer, (strlen(buffer) + 1) * sizeof(char));
    return tmp;
}

int main(int argc, char **argv) {
    char *current_string = read_string();
    Node *head = (Node *)malloc(sizeof(Node));
    insert_string(head, current_string);

    while (true) {
        current_string = read_string();
        if (current_string == NULL) break;
        insert_string(head, current_string);
    }

    Node *tmp = head;
    if (head->data != NULL) {
        do {
            if (tmp->data != NULL) {
                printf("%s", tmp->data);
            }
            tmp = tmp->next;
        } while (tmp != NULL);
    }

    clear_list(head);

    return 0;
}