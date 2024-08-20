//sre length ia multiplues of 3

#include<stdio.h>
#include<string.h>

int main(){
    char str[50] ;
    int i, length;
    printf("Enter the string\n");
    scanf("%s",str);
    length = strlen(str);
    if(length % 3 == 0){
        printf("valid String\n");
        return 0;
    }
    else{
        printf("Invalid String\n");
        return 1;
    }
}