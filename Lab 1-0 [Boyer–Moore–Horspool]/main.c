#include <stdio.h>

#define BUFFER_SIZE 4096

int fill_pattern(unsigned char pattern[]) {

    for (int len = 0; len < 17; ++len) {
        int c = getc(stdin);
        if (c == '\n') {
            return len;
        }
        pattern[len] = (unsigned char) c;
    }

    return 16;
}

void fill_shift_table(int table[], const unsigned char pattern[], const int pattern_len) {

    for (int i = 0; i < 512; ++i) {
        table[i] = pattern_len;
    }

    for (int i = 0; i < (pattern_len - 1); ++i) {
        table[(int)pattern[i]] = pattern_len - i - 1;
    }
}

void fill_buffer(unsigned char buffer[], const int index, int* last_filled_index) {

    int taken_elements = (int) fread(buffer + index, sizeof(unsigned char), BUFFER_SIZE - index, stdin);

    *last_filled_index = index + taken_elements - 1;
}

void compare_by_chars(const unsigned char buffer[], const unsigned char pattern[],
                      int index, const int checked, const int pattern_len) {

    int pattern_index = pattern_len - 1;
    while (pattern_index >= 0) {
        printf("%d ", checked + index + 1);
        if (pattern[pattern_index] != buffer[index]) {
            break;
        }
        --pattern_index;
        --index;
    }
}

void horspool(const unsigned char buffer[], const unsigned char pattern[], int* index,
              const int pattern_len, const int checked, const int shift[], const int last_filled_index) {

    if (last_filled_index < (pattern_len - 1)) {
        return;
    }

    int comparing = pattern_len - 1;

    while (comparing <= last_filled_index) {
        *index = comparing;

        if (buffer[comparing] == pattern[pattern_len - 1]) {
            compare_by_chars(buffer, pattern, comparing, checked, pattern_len);
        } else {
            printf("%d ", checked + comparing + 1);
        }

        comparing += shift[(int)buffer[comparing]];
    }

    *index = *index - (pattern_len - shift[(int)buffer[*index]]) + 1;
    /* index which indicates the start of shifting elements*/
}

void shift_last_elements(unsigned char buffer[], int* index, int* checked_elements) {

    *checked_elements += *index;

    if (*index == BUFFER_SIZE) {
        *index = 0;
        return;
    }

    int new_index = 0;
    while (*index < BUFFER_SIZE) {
        buffer[new_index] = buffer[*index];
        ++*index;
        ++new_index;
    }

    *index = new_index;
}

int main(void) {

    unsigned char pattern[16];
    int pattern_len = fill_pattern(pattern);

    int shift_table[512];
    fill_shift_table(shift_table, pattern, pattern_len);

    unsigned char buffer[BUFFER_SIZE];

    int next_index = 0;
    int last_filled_index = -1;
    int checked_elements = 0;

    while (1) {
        fill_buffer(buffer, next_index, &last_filled_index);

        horspool(buffer, pattern, &next_index, pattern_len, checked_elements, shift_table, last_filled_index);

        if (feof(stdin)) {
            break;
        }

        shift_last_elements(buffer, &next_index, &checked_elements);
    }

    return 0;
}
