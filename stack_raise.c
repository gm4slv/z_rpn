#include "defs.h"

void stack_raise(struct z_number **p, float real, int real_null, float im, int im_null, int make_polar)

{
				struct z_number *temp;

				int a = SIZE-1;
				
				
				/* prior to raising the stack we record the current TOP pointer */ 
				temp = p[SIZE-1];		
				
				
				/* a counts down from "top of the stack" to p[1] 
				 * this copies up each level from "y-stack (p[1])" upward
				 * into the level above.
				 * Stack [0] (x) is left as-is. This will be overwritten
				 * by the new value entered by the user.
				 *
				 * it the user pressed <enter><enter> then 
				 * the new value is taken to be the existing value */

				while(a>0)
				{	
					p[a] = p[a-1];
					--a;							
				}
				
				/* We decide if we can free the memory pointed to by what
				 * _had_ been the top level of the stack (the pointer
				 * is held in "temp").
				 * 
				 * it the new top level "p[SIZE-1]" is the same memory
				 * location as the old top level "temp"
				 * then we CAN't free it. This happens when
				 * the lower levels of the stack have been previously
				 * filled by copying down the top level during stack
				 * drops.
				 *
				 * if the level going down from the top is NOT the same (i.e
				 * it came UP from a stack raise) then we can free
				 * the memory location of the _old_ "stack top" (i.e. temp )
				 */
				
				if(temp != p[SIZE-1])
				{
					free(temp);
					temp = NULL;
				}
				
				
				/* This small routine handles the various
				 * cases where the user didn't enter 
				 * anything for real or im but pressed <enter>
				 * for one, or both, of them.
				 *
				 * if BOTH are "null" then we copy what's
				 * currently in "x-stack" into new "real" and "im"
				 * varables (and handle the signs)
				 * and then these real & im values will become
				 * our new entry, to be put into the
				 * bottom of the stack after it's raised
				 * - the effect is that the new entry is
				 *   the same as the previous X-stack and the stack
				 *   raises with the old x-stack value copied into
				 *   y.
				 */

		//		printf("before null detect real %.3f, im %.3f\n", real, im);

				if (real_null == 1 && im_null == 1)   
				{
		//			printf("real_null %d im_null %d\n", real_null, im_null);

					real = p[0]->abs_zre;
					if(p[0]->sign_zre[0] == '-')
					{
						real = -1*real;
					}
					im = p[0]->abs_zim;
					if(p[0]->sign_zim[0] == '-')
					{
						im = -1*im;
					}
					make_polar = p[0]->polar;
				}

				/* of only ONE of "real" or "im" are "null" then
				 * instead we assign zero to that part and make a new
				 * x-level with the entered value for the other part */

				else      
				{
		//			printf("real %.3f, real_null %d, im, %.3f im_null %d\n", real, real_null,im, im_null);
					if (real_null == 1)      
					{
						real = 0;
					}
					if (im_null == 1)
					{
						im = 0;
					}
				}
			
		//		printf("going to make_z() with real %.3f, im %.3f\n", real, im);

				/* now we assign the pointer help in x (z_stack[0] ) to 
				 * be the the newly created z_number entered by the user
				 */
				p[0] = make_z(real, im, make_polar);
				

}

