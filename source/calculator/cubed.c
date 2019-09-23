#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[]){
	int a;
	int answer;

	if(argc!=2){
		return 1;
	}

	a=atoi(argv[1]);
	answer=a*a*a;
	printf("%d\n", answer);
	return 0;
}
