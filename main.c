#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if(argc < 3) {
        fprintf(stderr, "Usage: %s -c <filename>", argv[0]);
        return 1;
    }

    char *filename = argv[2];
    
    int fd = open(filename, O_RDONLY);
    if(fd <0) {
        perror("Error opening file");
        return 1;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("Error getting file size");
        close(fd);
        return 1;
    }

    printf("%lu %s\n", sb.st_size, filename);
    return 0;
}
