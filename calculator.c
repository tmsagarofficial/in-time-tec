#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_EXPRESSION_LENGTH 100


int isitdigit(char c);
int checkValidityOfString(const char *expr);
int calculator(char *expr);

int isitdigit(char c){
    return c >= '0' && c <= '9';
}

int checkValidityOfString(const char* expr) {
    int lengthOfExpression = strlen(expr); 
    int digitsCount = 0;
    int operatorsCount = 0;
    int wasOperator = 1;
    int consecutiveNegatives = 0;

    for (int i = 0; i < lengthOfExpression; i++) {
        if (expr[i] == ' ') {
            // Check if space is improperly placed between digits.
            if (i > 0 && isitdigit(expr[i - 1]) && isitdigit(expr[i + 1])) {
                return 0; // Invalid if space is splitting digits.
            }
            continue;
        }
        if (isitdigit(expr[i])) {
            digitsCount++;
            while (i + 1 < lengthOfExpression && isitdigit(expr[i + 1])) {
                i++;
                digitsCount++;
            }
            wasOperator = 0;
            consecutiveNegatives = 0;
        } 
        else if (strchr("+-*/", expr[i])) {
            if (expr[i] == '-') {
                if (wasOperator) {
                    consecutiveNegatives++;
                    continue;
                }
            } else if (wasOperator) {
                return 0;
            }
            operatorsCount++;
            wasOperator = 1;
        } else {
            return 0; 
        }
    }

    return (digitsCount > operatorsCount); // Valid if more digits than operators.
}


int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}




int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("Error: Division by zero.\n");
                return 1;
            }
            return a / b;
        default: return 0;
    }
}


int evaluateExpression(char* expr) {
    int digitsStack[MAX_EXPRESSION_LENGTH]; 
    char operatorsStack[MAX_EXPRESSION_LENGTH]; 
    int topOfDigitsStack = -1, topOfOperatorsStack = -1;
    int consecutiveNegatives = 0;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == ' '){
            continue;
        }
        if (isitdigit(expr[i])) {
            int num = 0;
            while (isitdigit(expr[i])) {
                num = num * 10 + (int)(expr[i] - '0'); 
                i++;
            }
            i--;
            if(consecutiveNegatives % 2 == 1){
                num = -num;
            }
            consecutiveNegatives = 0;
            digitsStack[++topOfDigitsStack] = num; 
        } else if (strchr("+-*/", expr[i])) {
            // Processing operators based on precedence.
            while (topOfOperatorsStack >= 0 && precedence(operatorsStack[topOfOperatorsStack]) >= precedence(expr[i])){
                int num1 = digitsStack[topOfDigitsStack--];
                int num2 = digitsStack[topOfDigitsStack--];
                char op = operatorsStack[topOfOperatorsStack--];
                digitsStack[++topOfDigitsStack] = calculate(num2, num1, op);
            }
            operatorsStack[++topOfOperatorsStack] = expr[i];
            consecutiveNegatives = 0;
        }
    }

    // Evaluating remaining operators in the stack.
    while (topOfOperatorsStack >= 0) {
        int num1 = digitsStack[topOfDigitsStack--];
        int num2 = digitsStack[topOfDigitsStack--];
        char op = operatorsStack[topOfOperatorsStack--];
        digitsStack[++topOfDigitsStack] = calculate(num2, num1, op);
    }

    return digitsStack[topOfDigitsStack];
}

int main() {
    char expr[MAX_EXPRESSION_LENGTH];
    printf("Enter the mathematical expression to evaulate: ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = 0; 

    if (!checkValidityOfString(expr)) {
        printf("Error: Invalid expression.\n");
        goto end;
    }
    printf("\nResult: %d\n", evaluateExpression(expr));
    end:
        return 0;
}