
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]){
	int i,j;

	if(argc!=3){
		return 1;
	} 
	if(argv[1]==0||argv[2]==0){
		return 2;
	}
	i=atol(argv[1]);
	j=atol(argv[2]);
	printf("%d\n", i/j);
	return 0;
}
