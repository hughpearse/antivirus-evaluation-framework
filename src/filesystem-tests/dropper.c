/* Title: Write EICAR file to antivirus virtual file system
   Compile: wine gcc.exe filesystem-tests/dropper.c -o bin/dropper.exe
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
        FILE *fptr;
        fptr=fopen("eicar.com","w");

        if(fptr==NULL){
                printf("Error!");
                exit(1);
        }

        unsigned char s1[] = "X5O!P%@AP[4\\PZX54(P^)7CC)7}$";
        unsigned char split[] = "split EICAR on stack";
        unsigned char s2[] = "EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*";

        //write s1 and s2 to disk, completing the EICAR string
        fprintf(fptr,"%s",s1);
        fprintf(fptr,"%s",s2);
        fclose(fptr);
        return 0;
}
