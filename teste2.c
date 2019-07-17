#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_MAX_SIZE 26

typedef struct stackstruct{
    char wagons[STACK_MAX_SIZE];
    int top;
} stackstruct;

void Push(stackstruct*s, char character){
        s->top++;
        s->wagons[s->top] = character;
}

char Pop(stackstruct*s){
    char exit;

    if(s->top>=0){
        s->wagons[s->top] = exit;
        s->top--;
    } else{
        return '0';
    }

    return exit;
}

int main (){

    while(1){
        int total=0;

        scanf("%d%*c", &total);

        if(total==0){
            break;
        }

        int size = (2*total)-1;
        char input[size];
        char output[size];

        scanf("%[^\n]%*c", input);
        scanf("%[^\n]c", output);


        { //apaga os espaços das strings
        int i = 0, position = 0;
        for ( i, position; i < size; i++, position++) {
            if (input[position] == ' ') {
                position++;
            }
            input[i] = input[position];
        }
        i = 0, position = 0;
        for ( i, position; i < size; i++, position++) {
            if (output[position] == ' ') {
                position++;
            }
            output[i] = output[position];
        }
        }

        //printf("%s\n", input);
        //printf("%s\n", output);

        stackstruct stack;

        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){

                if(input[j]!=output[i]){
                    Push(&stack, input[j]);
                    printf("I");
                } else{
                    Pop(&stack);
                    printf("R");
                }

            }
        }


    }
    return 0;
}
