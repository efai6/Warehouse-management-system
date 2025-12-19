#include <stdio.h>
#include <string.h>
int Object_code_check(char* code){
    int i;
    if (strlen(code)!=5){
        return 1;
    }
    for (i = 0;i<2;i++){
        if(code[i] >= 'A'&& code[i]<= 'Z'){
        }
        else{
            return 1;
        }
    }
    for (i=2; i<5; i++){
        int c_int = code[i] - '0';
        if (c_int >=0 && c_int<=9){
        }
        else{
            return 1;
        }
    }
    return 0;
}