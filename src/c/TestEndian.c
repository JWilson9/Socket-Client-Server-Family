/***************************************/
/* Mark Deegan                         */
/* 3rd February 2015                   */
/***************************************/
/* simple test to check if this system */
/* uses little endian or big endian    */
/***************************************/

/* this is necessary to use the exit() function */
#include <stdlib.h>

/* this is necessary to use the printf function */
#include <stdio.h>

/* declare the main function */
int main(int argc, char **argv)
{
	/* a union in C can store variable of different types at the same location  */
	/* only one can be stored at a time, and the size of space reserved is the  */
	/* size of the largest element in the union declaration                     */
	/* in this case the reserved space can be referred to either as a short, s  */
	/* or as an array c, of the same size as a short                            */
	/* when we have it declared, reserve space for one such variable, called un */
	union {
		short s;
		char c[sizeof(short)];
	}un;
   
	/* set the vlaue stored at this location to hex 0101                        */
	/* this has the bit pattern of 0000:0001 0000:0010							*/
	/* the pattern is not important, only that the high-order byte is different */
	/* to the low-order byte                                                    */
	un.s = 0x0102;
   
	/* if the short data type is if size 2 bytes                                */
	if (sizeof(short) == 2) { /* start if sizeof(short) == 2                    */
   		/* if the low-order byte is    0000:0001								*/	
   		/* and the high-order byte is  0000:0010 then the bytes are stored      */
   		/* high before low meaning the system is big-endian                     */
      	if (un.c[0] == 1 && un.c[1] == 2)
      		printf("This system stores data as big-endian\n");
      		
      	/* else, if it was stored low before high, then it is low-endian        */
      	else if (un.c[0] == 2 && un.c[1] == 1)
         printf("This system stores data as little-endian\n");
    
    	/* else, we don't know what it is if it didn't store in that either of  */
    	/* the two above orders                                                 */     
		else
			printf("unknown\n");
	} /* end if sizeof(short) == 2                                              */ 
      
      /* else, if the sizeof(short) is not 2                                    */
      else {
      	printf("sizeof(short) = %ld\n", sizeof(short));
	}
      
	/* exit this program with the code 0 */   
	exit(0);
   
} /* end declaration of the main function */