
#include <stdio.h>
#include <stdlib.h>

void sort(int a[], int n) {
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-i-1; j++)
            if(a[j] > a[j+1]) {
                int t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
}

int main() {
    int a[100], n, head, total = 0, first = -1;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter requests: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    sort(a, n);

    printf("\nC-LOOK: %d", head);

    for(int i = 0; i < n; i++) {
        if(a[i] >= head) {
            total += abs(head-a[i]);
            head = a[i];
            printf(" -> %d", head);

            if(first == -1)
                first = i;
        }
    }

    if(first > 0) {
        total += abs(head-a[0]);
        head = a[0];
        printf(" -> %d", head);

        for(int i = 1; i < first; i++) {
            total += abs(head-a[i]);
            head = a[i];
            printf(" -> %d", head);
        }
    }
    else if(first == -1 && n > 0) {
        total += abs(head-a[0]);
        head = a[0];
        printf(" -> %d", head);

        for(int i = 1; i < n; i++) {
            total += abs(head-a[i]);
            head = a[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Movement = %d\n", total);
    return 0;
}

/* Run:
   gcc clook.c -o clook
   ./clook
*/
