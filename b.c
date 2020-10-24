//Jaki Giggi
//10-19-2020
//prog b called within main.c

#include<stdio.h> 
#include<unistd.h> 
  
int main() 
{ 
    printf("I am b.c called by execv() in partA.c \n");
    printf("Exiting b.c now...\n");
    return 0; 
} 
