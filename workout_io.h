#ifndef WORKOUT_IO_H
#define WORKOUT_IO_H

void trimnl(char *s);

void read_line(const char *prompt, char *buf, int size);

int read_int(const char *prompt);

double read_double(const char *prompt);

#endif
