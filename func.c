#include "defs.h"




void show_stack(struct z_number **p)  /* takes a pointer-to-pointer - the z_stack variable is passed in
										 which is a pointer to the pointer members of the stack array
										 which themselves hold pointers to the z_number struct locations.*/
{
	char polar_char; 	/* display formatting - the polar char is either a space or a @ */
	int x;				/* for looping across the stack array */

	polar_char = ' ';

	printf("\n\n==================...z rpn.%s....==================\n\n", VERSION);

	for (x=SIZE-1;x>=0;--x)
	{

		if(p[x]->polar == 1) /* check the "polar" member of the z_stack pointer being handled
								and if set we assign @ as an identifier of POLAR format
								and if unset we print a space */
			polar_char = '@';
		else
			polar_char = ' ';
		
		/* print the members of the stack pointer's z_number struct  (we do down from top
		 * to ""y" in one block */
		
		if( x == 1)
			printf("\n");


    	printf(" z[%0d]\t\t\t%c%.3f %c %c%.3f j \n", 
    /*	printf("z_stack[%0d]\t&z_stack %p\t*(&z_stack) %p\t%c%.3f %c %c%.3f j \n", */
		/*	x,&p[x],*(&p[x]), */
			x, 
			p[x]->sign_zre[0], p[x]->abs_zre,
			polar_char,
			p[x]->sign_zim[0], p[x]->abs_zim);
	}


}


void help(void)
{
	printf("\n\n\tExperimental RPN calculator with complex stack\n\n");
	
	printf("\tUsage:\n");

	printf("\n\tAt the \"Enter Real\" prompt type either:\n");
    printf("\tA command prefixed by the # sign\n");
	printf("\t\tor\n");
    printf("\tbegin a number entry with real part <enter> imaginary part <enter> \n");

	printf("\n\tFor number entry type:\n");
    printf("\tthe number and press <enter>\n");
	printf("\tFor zero just press <enter>\n\n");
	printf("\tAll numbers are treated as complex\n");
	printf("\tat the \"Enter Imaginary:\" prompt enter the imaginary part.\n");
	printf("\tFor zero just press <enter>\n\n");

	printf("\tCommands are prefix by #: \n");
	printf("\t\tAdd\t\t#a\n");
	printf("\t\tSubtract\t#s\n");
	printf("\t\tMultiply\t#m\n");
	printf("\t\tDivide\t\t#d\n\n");
	printf("\t\tInverse 1/z\t#i\n");
	printf("\t\tComplex Conj.\t#c\n\n");
	printf("\t\tDot product\t#.\n");
	printf("\t\tCross product\t#x\n");
	printf("\t\tUnit Vector\t#u\n\n");
	printf("\t\tRect -> Polar\t#p\n");
	printf("\t\tPolar -> Rect\t#r\n\n");
	printf("\t\tRoll Down\t#[\n");
	printf("\t\tSwap X<>Y\t#]\n\n");

	printf("\t\tThis HELP\t#h\n");
	printf("\t\tQuit\t\t#q\n");



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

