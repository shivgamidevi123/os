
#include <stdio.h>

int main()
{
    int n, m, i, j, k = 0, flag;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int a[n][m], max[n][m], need[n][m];
    int avail[m], work[m], finish[n], safe[n];

    printf("Enter Allocation Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&a[i][j]);

    printf("Enter Maximum Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&max[i][j]);

    printf("Enter Available Resources:\n");
    for(j=0;j<m;j++)
        scanf("%d",&avail[j]);

    for(i=0;i<n;i++) {
        finish[i]=0;
        for(j=0;j<m;j++)
            need[i][j]=max[i][j]-a[i][j];
    }

    for(j=0;j<m;j++)
        work[j]=avail[j];

    while(k<n) {
        flag=0;

        for(i=0;i<n;i++) {
            if(finish[i]==0) {
                int possible=1;

                for(j=0;j<m;j++)
                    if(need[i][j]>work[j])
                        possible=0;

                if(possible) {
                    for(j=0;j<m;j++)
                        work[j]+=a[i][j];

                    safe[k++]=i;
                    finish[i]=1;
                    flag=1;
                }
            }
        }

        if(flag==0)
            break;
    }

    if(k==n) {
        printf("\nSystem is SAFE\nSafe Sequence: ");

        for(i=0;i<n;i++)
            printf("P%d ",safe[i]);
    }
    else
        printf("\nSystem is UNSAFE\n");

    return 0;
}


// run :-
//  gcc p5.c -o p5
//  ./p5