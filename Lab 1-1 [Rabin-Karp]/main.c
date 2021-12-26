#include <stdio.h>
#include <stdbool.h>

#define BUFFER_SIZE 4096

int degrees_of_three[16] = {1, 3, 9, 27, 81, 243, 729, 2187,
                            6561, 19683, 59049, 177147, 531441, 1594323, 4782969, 14348907};

int get_hash(const int array[], const size_t size) {

    int hash = 0;
    for (size_t i = 0; i < size; ++i) {
        hash += (array[i] % 3) * degrees_of_three[i];
    }
    return hash;
}

int get_partial_hash(const int ch, const int multiplier) {
    return (ch % 3) * multiplier;
}

int get_hash_by_previous(const int previous_hash, const int first_char, const int last_char, const int multiplier) {

    return (previous_hash - (first_char % 3)) / 3 + get_partial_hash(last_char, multiplier);
}

void fill_pattern(int pattern[], size_t* size) {

    int ch;
    size_t i = 0;
    while ((ch = getchar()) != '\n' && i < 16) {
        pattern[i] = ch;
        ++*size;
        ++i;
    }
}

void fill_buffer(int buffer[], size_t index, int* last_index, bool* is_last_char) {

    int ch;
    while (index < BUFFER_SIZE && (ch = getchar()) != EOF) {
        buffer[index] = ch;
        ++index;
    }

    if (ch == EOF) {
        *is_last_char = true;
        *last_index = (int)index - 1;
        return;
    }

    *last_index = BUFFER_SIZE - 1;
}

void compare_by_chars(const int buffer[], size_t cur_index, const size_t checked,
                      const int pattern[], const size_t pattern_size) {

    for (size_t i = 0; i < pattern_size; ++i) {
        printf(" %zu", checked + (cur_index + i) + 1);
        if (pattern[i] != buffer[cur_index+i]) {
            break;
        }
    }
}

void rabin_karp(int buffer[], int pattern[], const int last_filled_index, const size_t checked,
                const size_t pattern_size, const int pattern_hash) {

    int current_hash = get_hash(buffer, pattern_size);
    if (current_hash == pattern_hash) {
        compare_by_chars (buffer, 0, checked, pattern, pattern_size);
    }

    for (int i = 1; i <= (last_filled_index - (int)pattern_size + 1); ++i) {
        current_hash = get_hash_by_previous (current_hash, buffer[i-1], buffer[i+pattern_size-1], degrees_of_three[pattern_size - 1]);
        if (current_hash == pattern_hash) {
            compare_by_chars (buffer, i, checked, pattern, pattern_size);
        }
    }
}

void shift_last_elements(int buffer[], const size_t pattern_size, size_t* checked) {

    size_t shifting_index = BUFFER_SIZE - pattern_size + 1;
    size_t new_index = 0;
    while (shifting_index < BUFFER_SIZE) {
        buffer[new_index] = buffer[shifting_index];
        ++new_index;
        ++shifting_index;
    }
    *checked += (BUFFER_SIZE - pattern_size + 1);
}

int main() {

    int pattern[16];
    size_t pattern_size = 0;
    fill_pattern(pattern, &pattern_size);
    int pattern_hash = get_hash(pattern, pattern_size);

    int buffer[BUFFER_SIZE];
    int last_filled_index = 0;
    size_t checked_elements = 0;
    bool is_last_char = false;

    fill_buffer(buffer, 0, &last_filled_index, &is_last_char);

    printf("%d", pattern_hash);

    while (!is_last_char) {

        rabin_karp (buffer, pattern, last_filled_index, checked_elements, pattern_size, pattern_hash);

        shift_last_elements (buffer, pattern_size, &checked_elements);

        fill_buffer (buffer, pattern_size - 1, &last_filled_index, &is_last_char);
    }

    if (last_filled_index != -1) {
        rabin_karp(buffer, pattern, last_filled_index, checked_elements, pattern_size, pattern_hash);
    }

    return 0;
}
