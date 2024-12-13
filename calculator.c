#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<stdbool.h>
#define MAX_EXPRESSION_LENGTH 100

// Validating the expression input about its syntactical corretcness.
bool checkValidityOfString(const char* expr) {
    int lengthOfExpression = strlen(expr); 
    int digitsCount= 0;
    int operatorsCount = 0;
    bool wasOperator=true;

    for (int i = 0; i < lengthOfExpression; i++) {
        // This loop is to count the number of digits and operators and update the same in variables digitsCount and operatorsCount.
        if (expr[i] == ' '){
            continue;
        } 

        if (isdigit(expr[i])) {
            digitsCount++;
            wasOperator = false;
        } 
        else if (strchr("+-*/", expr[i])) {
            
            if (wasOperator && expr[i] != '-') {// To consider negative numbers.
                return false; 
            }
            operatorsCount++;
            wasOperator = true;
        } else {
            return false; // Invalid characters found in the expression.
        }
    }

    return (digitsCount> operatorsCount); // Valid if only all the operators are between digits i.e we should hav more number of digits then operators. 
}
// This is to address the precedence of the operators i.e DMAS as per the requirements.
int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Performing the calculation for the given operands and a given operator.
int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("Error: Division by zero.\n");
                exit(1);
            }
            return a / b;
        default: return 0;
    }
}

// Evaluating  the mathematical expression.
int evaluateExpression(char* expr) {
    int digitsStack[MAX_EXPRESSION_LENGTH]; // Stack for digits.
    char operatorsStack[MAX_EXPRESSION_LENGTH];  // Stack for operators.
    int topOfDigitsStack = -1, topOfOperatorsStack = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == ' '){
            continue;
        }

        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (int)(expr[i] - '0'); // Getting the digitsvalue from the string expression.
                i++;
            }
            i--;
            digitsStack[++topOfDigitsStack] = num; // Pushing dgits to digits stack.
        } else if (strchr("+-*/", expr[i])) {
            // Processing operators based on precedence.
            while (topOfOperatorsStack >= 0 && precedence(operatorsStack[topOfOperatorsStack]) > precedence(expr[i])) {
                int num1 = digitsStack[topOfDigitsStack--];
                int num2 = digitsStack[topOfDigitsStack--];
                char operator = operatorsStack[topOfOperatorsStack--];
                digitsStack[++topOfDigitsStack] = calculate(num2, num1, operator);
            }
            operatorsStack[++topOfOperatorsStack] = expr[i]; // Pushing current operator to operators stack.
        }
    }

    // Evaluating remaining operators in the stack.
    while (topOfOperatorsStack >= 0) {
        int num1 = digitsStack[topOfDigitsStack--];
        int num2 = digitsStack[topOfDigitsStack--];
        char operator = operatorsStack[topOfOperatorsStack--];
        digitsStack[++topOfDigitsStack] = calculate(num2, num1, operator);
    }

    return digitsStack[topOfDigitsStack];
}

int main() {
    char expr[MAX_EXPRESSION_LENGTH];// To store the mathematical expression of the string data-type.

    printf("Enter the mathematical expression to evaulate: ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = 0; // Removing the newline character which would come when we press enter key.

    if (!checkValidityOfString(expr)) {
        printf("Error: Invalid expression.\n");
        return 1;
    }

    
    printf("\nResult: %d\n", evaluateExpression(expr));

    return 0;
}
