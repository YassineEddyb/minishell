
#include <stdio.h>
#include <fcntl.h>

int main ()
{
    int fd1 = open("./file1", O_RDWR, 0644);
    int fd2 = open("./file2", O_RDWR, 0644);

    dup2(fd1, 1);
    dup2(fd2, 1);
    printf("hello world");
}