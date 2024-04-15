#include <stdio.h>
#include <string.h>

#define SUCCESS 1
#define FAILED 0

const char *cursor;
char string[64];

int E(), Edash(), T(), Tdash(), F();

int main() {
    puts("Enter the string");
    scanf("%s", string); // Read input from the user
    cursor = string;
    puts("");
    puts("Input Action");
    puts(" ");
    if (E() && *cursor == '\0')
        puts("String is successfully parsed");
    else
        puts("Error in parsing String");
    return 0;
}

// Grammar rule: E -> T E'
int E() {
    printf("%-16s E -> T E'\n", cursor);
    if (T()) {
        if (Edash())
            return SUCCESS;
        return FAILED;
    }
    return FAILED;
}

int Edash() {
    if (*cursor == '+') {
        printf("%-16s E' -> + T E'\n", cursor);
        cursor++;
        if (T()) {
            if (Edash())
                return SUCCESS;
            else
                return FAILED;
        }
        return FAILED;
    } else if (*cursor == '\0') {
        printf("%-16s E' -> $\n", cursor);
        return SUCCESS;
    }
    return FAILED;
}

int T() {
    printf("%-16s T -> F T'\n", cursor);
    if (F()) {
        if (Tdash())
            return SUCCESS;
        return FAILED;
    }
    return FAILED;
}

int Tdash() {
    if (*cursor == '*') {
        printf("%-16s T' -> * F T'\n", cursor);
        cursor++;
        if (F()) {
            if (Tdash())
                return SUCCESS;
            else
                return FAILED;
        }
        return FAILED;
    } else if (*cursor == '+' || *cursor == '\0') {
        printf("%-16s T' -> $\n", cursor);
        return SUCCESS;
    }
    return FAILED;
}

int F() {
    if (*cursor == '(') {
        printf("%-16s F -> ( E )\n", cursor);
        cursor++;
        if (E()) {
            if (*cursor == ')') {
                cursor++;
                return SUCCESS;
            } else
                return FAILED;
        } else
            return FAILED;
    } else if (*cursor == 'i') {
        printf("%-16s F -> i\n", cursor);
        cursor++;
        return SUCCESS;
    } else
        return FAILED;
}
