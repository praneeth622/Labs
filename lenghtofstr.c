//Length should be 2

#include<stdio.h>
#include<string.h>

int main(){
    int a;
    char str[50];
    printf("Enter the stirng \n");
    scanf("%s",str);
    int length =strlen(str);
    (length >2) ? printf("Invalid") : printf("Valid");
}