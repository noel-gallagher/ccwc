#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if(argc < 3) {
        fprintf(stderr, "Usage: %s -c <filename>", argv[0]);
        return 1;
    }

    char *option = argv[1];
    char *filename = argv[2];
    
    if(strcmp(option, "-c")) { 
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

    else if(strcmp(option, "-l")) {
        FILE *file = fopen(filename, "r");
        if(file == NULL) {
            perror("Error opening file");
            return 1;
        }
        
        char c;
        int totalLines = 0;
        while((c = fgetc(file)) != EOF) {
            if(c == '\n')
                totalLines++;
        }
    
        printf("%d %s\n", totalLines, filename);
        return 0;
    }
    else if(strcmp(option, "-w")) {
        FILE *file = fopen(filename, "r");
        if(file == NULL) { 
            perror("Error opening file");
            return 1;            
        }

        char c;
        int totalWords = 0;
        while((c = fgetc(file)) != EOF) {
            if(c == ' ' || c == '\n')
                totalWords++;    
        }
        printf("%d %s\n", totalWords, filename);
        return 0;
    }

    fprintf(stderr, "Usage: %s -c <filename>", argv[0]);
    return 1;
}
