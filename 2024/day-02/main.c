#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void remove_chars_and_shift(char *data, int index, int count) {
    int len = strlen(data);
    for (int i = index; i + count <= len; i++) {
        data[i] = data[i + count];
    }
}

void is_safe(char * data, int * count, int unsafe){
    int i = 0;
    int in_or_de = 0;
    while (1){
        int num1 = 0;
        if (data[i + 1] == '\n' || data[i + 2] == '\n') break;
        if (data[i + 1] != ' ' && data[i + 1] != '\n'){
            num1 = (data[i] - '0') * 10 + (data[i + 1] - '0');
            i += 3; 
        } else {
            num1 = data[i] - '0';
            i += 2;
        }
        int num2 = 0;
        if (data[i + 1] != ' ' && data[i + 1] != '\n'){
            num2 = (data[i] - '0') * 10 + (data[i + 1] - '0'); 
        } else {
            num2 = data[i] - '0';
        }
        int sum = 0;
        if (num1 > num2){
            sum = num1 - num2;
            if (in_or_de == 0) in_or_de = 1;
            if (in_or_de == 2){
                if (num1 > 9 && num2 > 9 && unsafe == 0){
                    remove_chars_and_shift(data, i - 3, 3);
                    return is_safe(data, count, 1);
                }
                if ((num1 < 10 && num1 > 0) && (num2 < 10 && num2 > 0) && unsafe == 0){
                    remove_chars_and_shift(data, i - 2, 2);
                    return is_safe(data, count, 1);
                }
                return;
            }
            if (sum > 3){
                if (num1 > 9 && num2 > 9 && unsafe == 0){
                    remove_chars_and_shift(data, i - 3, 3);
                    return is_safe(data, count, 1);
                }
                if ((num1 < 10 && num1 > 0) && (num2 < 10 && num2 > 0) && unsafe == 0){
                    remove_chars_and_shift(data, i - 2, 2);
                    return is_safe(data, count, 1);
                }
                return;
            }
        } 
        if (num1 < num2){
            sum = num2 - num1;
            if (in_or_de == 0) in_or_de = 2;
            if (in_or_de == 1){
                if (num1 > 9 && num2 > 9 && unsafe == 0){
                    remove_chars_and_shift(data, i - 3, 3);
                    return is_safe(data, count, 1);
                }
                if ((num1 < 10 && num1 > 0) && (num2 < 10 && num2 > 0) && unsafe == 0){
                    remove_chars_and_shift(data, i - 2, 2);
                    return is_safe(data, count, 1);
                }
                return;
            }
            if (sum > 3){
                if (num1 > 9 && num2 > 9 && unsafe == 0){
                    remove_chars_and_shift(data, i - 3, 3);
                    return is_safe(data, count, 1);
                }
                if ((num1 < 10 && num1 > 0) && (num2 < 10 && num2 > 0) && unsafe == 0){
                    remove_chars_and_shift(data, i - 2, 2);
                    return is_safe(data, count, 1);
                }
                return;
            }
        }
        if (num1 == num2){
            if (num1 > 9 && num2 > 9 && unsafe == 0){
                    remove_chars_and_shift(data, i - 3, 3);
                    return is_safe(data, count, 1);
                }
                if ((num1 < 10 && num1 > 0) && (num2 < 10 && num2 > 0) && unsafe == 0){
                    remove_chars_and_shift(data, i - 2, 2);
                    return is_safe(data, count, 1);
                }
                return;
        }
    }
    (*count)++;
    printf("%d\n", *count);
}

int main(){
    int count = 0;
    while (1){
        char * data = NULL;
        size_t len = 0;
        int ret = getline(&data, &len, stdin);
        if (ret == EOF) break;
        is_safe(data, &count, 0);
        free(data);
    }
    printf("count of safe: %d\n", count);
    return 0;
}