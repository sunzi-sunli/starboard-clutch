#include <string.h>
#include <stdio.h>

int
main(int argc, char *argv[]){
        int i, j;
        char *p;
        FILE *fp;
        char input[80];

        if (argc != 3){
                printf("FETCH [search term] [filename]\n");
                return 1;
        }
        fp=fopen(argv[2], "r");
        if(!fp){
                printf("File not found.\n");
                return 2;
        }
        fread(input, 1, 80, fp);
        p=strstr(input, argv[1]);
        if(p){
                printf("keyword found!\n");
        }
        fclose(fp);
        return 0;
}
