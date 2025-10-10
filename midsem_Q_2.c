#include <stdio.h>
#include <stdlib.h>

struct Node {
    int songID;
    struct Node* next;
};

struct Node* newNode(int id) {
    struct Node* t = (struct Node*) malloc(sizeof(struct Node));
    if (t == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    t->songID = id;
    t->next = NULL;
    return t;
}

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d", head->songID);
        if (head->next != NULL) printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

struct Node* reversePlaylistSegment(struct Node* head, int m, int n) {
    if (head == NULL || m == n) return head;

    struct Node dummy;
    dummy.next = head;
    struct Node* prev = &dummy;

    int i;
    for (i = 1; i < m; i++)
        prev = prev->next;

    struct Node* curr = prev->next;
    struct Node* nxt;

    for (i = 0; i < n - m; i++) {
        nxt = curr->next;
        curr->next = nxt->next;
        nxt->next = prev->next;
        prev->next = nxt;
    }

    return dummy.next;
}

int main() {
    struct Node* head = newNode(101);
    head->next = newNode(102);
    head->next->next = newNode(103);
    head->next->next->next = newNode(104);
    head->next->next->next->next = newNode(105);
    head->next->next->next->next->next = newNode(106);
    head->next->next->next->next->next->next = newNode(107);

    printf("Original Playlist:\n");
    printList(head);

    int m = 2, n = 5;
    head = reversePlaylistSegment(head, m, n);

    printf("Modified Playlist:\n");
    printList(head);

    printf("\nPress Enter to exit...");
    getchar(); 
    return 0;
}
