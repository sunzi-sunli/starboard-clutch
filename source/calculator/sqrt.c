#include <stdio.h>
#include <math.h>

int
main(int argc, char *argv[]){
	float i;

	if(argc!= 2)
		return 1;
	i=sqrt(atof(argv[1]));
	printf("%f\n", i);
	return 0;
}

