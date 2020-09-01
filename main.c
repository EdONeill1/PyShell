#include <stddef.h>
#include "shell-methods.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
    char input_str[128];
    
    while(1){
        timeDate();
        printf("# ");
        fgets(input_str, 128, stdin);
        printf("\n");
        parse(input_str);
      
    }
    
    return 0;
}