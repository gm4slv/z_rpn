#include "defs.h"






void show_stack(struct z_number **p, struct z_number *last_x, struct z_number **mem)  /* takes a pointer-to-pointer - the z_stack variable is passed in
										 which is a pointer to the pointer members of the stack array
										 which themselves hold pointers to the z_number struct locations.*/
{
	char polar_char; 	/* display formatting - the polar char is either a space or a @ */
	int x;				/* for looping across the stack array */
	
//	printf("in show_stack() \n");

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


		if(x == 1)
			printf(". . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");

		/* print the members of the stack pointer's z_number struct  (we do down from top
		 * to ""y" in one block */
		if (p[x]->abs_zre > 10000 || (p[x]->abs_zre < 0.001 && p[x]->abs_zre != 0))
		{
			if(p[x]->abs_zim > 10000 || (p[x]->abs_zim < 0.001 && p[x]->abs_zim != 0))
			{
				printf(" %0d:\t\t%c%.3E\t%c %c%.3E j \n",
					x+1, 
					p[x]->sign_zre[0], p[x]->abs_zre,
					polar_char,
					p[x]->sign_zim[0], p[x]->abs_zim);
			}
			else
			{

				printf(" %0d:\t\t%c%.3E\t%c %c%9.3f j \n",
					x+1, 
					p[x]->sign_zre[0], p[x]->abs_zre,
					polar_char,
					p[x]->sign_zim[0], p[x]->abs_zim);
			}
		}
		else
		{
			if(p[x]->abs_zim > 10000 || ( p[x]->abs_zim < 0.001 && p[x]->abs_zim != 0) )
			{
				printf(" %0d:\t\t%c%9.3f\t%c %c%.3E j \n",
					x+1, 
					p[x]->sign_zre[0], p[x]->abs_zre,
					polar_char,
					p[x]->sign_zim[0], p[x]->abs_zim);
			}
			else
			{
				printf(" %0d:\t\t%c%9.3f\t%c %c%9.3f j \n",
					x+1, 
					p[x]->sign_zre[0], p[x]->abs_zre,
					polar_char,
					p[x]->sign_zim[0], p[x]->abs_zim);
			}
		}
	
	
	}


		/* then space down and do the bottom "X" stack level on a line to itself. This is where our
		 * main result is shown */

		if(last_x->polar == 1)
			polar_char = '@';
		else
			polar_char = ' ';

		printf("\n------------------------------------------------------\n");
		if (last_x->abs_zre > 10000 || (last_x->abs_zre < 0.001 && last_x->abs_zre != 0))
		{
			if(last_x->abs_zim > 10000 || (last_x->abs_zim < 0.001 && last_x->abs_zim != 0))
				{
					printf(" last x:\t%c%.3E\t%c %c%.3E j \n",
						last_x->sign_zre[0], last_x->abs_zre,
						polar_char,
					last_x->sign_zim[0], last_x->abs_zim);
			}
			else
			{

				printf(" last x:\t%c%.3E\t%c %c%9.3f j \n",
					last_x->sign_zre[0], last_x->abs_zre,
					polar_char,
					last_x->sign_zim[0], last_x->abs_zim);
			}
		}
		else
		{
			if(last_x->abs_zim > 10000 || ( last_x->abs_zim < 0.001 && last_x->abs_zim != 0) )
			{
				printf(" last x:\t%c%9.3f\t%c %c%.3E j \n",
					last_x->sign_zre[0], last_x->abs_zre,
					polar_char,
					last_x->sign_zim[0], last_x->abs_zim);
			}
			else
			{
				printf(" last x:\t%c%9.3f\t%c %c%9.3f j \n",
					last_x->sign_zre[0], last_x->abs_zre,
					polar_char,
					last_x->sign_zim[0], last_x->abs_zim);
			}
		}	
			
		printf("\n");
	//	printf("\n-------------------------------------------------------\n");
	
		for (x=SIZE-1;x>=0;--x)
		{	
			if(mem[x]->polar == 1)
				polar_char = '@';
			else
				polar_char = ' ';
				if (mem[x]->abs_zre > 10000 || (mem[x]->abs_zre < 0.001 && mem[x]->abs_zre != 0))
		{
			if(mem[x]->abs_zim > 10000 || (mem[x]->abs_zim < 0.001 && mem[x]->abs_zim != 0))
			{
				printf(" mem %0d:\t\t%c%.3E\t%c %c%.3E j \n",
					x+1, 
					mem[x]->sign_zre[0], mem[x]->abs_zre,
					polar_char,
					mem[x]->sign_zim[0], mem[x]->abs_zim);
			}
			else
			{

				printf(" mem %0d:\t\t%c%.3E\t%c %c%9.3f j \n",
					x+1, 
					mem[x]->sign_zre[0], mem[x]->abs_zre,
					polar_char,
					mem[x]->sign_zim[0], mem[x]->abs_zim);
			}
		}
		else
		{
			if(mem[x]->abs_zim > 10000 || ( mem[x]->abs_zim < 0.001 && mem[x]->abs_zim != 0) )
			{
				printf(" mem %0d:\t\t%c%9.3f\t%c %c%.3E j \n",
					x+1, 
					mem[x]->sign_zre[0], mem[x]->abs_zre,
					polar_char,
					mem[x]->sign_zim[0], mem[x]->abs_zim);
			}
			else
			{
				printf(" mem %0d:\t\t%c%9.3f\t%c %c%9.3f j \n",
					x+1, 
					mem[x]->sign_zre[0], mem[x]->abs_zre,
					polar_char,
					mem[x]->sign_zim[0], mem[x]->abs_zim);
			}
		}
		}
}


void help(void)
{
	printf("\n\n\tExperimental RPN calculator with complex stack\n\n");
	
	printf("\tUsage:\n");

	printf("\n\tAt the \"Enter Real:\" prompt type either:\n");
    printf("\tA command or begin a (complex) number entry with the Real part\n");
	printf("\tFor zero just press <enter> on its own\n\n");
	printf("\tAll numbers are treated as complex so then\n");
	printf("\tat the \"Enter Imaginary:\" prompt type the imaginary part <enter>\n");
	printf("\tFor zero just press <enter> on its own\n\n");
	printf("\tLeaving the entry blank and pressing <enter><enter> will copy the\n");
	printf("\tcurrent 'x' stack up into 'y' and raise the stack\n\n");

	printf("\tCommands are :  \n");
	printf("\t\tA)dd\t\ta\n");
	printf("\t\tS)ubtract\ts\n");
	printf("\t\tM)ultiply\tm\n");
	printf("\t\tD)ivide\t\td\n\n");
	printf("\t\tI)nverse 1/z\ti\n");
	printf("\t\tC)omplex Conj.\tc\n\n");
	
	printf("\t\t.)Dot product\t.\n");
	printf("\t\tx)Cross product\tx\n");
	printf("\t\tU)nit Vector\tu\n\n");
	printf("\t\tRect -> P)olar\tp\n");
	printf("\t\tPolar -> R)ect\tr\n\n");
	
	printf("\t\tRoll Down\t[\n");
	printf("\t\tSwap X<>Y\t]\n");
	printf("\t\tClear X\t\t<\n");
	printf("\t\tClear Stack\t>\n\n");

	printf("\t\tThis HELP\t#h\n");
	printf("\t\tQuit\t\t#q\n");



}


struct z_number *make_z(float in_re, float in_im, int p )
{

	struct z_number *z_ptr;

	char sign_re[1];
	char sign_im[1];

	/* use calloc() instead of malloc() : 
	 * to both allocate AND initiallize the full size of the struct. 
	 * 
	 * This is necessary because 16 bytes are allocated to the struct
	 * (the OS likes to work in 16 byte chunks) although we only use
	 * 14 bytes of user data:
	 *
	 * float real = 4
	 * float im   = 4
	 * int polar  = 4
	 * char sign real = 1
	 * char sign im   = 1
	 *
	 * using malloc() the remaining 2 bytes are allocated
	 * but don't get initiallized by the 14 bytes of our data.
	 * This only appears as a problem when we write the struct
	 * to a file (save state) - and valgrind complains of
	 * un-initialized memory. Everything WORKS - but it isn't 
	 * "right".
	 *
	 * By using calloc() we initiallize the full 16 bytes of the 
	 * struct, and then are free to only put in 14 bytes of user data
	 * - valgrind is happy and we aren't writing un-initiallized memory
	 *   contents to the save state file.
	 *
	 ******************************************************************
	 *
	 * Another way around this, using malloc(), is to increase the
	 * amount of user data we store in the struct by 2 bytes
	 * I tested this by adding a second character to the "sign" char
	 *
	 * in defs.h
	 *
	 * char sign_zre[2];
	 * char sign_zim[2]; 
	 *
	 *
	 * in the struct prototype, and then when making a new z_number
	 * I'd add a second (padding) character:
	 *
	 * in make_z()
	 *
	 * z_ptr->sign_zre[1] = 'f';
	 * z_ptr->sign_zim[1] = 'e';
	 *
	 * this meant that we had to assign these extra chars when reading the
	 * state file, even though they aren't of any use.
	 *
	 * In read_state()
	 *
	 * state[x]->sign_zre[1] = r_state.sign_zre[1];
	 * state[x]->sign_zim[1] = r_state.sign_zre[1];
	 *
	 * lastx->sign_zre[1] = r_state.sign_zre[1];
	 * lastx->sign_zim[1] = r_state.sign_zim[1];
	 *
	 * Simpler to just use calloc() in the first place. 
	 *
	 ***********************************************************************/

	z_ptr=(struct z_number *)calloc(1,sizeof(struct z_number));
	
	if ( z_ptr == NULL)
	{
		puts("calloc() error");
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

	z_ptr->sign_zim[0] = sign_im[0];
	z_ptr->abs_zre = in_re;
	z_ptr->abs_zim = in_im;
	z_ptr->polar = p;
	
	return (z_ptr);
}

