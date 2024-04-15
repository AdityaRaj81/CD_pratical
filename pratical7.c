#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Token types
typedef enum {
    NUMBER,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    END
} TokenType;

// Token structure  
typedef struct {
    TokenType type;
    int value; // Only used for NUMBER type
} Token;

// LALR Parser
typedef struct {
    Token currentToken;
} Parser;

// Function prototypes
Token getNextToken();
void parse();
void error(const char *message);

// Global variables
char input[256]; // Adjust size as needed
int currentPos = 0;

// Main function
int main() {
    printf("Enter the Expression: ");
    scanf("%[^\n]", input); // Read input until newline character
    parse();
    printf("Parsing successful!\n");
    return 0;
}

// Get the next token from the input
Token getNextToken() {
    Token token;
    char currentChar = input[currentPos++];
    
    while (isspace(currentChar)) {
        currentChar = input[currentPos++];
    }
    
    if (isdigit(currentChar)) {
        ungetc(currentChar, stdin); // Unget the digit
        scanf("%d", &token.value);
        token.type = NUMBER;
    } else {
        switch (currentChar) {
            case '+':
                token.type = ADD;
                break;
            case '-':
                token.type = SUBTRACT;
                break;
            case '*':
                token.type = MULTIPLY;
                break;
            case '/':
                token.type = DIVIDE;
                break;
            case '(':
                token.type = LPAREN;
                break;
            case ')':
                token.type = RPAREN;
                break;
            case '\0':
                token.type = END;
                break;
            default:
                error("Invalid character");
        }
    }
    return token;
}

// Parse expressions
void parse() {
    Parser parser;
    parser.currentToken = getNextToken();
    
    while (parser.currentToken.type != END) {
        switch (parser.currentToken.type) {
            case ADD:
            case SUBTRACT:
                printf("Shift and reduce by E -> T\n");
                parser.currentToken = getNextToken();
                break;
            case MULTIPLY:
            case DIVIDE:
                printf("Shift and reduce by T -> F\n");
                parser.currentToken = getNextToken();
                break;
            case LPAREN:
                printf("Shift and reduce by F -> ( E )\n");
                parser.currentToken = getNextToken();
                break;
            case RPAREN:
                printf("Reduce by F -> ( E )\n");
                parser.currentToken = getNextToken();
                break;
            case NUMBER:
                printf("Shift and reduce by F -> NUMBER\n");
                parser.currentToken = getNextToken();
                break;
            default:
                error("Invalid token");
        }
    }
}

void error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(1);
}
