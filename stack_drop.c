#include "defs.h"



void stack_drop(struct z_number **z_stack, struct z_number *result, int polar_flag, int drop_flag, int null_flag )
{

		/*************************************
		 *
		 *  DROP STACK
		 *
		 * **********************************
		 */

		int a;
		int i;
		i = SIZE-1;
		struct z_number *drop_temp; 
		if(drop_flag)
		{
			a = 1;
			/* a similar process to decide on free'ing the discarded "y" stack value - as long is it's not
			 * also allocated to levels above - c.f. the raise stack routine */
			drop_temp = z_stack[1];	
		//	printf("&z_stack[%d] = %p *z_stack[%d] = %p drop_temp = %p \n", a, &z_stack[a], a, z_stack[a], drop_temp);	
			while(a<i)
				{

					/* starting at level 1 (i.e. "y" stack) we copy the value down from the level above
					 * and do so until a reaches the top of the stack (i) */
					z_stack[a] = z_stack[a+1];
					++a;
				}
				
				/* then we assing the bottom "x" stack with the members of the results pointer */
				z_stack[0]->sign_zre[0] = result->sign_zre[0];
				z_stack[0]->sign_zim[0] = result->sign_zim[0];	
				z_stack[0]->abs_zre = result->abs_zre;
				z_stack[0]->abs_zim = result->abs_zim;
				z_stack[0]->polar = result->polar;

				/* the results pointer is now un-needed and can be free'd */
		//		printf("In drop.... freeing result %p\n", result);
				
		

				free(result);	
				
				/* we check the pointer from the old "y" stack level with the one above
				 * if it's the same, we can't free the old "Y" memory location
				 * because it's also the location of the levels upwards to the top of the stack
				 *
				 * if it's not the same as the level above we don't need it any more and it can be free'd.
				 *
				 * the new "y" level is (generally) different to the drop_temp pointer, as the new
				 * "y" level has been dropped down from above. That's why we need the drop_temp pointer
				 * to keep track of the (possibl) unused memory while we decide what to do */

		//		printf("can't free z_stack[1]  %p\n", drop_temp);
				if(drop_temp != z_stack[2])
				{
		//			printf("CAN free z_stack[1] \n");

					free(drop_temp);
					drop_temp = NULL;
				}	
		}
		else  /* if the DROP FLAG isn't set we check for NULL flag */
		{
			if(!null_flag)

			{
				z_stack[0]->sign_zre[0] = result->sign_zre[0];
				z_stack[0]->sign_zim[0] = result->sign_zim[0];	
				z_stack[0]->abs_zre = result->abs_zre;
				z_stack[0]->abs_zim = result->abs_zim;
				if (!polar_flag)
					z_stack[0]->polar = result->polar;
				else
					z_stack[0]->polar = 1;
				
				if(result != z_stack[0])
				{
					free(result);
				}
			}
		}
		
}
