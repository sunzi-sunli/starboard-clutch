#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]){
	int i;
	int counter;
	int answer=1;

	if(argc!=2)
		return 1;
	i=atoi(argv[1]);
	for(counter=1; counter!=(i+1); counter++)
		answer*=counter;
	printf("%d\n", answer);
	return 0;
}

