
# define MAC '>'
# include <fcntl.h>

int main () {
    int fd = open("file",  O_RDONLY, 0644);
    if (fd == -1)
        printf("Error opening input file\n");
}