
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]){
	int i,j;

	if(argc!=3){
		return 1;
	}
	i=atol(argv[1]);
	j=atol(argv[2]);
	printf("%d\n", i*j);
	return 0;
}
