
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
    int a[100], n, head, size, total = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter requests: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter head position and disk size: ");
    scanf("%d%d", &head, &size);

    sort(a, n);

    printf("\nSCAN: %d", head);

    for(int i = 0; i < n; i++) {
        if(a[i] >= head) {
            total += abs(head-a[i]);
            head = a[i];
            printf(" -> %d", head);
        }
    }

    total += abs(head-(size-1));
    head = size-1;
    printf(" -> %d", head);

    for(int i = n-1; i >= 0; i--) {
        if(a[i] < head) {
            total += abs(head-a[i]);
            head = a[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Movement = %d\n", total);
    return 0;
}

/* Run:
   gcc scan.c -o scan
   ./scan
*/
