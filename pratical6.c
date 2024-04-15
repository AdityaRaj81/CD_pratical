#include <stdio.h>
#include <ctype.h>

int stack[50];
int top = -1;

void push(int item) {
    stack[++top] = item;
}

int pop() {
    return stack[top--];
}

int isOperator(char symbol) {
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/')
        return 1;
    return 0;
}

int getPrecedence(char symbol) {
    switch (symbol) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

void parseExpression(char expression[]) {
    int i;
    char symbol;
    
    for (i = 0; expression[i] != '\0'; i++) {
        symbol = expression[i];
        
        if (isalnum(symbol)) {
            printf("%c ", symbol);
        } else if (isOperator(symbol)) {
            while (top != -1 && getPrecedence(stack[top]) >= getPrecedence(symbol)) {
                printf("%c ", pop());
            }
            push(symbol);
        } else if (symbol == '(') {
            push(symbol);
        } else if (symbol == ')') {
            while (stack[top] != '(') {
                printf("%c ", pop());
            }
            pop(); // Discard the '('
        }
    }
    
    while (top != -1) {
        printf("%c ", pop());
    }
}

int main() {
    char expression[50];
    printf("Enter an infix expression: ");
    fgets(expression, sizeof(expression), stdin);
    printf("Postfix expression: ");
    parseExpression(expression);
    return 0;
}
