#ifndef FIELD_H
#define FIELD_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Field {
    int x_size, y_size;
    char** gen;
    char** next_gen;
} Field;

Field* field_initialisation(char *data, int x, int y); 

void field_delition(Field *field);

void swap_fields(char **prev, char **new);

void next_gen_calculation(Field *field);

char neighbor_count_simple(char **prev_gen, int x, int y);

char neighbor_count_hard(Field *field, int x, int y);

void field_print(Field *field);

#endif
