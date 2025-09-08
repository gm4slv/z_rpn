#include "defs.h"



int main(void)
{

	int a=0;	/* for iterating across the stack for raising and dropping */
	int i;		/* points to the top level of the stack */    
	int x;		/* for general loop control: used in various places */	
	int real_null = 0;   /* to indicate an empty input string for controlling stack entry */
	int im_null = 0;

	struct z_number *z_stack[SIZE];		/* the complex stack = holds pointers to the complex numbers */

	struct z_number *last_x;			/* a pointer to the last-x */
	struct z_number *mem[SIZE];			/* a pointer to the last-x */

	struct z_number *result;			/* a pointer to the result of a calculation */
	struct z_number *temp;				/* a temporary pointer to a potential free-able memory, after a stack-raise */
	struct z_number *swap_temp;			/* a temporary pointer for the "swap x<>y" function */
	float real = 0;							/* input real value */
	float im = 0;							/* input imaginary value */
	
	char opcode = ' ';						/* the requested arithmetic function (+ - * / r p i c) */ 
	char opcode2 = ' ';						/* FUTURE USE */
	char command[2];					/* FUTURE USE */

	int drop_flag = 0;						/* a flag to control */
	int polar_flag = 0;					/* a flag indicating we're displaying a polar-format number, to control the
										   display of @ */

	int null_flag = 0;					/* a flag to do an NOP on the stack following an un-recognizable user entry 
										   or recall of last-x to the stack */
	
	char line[20];						/* a char-string to hold the user input prior to parsing */
	
	int make_polar = 0;						/* a flag to send to make_z() when the user enters an imaginary part prefixed by @ 
										   to indicate a polar format input */

    /* Initializing the stack
	 * fill with the correct number
	 * of 0 + 0j rectangular format
	 * complex numbers
	 *
	 * i keeps track ot the top of the stack
	 * and controls the raise / drop funtionality
	 *
	 * when the stack is full i will give the topmost
	 * stack index */

	for(i=0;i<SIZE;++i)
	{
		z_stack[i] = make_z(real, im, make_polar);
		mem[i] = make_z(real, im, make_polar);
	}

	if (i > SIZE-1)
		i = SIZE-1;
	
	last_x = make_lastx(z_stack[0]);
	
	/* READ SAVED STATE */

	read_state(z_stack, last_x);
	read_mem(mem);

	/* show_stack() is a function that takes the hase address of
	 * the z_stack and iterates across each element */
	
//	printf("to show_stack() before while loop starts \n");

	show_stack(z_stack, last_x, mem);
	

	/* start the endless process */
	while(1)
	{	
		/* the internal while() loop handles user input
		 * 
		 * if an "OPCODE" input is detected via prefix of #
		 * the while loop breaks and drops to the switch-case
		 * selection of the wanted operation */
		while(1)
		{	
//			printf("At start of entry while with make_polar = %d\n", make_polar);
			make_polar = 0;
//			printf("reset make_polar -> %d\n", make_polar);

			printf("\nEnter Real (or command) : ");
			fgets(line, sizeof(line), stdin);
/*			printf("strlen(line) = %d\n", strlen(line)); */
			line[strlen(line)-1] = '\0';
/*			printf("strlen(line) = %d\n", strlen(line)); */
			
			if(strlen(line) == 0)   /* we just pressed ENTER */
				real_null = 1;      /* set the flag to show this:
									   we can't test later for "real == '\n'
									   because a genuine entry of (float) 10
									   is read later as the \n character */
			else
				real_null = 0;

			if (line[0] > 58) /* # to enter opcode */
			{
				opcode = line[0];

				/* future use - second option for command input */
				opcode2 = line[1]-'0'; 
				
				break;
			}

			/* if the input wasn't prefixed by # (char 35) check it for 
			 * a valid numerical input 
			 *
			 * a blank line is taken to mean "no input" or "zero this part"
			 *
			 * the first char of the input line is tested to verify it's a 
			 * number or a narrow range of ASCII values to ensure a user entry
			 * of a negative number is read correctly (a minus sign is ASCII 45 (0x2d).
			 *
			 * */
			else
			{
				if (line[0] > 44 && line[0] < 58)
				{
					sscanf(line, "%f", &real);
			//		printf(" real entered %f\n", real);      
				}
				polar_flag = 0;	
			



				printf("Enter Imaginary : ");
				fgets(line, sizeof(line), stdin);
				line[strlen(line)-1] = '\0';
				
				if(strlen(line) == 0)   /* test for an empty "enter" */
					im_null = 1;
				else
					im_null = 0;

				if (line[0] > 44 && line[0] < 58)
				{
					sscanf(line, "%f", &im);
//					printf(" imag entered %f\n", im);   
				}

				
				/* if the imaginary entry is prefixed by @ (ASCII 64 (0x40)
				 * the user is requesting POLAR mode 
				 * the number (angle) is then read from the rest of the 
				 * line string - we shuffle the chars in the string along
				 * to the left by one
				 * */

				else if (line[0] == 64)  /* @ for polar argument */
				{
					for (x = 0;x<strlen(line);++x)
					{
						line[x] = line[x+1];
					}
					
					sscanf(line, "%f", &im);
					
					/* this is a POLAR format number - we send the "make_polar"
					 * along with real & imaginary to the make_z() function
					 */

					make_polar = 1;
				}
				else
				{
				;//	printf("Huh\n");
				//	real = 0;
				//	im = 0;
				//	make_polar = 0;
					//break;
				}

				
	//			printf(" imag entered %f\n", im);   
			
	//			printf("in main()... going to stack_raise() with real %.3f, im %.3f\n", real, im);	
				stack_raise(z_stack, real, real_null, im, im_null, make_polar);
		
				polar_flag = 0;	

				
	//			printf("going to show_stack() after imag entry \n");	
				
				
				show_stack(z_stack, last_x, mem);
		
			}
		}	    /* the WHILE() loop spins, looking for more user input */




		

		/* we've got the stack built and this is outside the inner while() loop - we get here
		 * from the break; statement in the input handling routine - when a 
		 * user command is entered (identified by a prefix of #
		 *
		 * the input routine sets "opcode" to the char AFTER the # prefix ( opcode = line[1] )
		 *
		 *
		 */
		
		   
		   
		polar_flag = 0;  /* default to RECT - -POLAR is set by the switch-case when a RECT->POLAR 
							operation is requested */

		null_flag = 0;	 /* default to "not NULL" - null_flag is SET by the switch-case leter on */
		
		/* each chosen operation will generally return a pointer to a
		 * new z_number. Most will also require the stack to drop
		 * - whereby z_stack[0] will hold the result, z_stack[1]
		 *   will be overwritten by the level above, and so on
		 *   until the top stack value is copied down to the level below.
		 *  
		 *   the mechanism is controlled by flags
		 *
		 *   drop_flag
		 *   polar_flag
		 *   null_flag
		 *
		 *  
		 */

		switch (opcode)
		{
			case '+':
			case 'a':
				free(last_x);
				last_x = make_lastx(z_stack[0]);
				result = add_z(z_stack[1], z_stack[0]);
				drop_flag = 1;
				break;
			case '-':
			case 's':
				free(last_x);
				last_x = make_lastx(z_stack[0]);
				result = subtract_z(z_stack[1], z_stack[0]);
				drop_flag = 1;
				break;
			case '*':
			case 'm':
				free(last_x);
				last_x = make_lastx(z_stack[0]);
				result = multiply_z(z_stack[1], z_stack[0]);
				drop_flag = 1;
				break;
			case '/':
			case 'd':
				free(last_x);
				last_x = make_lastx(z_stack[0]);
				result = divide2_z(z_stack[1], z_stack[0]);
				drop_flag = 1;
				break;
			case '<':
				result = clear_z();
				drop_flag = 0;
				break;
			case '>':
				for(x=0;x<SIZE;++x)
					{
						free(z_stack[x]);
						z_stack[x] = make_z(0, 0, 0);
					}
				drop_flag=0;
				null_flag=1;
				break;
			case '.':
				free(last_x);
				last_x = make_lastx(z_stack[0]);
				result = dot_product(z_stack[1], z_stack[0]);
				drop_flag = 1;
				break;
			case 'x':
				free(last_x);
				last_x = make_lastx(z_stack[0]);
				result = cross_product(z_stack[1], z_stack[0]);
				drop_flag = 1;
				break;
			case 'i':
				free(last_x);
				last_x = make_lastx(z_stack[0]);
				result = invert_z(z_stack[0]);
				drop_flag = 0;
				break;
			case 'c':
				result = conjugate_z(z_stack[0]);
				drop_flag = 0; 						/* we don't drop the stack, simply replace z_stack[0] with the
													  returned pointer to the location the complex-conjugate */
				break;
			
				
			case 'p':										/* rect -> polar */
															
				if(!z_stack[0]->polar)						/* if the z_number in stack[0] isn't already POLAR
															   then we send stack[0]'s pointer to the rect->polar()
															   funtion. the result is a pointer to the 
															   new z_number which holds the mag/angle (and its sign
															   along with a POLAR flag */
				{
					printf("Goint to rect_to_polar\n");
					result = rect_to_polar(z_stack[0]);
				}
				else
				{
					printf("Already polar! \n");
					result=z_stack[0];
				}			
													/* other wise, were' already POLAR and we copy the 
														   pointer of the existing z_number into the result
															   pointer.*/
				polar_flag = 1;								/* we set a flag to show we've got a POLAR number
															   which is used later to format the display */
				drop_flag = 0;								/* this is a simple conversion - no requirement to 
															   drop the stack */
				break;
			
			case 'r':										/* a similar procedure for the reverse process */
				if(z_stack[0]->polar)
					result = polar_to_rect(z_stack[0]);
				else
					result=z_stack[0];
				polar_flag = 0;
				drop_flag = 0;
				break;
			
			case ']':									/* Swap x<>y */
				swap_temp = z_stack[0];	
				z_stack[0] = z_stack[1];
				z_stack[1] = swap_temp;
				null_flag = 1;								/* NULL flag - do nothing to the stack */
				drop_flag = 0;
				break;	
			case '[':									/* ROLL DOWN */
				swap_temp = z_stack[0];
				for (i=0;i<SIZE-1;++i)
				{
					z_stack[i] = z_stack[i+1];
				}
					z_stack[SIZE-1] = swap_temp;
				
				null_flag = 1;								/* NULL flag - do nothing to the stack */
				drop_flag = 0;
				break;	
			case 'u':
				free(last_x);
				last_x = make_lastx(z_stack[0]);
				result = uvec_z(z_stack[0]);
				drop_flag = 0;
				break;

			case 'l':
				push_lastx(z_stack, last_x);
				drop_flag = 0;
				null_flag = 1;
				break;
			case 'j':
				if(opcode2 > 0 && opcode2 <= SIZE)
				{
					free(mem[opcode2-1]);
					mem[opcode2-1] = make_mem(z_stack[0], opcode2-1);
				}
				drop_flag = 0;
				null_flag = 1;
				break;
			case 'k':
				push_mem(z_stack, mem[opcode2-1]);
				drop_flag = 0;
				null_flag = 1;
				break;
			
			case 'h':										/* a rudimentary HELP feature...... */
				help();
				drop_flag = 0;
				null_flag = 1;								/* NULL flag - do nothing to the stack */
				break;
			case 'q':
			case 'Q':										/* clean up  - find which pointers are "unique" and not
															   copied into multiple stack levels
															   free them as approriate
																 */
				save_state(z_stack,last_x);
				save_mem(mem);

				for (x = SIZE-1;x>0;--x)
				{
					if(z_stack[x] != z_stack[x-1])
					{
				/*		printf("  Freeing stack[%d] ....%p \n", x, z_stack[x]); */
						free(z_stack[x]);
					}
				}
				/*
				printf("  Freeing stack[1] ....%p\n", z_stack[1]);
				free(z_stack[1]);
				*/
				
			/*	printf("  Freeing stack[0] ....%p\n", z_stack[0]); */
				free(z_stack[0]);
			/*	printf("....freeing last_x .... %p\n", last_x); */
				free(last_x);
				
				for (x = 0; x<SIZE; ++x)
				{
					free(mem[x]);
				}
			
				return(0);									/* Gracefully QUIT the program */

			default:
				drop_flag = 0;
				null_flag = 1;
		}                                              		/* the Switch - Case ends */



		/* we fall through to the rest of the code.....
		 * handling the stack as necessary after taking in user input, performing
		 * calculations and (in general) having a results pointer
		 * to the z_number struct who's contents need to be pointed to 
		 * at the bottom of the stack
		 * */


		/*************************************
		 *
		 *  DROP STACK
		 *
		 * **********************************
		 */

		stack_drop(z_stack, result, polar_flag, drop_flag, null_flag);
		
//		printf("going to show_stack() after stack_drop()\n");

		show_stack(z_stack, last_x, mem);

		}  		/* the INNER while() loop spins */
    return 0;
}
