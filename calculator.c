#include <stdio.h>
#include "pico/stdlib.h"
#include <stdlib.h>  


const uint ROWS[] = {2, 3, 4, 5};  
const uint COLS[] = {6, 7, 8, 9};  

// Keypad layout
const char KEYPAD[4][4] = {
    {'1', '2', '3', 'A'},  
    {'4', '5', '6', 'B'},  
    {'7', '8', '9', 'C'},  
    {'*', '0', '#', 'D'}   
};


char scan_keypad() {
    for (int col = 0; col < 4; col++) {
        gpio_put(COLS[col], 0);  

        for (int row = 0; row < 4; row++) {
            if (gpio_get(ROWS[row]) == 0) {  
                gpio_put(COLS[col], 1);  
                return KEYPAD[row][col];  
            }
        }

        gpio_put(COLS[col], 1); 

    return '\0';  
}


int perform_operation(int operand1, int operand2, char operator) {
    switch (operator) {
        case 'A': return operand1 + operand2;  
        case 'B': return operand1 - operand2;  
        case 'C': return operand1 * operand2;  
        case 'D': return (operand2 != 0) ? operand1 / operand2 : 0;  
        default: return 0;
    }
}

int main() {
    stdio_init_all();

  
    for (int i = 0; i < 4; i++) {
        gpio_init(ROWS[i]);
        gpio_set_dir(ROWS[i], GPIO_IN);
        gpio_pull_up(ROWS[i]);
    }

    
    for (int i = 0; i < 4; i++) {
        gpio_init(COLS[i]);
        gpio_set_dir(COLS[i], GPIO_OUT);
        gpio_put(COLS[i], 1);
    }

    char input[20];    
    int idx = 0;       
    char key;          
    int operand1 = 0;  
    int operand2 = 0;  
    char operator = 0; 

    printf("Simple Calculator:\n");

    while (1) {
        key = scan_keypad();  

        if (key != '\0') {  
            if (key == '*') {  
                idx = 0;
                operator = 0;
                printf("\nCleared\n");
            } else if (key == '#') { 
                input[idx] = '\0';  
                operand2 = atoi(input);  

                int result = perform_operation(operand1, operand2, operator);  
                printf("\nResult: %d\n", result);  
                idx = 0; 
                operator = 0;  
            } else if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {  
                input[idx] = '\0';  
                operand1 = atoi(input);  
                operator = key;  
                idx = 0;  
                printf(" %c ", key);  
            } else {  
                input[idx++] = key;  
                printf("%c", key);  
            }

            sleep_ms(300);  
        }
    }

    return 0;
}
