#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

typedef enum {
    OPTION_UNKNOWN,
    OPTION_C,
    OPTION_L,
    OPTION_W,
    OPTION_M
} Parsed_arg;

Parsed_arg parse_arg(const char *opt_str) {
    if (strcmp(opt_str, "-c") == 0) return OPTION_C;
    else if (strcmp(opt_str, "-l") == 0) return OPTION_L;
    else if (strcmp(opt_str, "-w") == 0) return OPTION_W;
    else if (strcmp(opt_str, "-m") == 0) return OPTION_M;
    else return OPTION_UNKNOWN;
}


FILE* open_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        perror("Error opening file");
    }
    return file;
}

void count_lines(FILE *file, char *filename) {
    char c;
    int totalLines = 0;
    while((c = fgetc(file)) != EOF) {
        if(c == '\n')
        {
            totalLines++;
        }
    }
    printf("%d %s\n", totalLines, filename);
}

void count_words(FILE *file, char *filename) {
    char c;
    int totalWords = 0;
    bool inWord = false;
    while((c = fgetc(file)) != EOF) {
        if (!(c == ' ' || c == '\n' || c == '\t')) 
        {
            inWord = true;
        }
        else 
        {
            if(inWord) 
            {
                inWord = false;
                totalWords++;
            }
        }
    }
    printf("%d %s\n", totalWords, filename);
}

int is_not_whitespace(char c) {
    return !(c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r');
}

void count_chars(FILE *file, char *filename) {
    char c;
    int totalChars = 0;
    while((c = fgetc(file)) != EOF) 
    {
        if (is_not_whitespace(c)) 
        {
            totalChars++;
        }
    }
    printf("%d %s\n", totalChars, filename);
}
int get_file_size(char *filename) {
    int fd = open(filename, O_RDONLY);
        if(fd <0) 
        {
            perror("Error opening file");
            return 1;
        }

        struct stat sb;
        if (fstat(fd, &sb) == -1)
        {
            perror("Error getting file size");
            close(fd);
            return 1;
        }

        printf("%lu %s\n", sb.st_size, filename);
        close(fd);
        return 0;
}

int main(int argc, char *argv[]) {
    if(argc < 3) 
    {
        fprintf(stderr, "Invalid option. Usage: %s -c || -l || -w || -m <filename>\n", argv[0]);
        return 1;
    }

    char *option = argv[1];
    Parsed_arg p_arg = parse_arg(option);
    char *filename = argv[2];
    FILE *file;

    switch(p_arg ){
        case OPTION_C:
            return get_file_size(filename); 
        case OPTION_L:
        case OPTION_W:
        case OPTION_M:
            file = open_file(filename);
            if(file == NULL) 
            {
                return 1;
            }
            if(p_arg == OPTION_L) count_lines(file, filename);
            else if(p_arg == OPTION_W) count_words(file, filename);
            else if(p_arg == OPTION_M) count_chars(file, filename);
            fclose(file);
            break;
        default: 
        fprintf(stderr, "Invalid option. Usage: %s -c || -l || -w || -m <filename>\n", argv[0]);
        return 1;
    }
    return 0;
}

