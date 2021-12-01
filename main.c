#include <stdio.h>
#include <math.h>

int bad_input() {
    printf("bad input");
    return 0;
}

int is_correct_symbol(int b1, char symbol) {
    if (!((symbol >= '0' && symbol <= '9') || (symbol >= 'A' && symbol <= 'F') || (symbol >= 'a' && symbol <= 'f') || symbol == '.'))
        return 0;
    if ((symbol >= '0' && symbol <= '9') && ((symbol - '0') > (b1 - 1)))    // запись цифр в b1
        return 0;
    if ((symbol >= 'A' && symbol <= 'F') && ((symbol - 55) > (b1 - 1)))     // запись заглавных букв в b1
        return 0;
    if ((symbol >= 'a' && symbol <= 'f') && ((symbol - 87) > (b1 - 1)))    // запись строчных букв в b1
        return 0;
    return 1;
}

void convert_number(int *result_int, int *result_frac, int b1, int b2,
                    const int* input_int, const int* input_frac, int len_int, int len_frac) {
    long long decimal_int = 0;
    long double decimal_frac = 0.0;
    for (int i = 0; i <= len_int - 1; i++) {
        if (input_int[i] == -1)
            break;
        decimal_int += (long long)(input_int[i] * (powl(b1, len_int - i - 1)));
    }
    for (int i = 0; i <= len_frac - 1; i++) {
        if (input_frac[i] == -1)
            break;
        decimal_frac += input_frac[i] * (powl(b1, -1 - i));
    }

    int i = 0;
    while (decimal_int >= b2) {                 // перевод целой части
        result_int[i] = (int)(decimal_int % b2);
        decimal_int /= b2;
        i++;
    }
    result_int[i] = (int)decimal_int;
    i = 0;

    while ((decimal_frac != 0) && i != 12) {
        decimal_frac *= b2;                     // перевод дробной части
        result_frac[i] = (int)decimal_frac;
        decimal_frac -= (int)decimal_frac;
        i++;
    }
}

void print_result(const int* result_int, const int* result_frac) {
    int num;
    for (int i = 0; i < 48; i++) {
        num = result_int[47-i];
        if (num == -1)
            continue;
        num > 9 ? printf("%c", num + 87) : printf("%d", num);
    }
    for (int i = 0; i < 12; i++) {
        num = result_frac[i];
        if (num == -1)
            break;
        else if (i == 0)
            printf(".");
        num > 9 ? printf("%c", num + 87) : printf("%d", num);
    }
}


int main(void) {
    int b1 = 0, b2 = 0;
    char input[13] = "_____________";

    if(scanf("%d %d", &b1, &b2) != 2)
        return bad_input();
    if (b1 < 2 || b1 > 16 || b2 < 2 || b2 > 16)
        return bad_input();

    char symbol;
    for (int i = 0; i < 13; i++) {
        if(scanf("%c", &symbol) != 1)
            return bad_input();
        if (symbol == '\n' && i == 0) {         // для случая, если первым элементом считался Enter
            if (scanf("%c", &symbol) != 1)
                return bad_input();
        }
        else if (symbol == '\n')
            break;
        input[i] = symbol;
    }

    int input_int[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};     // первоначальная запись числа
    int input_frac[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int len_int = 0, len_frac = 0;
    int point_exists = 0;
    for (int i = 0; i < 13; i++) {
        symbol = input[i];
        if (symbol == '_')
            break;
        if (symbol == '.') {
            point_exists += 1;
            continue;
        }
        if (point_exists == 0) {
            if (is_correct_symbol(b1, symbol) == 0)
                return bad_input();
            len_int++;
            if (symbol >= 'a')
                input_int[i] = symbol - 87;
            else if (symbol >= 'A')
                input_int[i] = symbol - 55;
            else input_int[i] = symbol - '0';
        }
        else {
            if (is_correct_symbol(b1, symbol) == 0)
                return bad_input();
            len_frac++;
            if (symbol >= 'a')
                input_frac[len_frac-1] = symbol - 87;
            else if (symbol >= 'A')
                input_frac[len_frac-1] = symbol - 55;
            else input_frac[len_frac-1] = symbol - '0';
        }
    }
    if (point_exists > 1 || (point_exists == 1 && (len_int == 0 || len_frac == 0)))
        return bad_input();                     // проверяем корректность ввода точек


    int result_int[48];                               // конечная запись числа
    int result_frac[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    for (int i = 0; i < 48; i++)
        result_int[i] = -1;

    convert_number (result_int, result_frac, b1, b2, input_int, input_frac, len_int, len_frac);

    print_result (result_int, result_frac);
    return 0;
}
