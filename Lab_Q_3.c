#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define STR_LEN 20

typedef struct {
    char items[MAX][STR_LEN];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, char *op) {
    if (isFull(s)) {
        printf("Stack overflow! Cannot perform operation.\n");
        return;
    }
    strcpy(s->items[++(s->top)], op);
}

char* pop(Stack *s) {
    if (isEmpty(s)) return NULL;
    return s->items[s->top--];
}

void clear(Stack *s) {
    s->top = -1;
}

void performOperation(Stack *undo, Stack *redo, char *op) {
    push(undo, op);
    clear(redo);
    printf("Performed operation: \"%s\"\n", op);
}

void undoOperation(Stack *undo, Stack *redo) {
    char *op = pop(undo);
    if (!op) {
        printf("Nothing to undo.\n");
        return;
    }
    push(redo, op);
    if (!isEmpty(undo))
        printf("Undone. Next undoable: \"%s\"\n", undo->items[undo->top]);
    else
        printf("Undo completed. No more operations to undo.\n");
}

void redoOperation(Stack *undo, Stack *redo) {
    char *op = pop(redo);
    if (!op) {
        printf("Nothing to redo.\n");
        return;
    }
    push(undo, op);
    if (!isEmpty(redo))
        printf("Redo completed. Next redoable: \"%s\"\n", redo->items[redo->top]);
    else
        printf("Redo completed. No more operations to redo.\n");
}

int main() {
    Stack undo, redo;
    init(&undo);
    init(&redo);

    performOperation(&undo, &redo, "op1");
    performOperation(&undo, &redo, "op2");
    performOperation(&undo, &redo, "op3");

    undoOperation(&undo, &redo);
    redoOperation(&undo, &redo);
    performOperation(&undo, &redo, "op4");
    undoOperation(&undo, &redo);
    undoOperation(&undo, &redo);
    redoOperation(&undo, &redo);

    return 0;
}
