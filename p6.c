// 6th a :- client
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    int fd;
    char buff[1024], result[1024];

    mkfifo("myfifo1", 0666);
    mkfifo("myfifo2", 0666);

    printf("Enter the sentences: ");
    fgets(buff, sizeof(buff), stdin);

    fd = open("myfifo1", O_WRONLY);
    write(fd, buff, strlen(buff)+1);
    close(fd);

    printf("Data sent to server.\n");

    printf("Press Enter after server execution...\n");
    getchar();

    fd = open("myfifo2", O_RDONLY);
    read(fd, result, sizeof(result));
    close(fd);

    printf("***RESULT***\n%s", result);

    return 0;
}

// 6th b :- server

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    int fd, ch=0, w=0, l=0;
    char buff[1024];
    char result[100];

    mkfifo("myfifo1", 0666);
    mkfifo("myfifo2", 0666);

    fd = open("myfifo1", O_RDONLY);
    read(fd, buff, sizeof(buff));
    close(fd);

    for(int i=0; buff[i]!='\0'; i++)
    {
        if((buff[i]>='a' && buff[i]<='z') ||
           (buff[i]>='A' && buff[i]<='Z'))
            ch++;

        if(buff[i]==' ' || buff[i]=='\n')
            w++;

        if(buff[i]=='\n')
            l++;
    }

    sprintf(result, "Char count:%d\nWord count:%d\nLine count:%d\n",
            ch, w, l);

    fd = open("myfifo2", O_WRONLY);
    write(fd, result, strlen(result)+1);
    close(fd);

    printf("Data sent to client.\n");

    return 0;
}

// Terminal 1 – Start server first:
// gcc server.c -o server
// ./server


// Terminal 2 – Start client:
// gcc client.c -o client
// ./client

