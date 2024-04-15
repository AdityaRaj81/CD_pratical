#include <stdio.h>
#include <ctype.h>

int main() {
    char line[150];
    int vowels, consonant, digit, space;
    // initialize all variables to 0
    vowels = consonant = digit = space = 0;
    // get full line of string input
    printf("Enter a line of string: ");
    fgets(line, sizeof(line), stdin);
    // loop through each character of the string
    for (int i = 0; line[i] != '\0'; ++i) {
        // convert character to lowercase
        char ch = tolower(line[i]);
        // check if the character is a vowel
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            // increment value of vowels by 1
            ++vowels;
        }
        // if it is not a vowel and if it is an alphabet, it is a consonant
        else if ((ch >= 'a' && ch <= 'z')) {
            ++consonant;
        }
        // check if the character is a digit
        else if (ch >= '0' && ch <= '9') {
            ++digit;
        }
        // check if the character is an empty space
        else if (ch == ' ') {
            ++space;
        }
    }
    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonant);
    printf("Digits: %d\n", digit);
    printf("White spaces: %d\n", space);
    return 0;
}
