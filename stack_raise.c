#include "defs.h"

void stack_raise(struct z_number **p, float real, int real_null, float im, int im_null, int make_polar, int a, int i)

{
				struct z_number *temp;
				a=i;
				temp = p[SIZE-1];		/* prior to raising the stack we record the curent TOP pointer */ 
				while(a>0)
				{	
					p[a] = p[a-1];
					--a;								/* a counts down from "top of the stack" to 1 */
				}
				if(temp == p[SIZE-1])
					;		
				else
				{
					free(temp);
					temp = NULL;
				}
				if (real_null == 1 && im_null == 1)   
				{
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
				else      
				{
					if (real_null == 1)      
					{
						real = 0;
					}
					if (im_null == 1)
					{
						im = 0;
					}
				}
				p[0] = make_z(real, im, make_polar);
				++i;
				if(i > SIZE-1)
					i = SIZE - 1;
}

