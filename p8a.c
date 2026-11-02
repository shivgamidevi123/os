
#include <stdio.h>
#include <stdlib.h>

int main() {
    int a[100], v[100] = {0};
    int n, head, total = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter requests: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nSSTF: %d", head);

    for(int i = 0; i < n; i++) {
        int min = 9999, p = -1;

        for(int j = 0; j < n; j++) {
            if(!v[j] && abs(head-a[j]) < min) {
                min = abs(head-a[j]);
                p = j;
            }
        }

        v[p] = 1;
        total += min;
        head = a[p];

        printf(" -> %d", head);
    }

    printf("\nTotal Movement = %d\n", total);
    return 0;
}

/* Run:
   gcc sstf.c -o sstf
   ./sstf
*/
