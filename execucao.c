#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    float stack[MAX_SIZE];
    int top;
} Stack;

void push(Stack *s, float value) {
    if (s->top == MAX_SIZE - 1) {
        printf("Erro: Pilha cheia\n");
        exit(EXIT_FAILURE);
    }
    s->top++;
    s->stack[s->top] = value;
}

float pop(Stack *s) {
    if (s->top == -1) {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
    float value = s->stack[s->top];
    s->top--;
    return value;
}

float evaluateExpression(char *expression) {
    Stack s;
    s.top = -1;

    char *token = strtok(expression, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&s, atof(token));
        } else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/') {
            float b = pop(&s);
            float a = pop(&s);
            switch (token[0]) {
                case '+':
                    push(&s, a + b);
                    break;
                case '-':
                    push(&s, a - b);
                    break;
                case '*':
                    push(&s, a * b);
                    break;
                case '/':
                    push(&s, a / b);
                    break;
            }
        } else if (strcmp(token, "^") == 0) {
            float b = pop(&s);
            float a = pop(&s);
            push(&s, pow(a, b));
        } else if (strcmp(token, "log") == 0) {
            float a = pop(&s);
            push(&s, log10(a));
        } else {
            printf("Operação não suportada: %s\n", token);
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, " ");
    }

    return pop(&s);
}

int main() {
    char expression[MAX_SIZE];

    // Teste 1: 3 4 + 5 *
    printf("Digite a expressão em notação posfixa: ");
    fgets(expression, MAX_SIZE, stdin);
    float result = evaluateExpression(expression);
    printf("Resultado: %.2f\n", result);

    return 0;
}
