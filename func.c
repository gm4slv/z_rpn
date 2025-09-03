#include "defs.h"




void show_stack(struct z_number **p)  /* takes a pointer-to-pointer - the z_stack variable is passed in
										 which is a pointer to the pointer members of the stack array
										 which themselves hold pointers to the z_number struct locations.*/
{
	char polar_char; 	/* display formatting - the polar char is either a space or a @ */
	int x;				/* for looping across the stack array */

	polar_char = ' ';

	printf("\n\n==================...z rpn.....==================\n\n");

	for (x=SIZE-1;x>=1;--x)
	{
		if(p[x]->polar == 1) /* check the "polar" member of the z_stack pointer being handled
								and if set we assign @ as an identifier of POLAR format
								and if unset we print a space */
			polar_char = '@';
		else
			polar_char = ' ';
		
		/* print the members of the stack pointer's z_number struct  (we do down from top
		 * to ""y" in one block */
    	printf("z_stack[%0d]\t\t\t%c%.3f %c %c%.3f j \n", 
    /*	printf("z_stack[%0d]\t&z_stack %p\t*(&z_stack) %p\t%c%.3f %c %c%.3f j \n", */
		/*	x,&p[x],*(&p[x]), */
			x, 
			p[x]->sign_zre[0], p[x]->abs_zre,
			polar_char,
			p[x]->sign_zim[0], p[x]->abs_zim);
	}


		/* then space down and do the bottom "X" stack level on a line to itself. This is where our
		 * main result is shown */

		if(p[0]->polar == 1)
			polar_char = '@';
		else
			polar_char = ' ';
    		printf("\nz_stack[%0d]\t\t\t%c%.3f %c %c%.3f j \n", 
    	/*	printf("\nz_stack[%0d]\t&z_stack %p\t*(&z_stack) %p\t%c%.3f %c %c%.3f j \n", */
			x, 
		/*	x,&p[0],*(&p[0]), */
			p[0]->sign_zre[0], p[0]->abs_zre,
			polar_char,
			p[0]->sign_zim[0], p[0]->abs_zim);
}


void help(void)
{
	printf("\n\n\tExperimental RPN calculator with complex stack\n\n");
	
	printf("\tUsage:\n");

	printf("\n\tAt the \"Enter Real\" prompt type either:\n");
    printf("\tA command prefixed by the # sign\n");
	printf("\t\tor\n");
    printf("\ta number to put on the stack \n");

	printf("\n\tFor number entry type:\n");
    printf("\tthe number and press <Enter>\n");
	printf("\tFor zero just press Enter\n");
	printf("\tFor a complex number : \n");
	printf("\tat the \"Enter Imaginary:\" prompt enter the imaginary part.\n");
	printf("\tFor zero just press Enter\n\n");

	printf("\tCommands are prefix by #: \n");
	printf("\t\tAdd		#+\n");
	printf("\t\tSubtract	#-\n");
	printf("\t\tMultiply	#*\n");
	printf("\t\tDivide		#/\n\n");
	printf("\t\tInverse 1/z		#i\n");
	printf("\t\tComplex Conjugate	#c\n");
	printf("\t\tRect -> Polar		#p\n");
	printf("\t\tPolar -> Rect		#r\n\n");
	printf("\t\tRoll Down			#x\n");
	printf("\t\tSwap X<>Y			#z\n\n");

	printf("\tThis HELP		#h\n");
	printf("\tQuit			#q\n");



}


struct z_number *make_z(float in_re, float in_im, int p)
{

	struct z_number *z_ptr;

	char sign_re[1];
	char sign_im[1];

	z_ptr=(struct z_number *)malloc(sizeof(struct z_number) * 1);
	
	if ( z_ptr == NULL)
	{
		puts("Malloc() error");
		exit(1);
	}
	

	/* we store the absolute value of real & imaginary along with the 
	 * char representing the sign. */
	if (in_re < 0)
	{
		sign_re[0] = '-';
		in_re = in_re * -1;
	}
	else
	{
		sign_re[0] = ' ';
		
	}

	if (in_im < 0)
	{
		sign_im[0] = '-';
		in_im = in_im * -1;
	}
	else
	{
		sign_im[0] = '+';
	
	}
	
	/* we are p assing the struct members using pointer notation
	 * with the values and char (for sign) before returning the
	 * pointer for the location of the filled-in-with-data struct */

	z_ptr->sign_zre[0] = sign_re[0];
	/*
	if(!p)
		z_ptr->sign_zim[0] = sign_im[0];
	else
		z_ptr->sign_zim[0] = '@';
	*/

	z_ptr->sign_zim[0] = sign_im[0];
	z_ptr->abs_zre = in_re;
	z_ptr->abs_zim = in_im;
	z_ptr->polar = p;
	
	return (z_ptr);
}

