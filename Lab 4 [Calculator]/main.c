#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "token.h"

int return_result(const int error_code) {

    if (error_code == 1) {
        printf("syntax error");
        return 0;
    }
    if (error_code == 2) {
        printf("division by zero");
        return 0;
    }

    return 0;
}

void take_input(struct Queue* input) {

    for (int i = 0; i < MAX_INPUT_LEN; ++i) {
        int ch;
        if ((ch = getchar()) == '\n') {
            break;
        }
        push_queue(input, ch);
    }
}

void to_polish_notation(struct Queue* input, struct Queue* result, struct Queue* tokens, int* error_code) {

    struct Stack operators;
    init_stack(&operators);

    int parentheses_balance = 0;
    char prev_token = 's';

    while ((input->first < input->last) && *error_code == 0) {

        int element = pop_queue(input);
        char token = get_token(element);

        switch (token) {
            case 'n':
                if (prev_token == 'n') {                  /* if the number has more than one digit */
                    result->data[result->last-1] *= 10;
                    result->data[result->last-1] += element - '0';
                } else {
                    push_queue(result, element - '0');
                    push_queue(tokens, 'n');
                } break;

            case '(':
                push_stack(&operators, element);
                ++parentheses_balance; break;

            case ')':
                if (parentheses_balance < 1 || (prev_token != 'n' && prev_token != ')')) {
                    *error_code = 1;
                    return;
                }
                while (get_top(&operators) != '(') {
                    push_queue(result, pop_stack(&operators));
                    push_queue(tokens, 'o');
                }
                pop_stack(&operators);
                --parentheses_balance; break;

            case 'o':
                while ((operators.top != 0) && (get_priority(get_top(&operators)) >= get_priority(element))) {
                    push_queue(result, pop_stack(&operators));
                    push_queue(tokens, 'o');
                }
                push_stack(&operators, element); break;

            default:
                *error_code = 1;
                return;
        }

        prev_token = token;
    }

    while (operators.top != 0) {
        push_queue(result, pop_stack(&operators));
        push_queue(tokens, 'o');
    }
}

int calculate(const int a, const int b, const int operator) {

    if (operator == '+') {
        return b + a;
    }
    if (operator == '-') {
        return b - a;
    }
    if (operator == '/') {
        return b / a;
    }

    return b * a;
}

void read_polish_notation(struct Queue* polish_notation, struct Queue* tokens, int* error_code) {

    struct Stack operands;
    init_stack(&operands);

    while ((polish_notation->first < polish_notation->last) && *error_code == 0) {

        int a, b;
        int element = pop_queue(polish_notation);
        char token = (char) pop_queue(tokens);

        if (token == 'n') {
            push_stack(&operands, element);
        }
        else if (token == 'o') {
            if (operands.top < 2) {
                *error_code = 1;
                return;
            }
            a = pop_stack(&operands);
            b = pop_stack(&operands);

            if (element == '/' && a == 0) {                  /* division by zero */
                *error_code = 2;
                return;
            }

            push_stack(&operands, calculate(a, b, element));
        }
    }

    if (operands.top != 1) {
        *error_code = 1;
        return;
    }

    printf("%d", pop_stack(&operands));
}


int main(void) {

    struct Queue input;
    init_queue(&input);

    take_input(&input);

    if (input.last == 0) {
        return return_result(1);                  /* if an empty line was received */
    }
    if (get_token(input.data[0]) == 'o' || get_token(input.data[input.last-1]) == 'o') {
        return return_result(1);                  /* if an operator stays in the beginning/end of the line */
    }

    struct Queue polish_notation;
    init_queue(&polish_notation);

    struct Queue tokens;
    init_queue(&tokens);

    int error_code = 0;

    to_polish_notation(&input, &polish_notation, &tokens, &error_code);

    if (error_code == 0) {
        read_polish_notation(&polish_notation, &tokens, &error_code);
    }

    return return_result(error_code);
}
