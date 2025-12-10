#include <stdio.h>
#include <string.h>
#include "workout_io.h"

void trimnl(char *s) {
    size_t L = strlen(s);
    while (L > 0 && (s[L-1] == '\n' || s[L-1] == '\r'))
        s[--L] = '\0';
}

void read_line(const char *prompt, char *buf, int size) {
    printf("%s ", prompt);
    if (!fgets(buf, size, stdin)) {
        buf[0] = '\0';
        return;
    }
    trimnl(buf);
}

int read_int(const char *prompt) {
    char line[256];
    int v;

    while (1) {
        printf("%s ", prompt);
        if (!fgets(line, sizeof(line), stdin)) return 0;

        if (sscanf(line, "%d", &v) == 1)
            return v;

        printf("Please enter a valid integer.\n");
    }
}

double read_double(const char *prompt) {
    char line[256];
    double v;

    while (1) {
        printf("%s ", prompt);
        if (!fgets(line, sizeof(line), stdin)) return 0;

        if (sscanf(line, "%lf", &v) == 1)
            return v;

        printf("Please enter a valid number.\n");
    }
}
