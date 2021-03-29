#include "file.h"

int read_top_score(char filepath[]) {
    int top_score = 0;
    FILE *top_score_file;

    top_score_file = fopen(filepath, "r");

    if (top_score_file == NULL) {
        printf("Error: fopen()\n");
        exit(1);
    }

    fscanf(top_score_file, "%d", &top_score);

    fclose(top_score_file);

    return top_score;
}

void write_top_score(int new_score, char filepath[]) {
    FILE *top_score_file;

    top_score_file = fopen(filepath, "w");

    if (top_score_file == NULL) {
        printf("Error: fopen()\n");
        exit(1);
    }

    fprintf(top_score_file, "%d", new_score);

    fclose(top_score_file);
}
