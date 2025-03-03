#include <stdio.h>

// EXTRA CREDIT - print the drexel dragon from the readme.md
extern void print_dragon(){
  FILE *file = fopen("dragon.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
    }
        
    char line[256]; // Buffer for each line
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        
    }
    fclose(file);
    // return 1;
}
