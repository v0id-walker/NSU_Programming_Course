#pragma once

char get_token(const int elem) {

    if ((elem >= '0') && (elem <= '9')) {
        return 'n';                  /* number */
    }
    if (elem == '+' || elem == '-' || elem == '/' || elem == '*') {
        return 'o';                  /* operator */
    }
    if (elem == '(') {
        return '(';
    }
    if (elem == ')') {
        return ')';
    }

    return 's';                  /* syntax error */
}

int get_priority(const int elem) {

    if (elem == '*' || elem == '/') {
        return 4;
    }
    if (elem == '+' || elem == '-') {
        return 2;
    }

    return 1;
}
