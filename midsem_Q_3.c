#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>  

#define MAX 100   

typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

typedef struct Queue {
    Node* data[MAX];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, Node* node) {
    if (q->rear < MAX)
        q->data[q->rear++] = node;
    else
        printf("Queue overflow!\n");
}

Node* dequeue(Queue* q) {
    if (isEmpty(q))
        return NULL;
    return q->data[q->front++];
}

Node* createNode(char ch) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->ch = ch;
    newNode->freq = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int incrementIfExists(Node* root, char ch) {
    Queue q;
    Node* temp;

    if (root == NULL)
        return 0;

    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        temp = dequeue(&q);
        if (temp->ch == ch) {
            temp->freq++;
            return 1; 
        }
        if (temp->left != NULL)
            enqueue(&q, temp->left);
        if (temp->right != NULL)
            enqueue(&q, temp->right);
    }
    return 0; 
}


void insertLevelWise(Node** root, char ch) {
    Queue q;
    Node* temp;

    if (*root == NULL) {
        *root = createNode(ch);
        return;
    }


    if (incrementIfExists(*root, ch))
        return;

   
    initQueue(&q);
    enqueue(&q, *root);

    while (!isEmpty(&q)) {
        temp = dequeue(&q);

        if (temp->left == NULL) {
            temp->left = createNode(ch);
            return;
        } else {
            enqueue(&q, temp->left);
        }

        if (temp->right == NULL) {
            temp->right = createNode(ch);
            return;
        } else {
            enqueue(&q, temp->right);
        }
    }
}




void levelOrderTraversal(Node* root) {
    Queue q;
    Node* temp;

    if (root == NULL)
        return;

    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        temp = dequeue(&q);
        printf("(%c, %d) ", temp->ch, temp->freq);
        if (temp->left != NULL)
            enqueue(&q, temp->left);
        if (temp->right != NULL)
            enqueue(&q, temp->right);
    }
}


int main() {
    char str[] = "programming";
    Node* root = NULL;
    int i, len;

    len = strlen(str);
    for (i = 0; i < len; i++) {
        insertLevelWise(&root, str[i]);
    }

    printf("Level Order Traversal (Character, Frequency):\n");
    levelOrderTraversal(root);

    getch();  
    return 0;
}

