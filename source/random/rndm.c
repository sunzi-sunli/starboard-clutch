#include <stdio.h>
#include <stdlib.h>

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876

float ran0(long *idum)
{
	long k;
	float ans;
	
	*idum ^= MASK;
	k=(*idum)/IQ;
	*idum=IA*(*idum-k*IQ)-IR*k;
	if (*idum < 0) *idum += IM;
	ans=AM*(*idum);
	*idum ^= MASK;
	return ans;
}

int
main(int argc, char *argv[]){
	long int seed=100, ctr;
	float num;

	if(argc != 2)
		return 1;
	
	seed=atoi(argv[1]);

	for(ctr=0; ctr<20; ctr++){
		num=ran0(&seed);
		printf("%f\n", num);
	}
	
	return 0;
}
