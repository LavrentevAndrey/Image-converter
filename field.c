#include "field.h"

// Выделение памяти под структуру поля
Field* field_initialisation(char *data, int x, int y) {
    // Выделение памяти под действующее поколение
    char **pgen = (char**)calloc(y, sizeof(char*)); 
    char *gen = (char*)calloc(x * y, sizeof(char));
    for (int i = 0; i < y; i++)
        pgen[i] = gen + x * i;

    // Заполняем начальное состояние для поля
    for (int i = 0; i < x * y; i++)
        gen[i] = data[i];
    
    // Выделение памяти под следующие поколение
    char **pnext_gen = (char**)calloc(y, sizeof(char*));
    char *next_gen = (char*)calloc(x * y, sizeof(char));
    for (int i = 0; i < y; i++)
        pnext_gen[i] = next_gen + x * i;
    
    // Заполнение полей структуры
    Field *pfield = (Field*)malloc(sizeof(Field));
    pfield->gen = pgen;
    pfield->next_gen = pnext_gen;
    pfield->x_size = x;
    pfield->y_size = y;
    return pfield;
}

// Очищает всю выдеоенную под поле память
void field_delition(Field *field) {
    free(field->gen[0]);
    free(field->gen);
    free(field->next_gen[0]);
    free(field->next_gen);
    free(field);
}

// Меняем поля местами чтобы перейти к новому поколению
void swap_fields(char **prev, char **new) {
    if (prev == NULL || new == NULL) {
        perror("Somthing went wrong in fields pointers");
        exit(EXIT_FAILURE);
    }
    char **tmp = prev;
    prev = new;
    new = tmp;
}

// Просчёт следующего поколения
void next_gen_calculation(Field *field) {
    char **prev_gen = field->gen;
    char **next_gen = field->next_gen;
    int x = field->x_size, y = field->y_size;

    register char neighbors;
    // Смотрим следующее поколение для неграничных клеток
    for (int i = 1; i < y - 1; i++) {
        for (int j = 1; j < x - 1; j++) {
            neighbors = neighbor_count_simple(prev_gen, i, j);
            // Краткая и эффективная запись условий зарождения, выживания и умирания
            next_gen[i][j] = prev_gen[i][j] ? (neighbors == 2) || (neighbors == 3) : neighbors == 3; 
        }
    }
    // Верхняя и нижняя границы
    int i1 = 0, i2 = y - 1;
    for (int j = 0; j < x; j++) {
        neighbors = neighbor_count_hard(field, i1, j);
        next_gen[i1][j] = prev_gen[i1][j] ? (neighbors == 2) || (neighbors == 3) : neighbors == 3;
        neighbors = neighbor_count_hard(field, i2, j);
        next_gen[i2][j] = prev_gen[i2][j] ? (neighbors == 2) || (neighbors == 3) : neighbors == 3;
    }
    
    // Правые и левые края
    int j1 = 0, j2 = x - 1;
    for (int i = 1; i < y - 1; i++) { // Не просматриваем угловые клетки
        neighbors = neighbor_count_hard(field, i, j1);
        next_gen[i][j1] = prev_gen[i][j1] ? (neighbors == 2) || (neighbors == 3) : neighbors == 3;
        neighbors = neighbor_count_hard(field, i, j2);
        next_gen[i][j2] = prev_gen[i][j2] ? (neighbors == 2) || (neighbors == 3) : neighbors == 3;
    }
}


// Функция считающая количетво соседей у клетки не на границе
char neighbor_count_simple(char **prev_gen, int y, int x) {
    char count = 0;
    for (int i = y - 1; i < y + 2; i++)
        for (int j = x - 1; j < x + 2; j++)
            count += prev_gen[i][j]; // Считаем сумму всех значений соседей
    
    return count - 1; // Вычитаем единицу т.к. посчитали искомую клетку
}

// Усложнённая версия функции расположенной выше, нужная для обработки краёв поля
char neighbor_count_hard(Field *field, int y, int x) {
    int max_x = field->x_size, max_y = field->y_size;
    char count = 0;
    for (int i = y - 1; i < y + 2; i++) {
        for (int j = x - 1; j < x + 2; j++) {
            i = (i + max_y) % max_y; // кольцевание кординаты по оси y
            j = (j + max_x) % max_x; // кольцевание кординаты по оси x // Теперь топология у поля такая же как и у тора
            count += field->gen[i][j]; // Считаем сумму всех значений соседей
        }
    }

    return count - 1; // Вычитаем единицу т.к. посчитали искомую клетку
}

void field_print(Field *field) {
    int max_x = field->x_size, max_y = field->y_size;
    char **data = field->gen;
    for (int i = 0; i < max_y; i++) {
        for (int j = 0; j < max_x; j++) {
            if (data[i][j] == 1)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
}