#include <stdio.h>

int main() {
    int n1[] = {2, 4, 6};
    int n2[] = {3, 5, 9};
    int n3[10];  

    int size1 = 3, size2 = 3;
    int i = 0, j = 0, k = 0;
 
    while (i < size1 && j < size2) {
        if (n1[i] < n2[j]) {
            n3[k++] = n1[i++];
        } else {
            n3[k++] = n2[j++];
        }
    }

    while (i < size1) {
        n3[k++] = n1[i++];
    }

    while (j < size2) {
        n3[k++] = n2[j++];
    }

    printf("Merged Sorted Array: ");
    for (i = 0; i < k; i++) {
        printf("%d ", n3[i]);
    }

    return 0;
}
