#include <stdio.h>
#include <string.h>  
#define DAYS 30

struct Member {
    char name[50];
    int steps[DAYS];
};

void analyzeSteps(struct Member members[], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        int daysOver10k = 0;
        int maxSteps = 0;

        for (j = 0; j < DAYS; j++) {
            if (members[i].steps[j] > 10000)
                daysOver10k++;
            if (members[i].steps[j] > maxSteps)
                maxSteps = members[i].steps[j];
        }

        printf("\nMember Name: %s\n", members[i].name);
        printf("Days exceeded 10,000 steps: %d\n", daysOver10k);
        printf("Maximum steps in the month: %d\n", maxSteps);
    }
}

int main() {
    struct Member members[2];
    int i;

    strcpy(members[0].name, "Alice");
    strcpy(members[1].name, "Bob");

    int aliceSteps[DAYS] = {12000, 8000, 15000, 9000, 11000, 7000, 10500, 13000, 9500, 8000,
                             11500, 10000, 8700, 9900, 10200, 7600, 12300, 8900, 9100, 10800,
                             8700, 12000, 9700, 8500, 9400, 11300, 8700, 10100, 8800, 9200};
    for (i = 0; i < DAYS; i++)
        members[0].steps[i] = aliceSteps[i];

    int bobSteps[DAYS] = {9500, 9700, 9900, 10200, 12000, 8000, 13000, 7000, 11000, 9500,
                           10000, 12300, 8700, 9500, 8800, 9300, 9400, 11000, 8700, 8900,
                           12000, 8700, 8600, 9800, 10200, 8900, 9100, 9400, 10300, 9600};
    for (i = 0; i < DAYS; i++)
        members[1].steps[i] = bobSteps[i];

    analyzeSteps(members, 2);

    printf("\nPress Enter to exit...");
    getchar();
    return 0;
}
