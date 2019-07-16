#include <stdio.h>
#include <stdlib.h>
#include <string.h>




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

    }
    return 0;
}
