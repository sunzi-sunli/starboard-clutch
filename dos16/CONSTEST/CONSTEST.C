#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[]){
        int i,j;
        char input;
        FILE* record;
        char output[80];
        
        if ( argc > 8 ){
                printf("too many arguments.\n");
                return 1;
        }
        for (i=1; i < argc; i++){
                if(i==1){
                        record=fopen(argv[1], "w");
                        if (!record){
                                printf("file creation failed\n");
                                return 2;
                        }
                } else {
                        strncat(output, "    ", 6);
                        strncat(output, argv[i], 10);
                }
        }
        strncat(output, "    \n", 6);
        fputs(output, record);
        printf("keywords written at beginning of file\n");
        printf("enter record text below:\n");
        do {
                input = getchar();
                if(input == '\n')
                        fputc('\n', record);
                fputc(input, record);
        } while ( input != '$' );
        
        fclose(record);
        return 0;
}
