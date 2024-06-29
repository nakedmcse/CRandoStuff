//Stupid tricks with switch
#include<stdio.h>

int main(void) {
    char i = 2;

    // Cursed
    switch(i)
        if(0) case 0: printf("Zero\n");
        else if(0) case 1: printf("One\n");
        else if(0) case 2: printf("Two\n");
        else if(0) case 15: printf("Fifteen\n");
        else if(0) default: printf("Something Else\n");

    // Also cursed
    switch(i) {
        if(0) case 0: printf("Zero\n");
        if(0) case 1: printf("One\n");
        if(0) case 2: printf("Two\n");
        if(0) case 15: printf("Fifteen\n");
        if(0) default: printf("Something Else\n");
    }

    // Normal
    switch(i) {
        case 0: printf("Zero\n"); break;
        case 1: printf("One\n"); break;
        case 2: printf("Two\n"); break;
        case 15: printf("Fifteen\n"); break;
        default: printf("Something Else\n");
    }

    return 0;
}