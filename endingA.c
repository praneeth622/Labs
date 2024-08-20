#include<stdio.h>
#include<string.h>

int main(){
    char str[50];
    int i ;
    printf("Enter The string");
    scanf("%s",&str);
    int length = strlen(str);
    if((str[length-1]) == 'a'){
        printf("Valid String");
    }
    else{
        printf("Invalid String");
    }
}