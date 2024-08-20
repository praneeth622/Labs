// String should cantain a
#include<stdio.h>
#include<string.h>

int main(){
    char str[50];
    int i;
    int a=0;
    printf("Enter A string \n");
    scanf("%s",str);
    for(i=0;i<strlen(str);i++){
        if(str[i]=='a'){
            a++;
        }
    }
    if(a>0){
        printf("It is valid String \n");
    }
}