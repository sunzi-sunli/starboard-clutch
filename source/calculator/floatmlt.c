
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]){
	float i,j;

	if(argc!=3){
		return 1;
	}
	i=atof(argv[1]);
	j=atof(argv[2]);
	printf("%f\n", i*j);
	return 0;
}
