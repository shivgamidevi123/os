
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p1[2], p2[2], pid;
    char path[100], data[100];

    pipe(p1);
    pipe(p2);

    printf("Enter full path: ");
    scanf("%99s", path);

    pid = fork();

    if (pid > 0) {              // Parent
        close(p1[0]);
        close(p2[1]);

        write(p1[1], path, strlen(path) + 1);
        close(p1[1]);

        wait(NULL);

        read(p2[0], data, sizeof(data));
        printf("***File content***\n%s", data);
        close(p2[0]);
    }
    else if (pid == 0) {        // Child
        close(p1[1]);
        close(p2[0]);

        read(p1[0], path, sizeof(path));
        close(p1[0]);

        FILE *fp = fopen(path, "r");

        if (fp == NULL)
            strcpy(data, "Could not open file...\n");
        else {
            int n = fread(data, 1, 99, fp);
            data[n] = '\0';
            fclose(fp);
        }

        write(p2[1], data, strlen(data) + 1);
        close(p2[1]);
    }

    return 0;
}

/* Run:
   gcc practical7.c -o practical7
   ./practical7
*/
