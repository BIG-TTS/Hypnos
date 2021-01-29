#include <Windows.h>
#include <stdio.h>
#include <string.h>

void main(void)
{
	unsigned int x = 0;
	unsigned int y = 0;
	FILE *fptr;


	fptr = fopen("C:\\Users\\Marco Rouge\\Desktop\\Hypnos_Code_PC\\Test.txt", "w");

	fprintf(fptr, "x\ty\n");

	for(x = 0; x < 10; x++)
	{
		y = x * 2;
		
		fprintf(fptr, "%i", x);
		fprintf(fptr, "\t%i\n", y);
	}
	

	fclose(fptr);


	////How to write a file
	//fptr = fopen("C:\\Users\\Marco Rouge\\Desktop\\Hypnos_Code_PC\\Test.txt","w");
	//
	//if(fptr==NULL)
	//{
	//	printf("Error finding the file!");
	//	exit(1);
	//}

	//printf("\nText to be added: ");
	//scanf("%s",&text);
	//fprintf(fptr, "%s", text);
	//fclose(fptr);

	
	////How to read a file
	//fptr = fopen("C:\\Users\\Marco Rouge\\Desktop\\Hypnos_Code_PC\\Test.txt","r");

	//fscanf(fptr,"%s",text);
	//printf("\nThe written Text is: %s",text);
	//fclose(fptr);
	


}
