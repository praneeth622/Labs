// take a string as input and it should satisfy some conditions 
// 1. string contain only a, b if not print str should contain only a,b
// 2. first letter should be a if now print not valid str
#include <stdio.h>
#include <string.h>

int main(){
    char a[50];
    int i;
    printf("Enter the string \n");
    scanf("%s",a);

    for(i=0;i<strlen(a);i++){
        if(a[i] != 'a'&& a[i]!='b'){
            printf("string Should contain only a , b \n");
            printf("%c",a[i]);
            return 1;
        }
    }
    if(a[0]=='a'){
        printf("Valid Sring \n");
    }
    else{
        printf("Invald Sring \n");
    }
}