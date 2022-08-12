#include "field.h"
#include <unistd.h> // для sleep()
#define XSIZE 80
#define YSIZE 25

int main() {
    // Начальная фигура diehard
    char start[YSIZE * XSIZE] = {[1080] = 1, [1079] = 1, [1081] = 1, [1075] = 1, [1154] = 1, [1155] = 1, [1240] = 1};
    // Создаём поле
    Field *field = field_initialisation(start, XSIZE, YSIZE);
    int time = 0; // Время работы программы 
    while (time < 30) {
        field_print(field); // Выводим на экран поле
        next_gen_calculation(field); // Просчитываем следующее поколение
        swap_fields(field->gen, field->next_gen); // Переходим к следующему поколению
        sleep(1); // Задержка одна секунда
        time++; // Увеличиваем время
    }
    // Удаляем поле
    field_delition(field);
}
