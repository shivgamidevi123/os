#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int a[20], n, i, j, temp;
    pid_t pid;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    pid = fork();

    if(pid == 0)
    {
        // Child: Ascending order
        for(i = 0; i < n; i++)
            for(j = 0; j < n-i-1; j++)
                if(a[j] > a[j+1])
                {
                    temp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = temp;
                }

        printf("\nChild Process (Ascending Order)\n");
        for(i = 0; i < n; i++)
            printf("%d ", a[i]);
    }
    else if(pid > 0)
    {
        wait(NULL);

        // Parent: Descending order
        for(i = 0; i < n; i++)
            for(j = 0; j < n-i-1; j++)
                if(a[j] < a[j+1])
                {
                    temp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = temp;
                }

        printf("\nParent Process (Descending Order)\n");
        for(i = 0; i < n; i++)
            printf("%d ", a[i]);
    }
    else
        printf("Fork failed!");

    return 0;
}


// for running :- use the below 2 lines seperately.. one after other(for command dont use "//" this).
//  gcc p2.c -o p2
//  ./p2