#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int i;
    struct stat buf;
    
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        printf("Prints the type of each specified file.\n");
        return 1;
    }
    
    for (i = 1; i < argc; i++) {
        printf("File: %s -> ", argv[i]);
        
        if (lstat(argv[i], &buf) < 0) {
            perror("lstat error");
            continue;
        }
        
        if (S_ISREG(buf.st_mode))
            printf("regular file\n");
        else if (S_ISDIR(buf.st_mode))
            printf("directory\n");
        else if (S_ISCHR(buf.st_mode))
            printf("character device file\n");
        else if (S_ISBLK(buf.st_mode))
            printf("block device file\n");
        else if (S_ISFIFO(buf.st_mode))
            printf("FIFO/pipe file\n");
        else if (S_ISLNK(buf.st_mode))
            printf("symbolic link\n");
        else if (S_ISSOCK(buf.st_mode))
            printf("socket file\n");
        else
            printf("unknown file type\n");
    }
    
    return 0;
}
