#include<stdio.h>
#include<string.h>
#include <stdlib.h>

int main(void){
	unsigned char s1[] = "X5O!P%@AP[4\\PZX54(P^)7CC)7}$";
	unsigned char split[] = "split EICAR on stack";
	unsigned char s2[] = "EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*";
	
	int blocklen = strlen(s2)+strlen(s1);
	
	char * block = NULL;
	block = (char *) malloc(blocklen);
	memcpy(block, s1, strlen(s1));
	memcpy(&block[strlen(s1)], &s2, strlen(s2)+1);
	printf("%s\n", block);
	return 0;
}
