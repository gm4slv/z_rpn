#include "defs.h"


struct z_number *multiply_z(struct z_number *z1, struct z_number *z2)
{
	struct z_number *result_ptr;
	struct z_number *ptr;
	float result_re;
	float result_im;
	float z1_re; /*  these are the signed real & imaginary parts    */
	float z1_im; /*  made by reference to the z->sign... char       */
	float z2_re; /*  multiplying the z->abs_xxx by -1 when the      */
	float z2_im; /*  sign member character  is '-'                  */
	int polar_in = 0;
	
	/*  make the signed version of real & imaginary parts
         *  of z1 and z1 to allow the calculation to be made */
	
	
	if(z1->polar)
	{
		z1 = polar_to_rect(z1);
		polar_in = 1;
	

        /* real parts */
        if( z1->sign_zre[0] == '-')
        {
                z1_re = z1->abs_zre * -1;
        }
        else
        {
                z1_re = z1->abs_zre;
        }


        if( z1->sign_zim[0] == '-')
        {
                z1_im = z1->abs_zim * -1;
        }
        else
        {
                z1_im = z1->abs_zim;
        }

		free(z1);

	}
	else
	{
        /* real parts */
        if( z1->sign_zre[0] == '-')
        {
                z1_re = z1->abs_zre * -1;
        }
        else
        {
                z1_re = z1->abs_zre;
        }


        if( z1->sign_zim[0] == '-')
        {
                z1_im = z1->abs_zim * -1;
        }
        else
        {
                z1_im = z1->abs_zim;
        }

	}

/******************************************************/


	if(z2->polar)
	{
		z2 = polar_to_rect(z2);
		polar_in = 1;
	

        if( z2->sign_zre[0] == '-')
        {
                z2_re = z2->abs_zre * -1;
        }
        else
        {
                z2_re = z2->abs_zre;
        }

        /* Imaginary parts */

        if( z2->sign_zim[0] == '-')
        {
                z2_im = z2->abs_zim * -1;
        }
        else
        {
                z2_im = z2->abs_zim;
        }
		free(z2);

	}
	else
	{
        if( z2->sign_zre[0] == '-')
        {
                z2_re = z2->abs_zre * -1;
        }
        else
        {
                z2_re = z2->abs_zre;
        }

        /* Imaginary parts */

        if( z2->sign_zim[0] == '-')
        {
                z2_im = z2->abs_zim * -1;
        }
        else
        {
                z2_im = z2->abs_zim;
        }
	}

 /* calculate the real and imaginary result */
        result_re = ((z1_re * z2_re) - (z1_im * z2_im));
        result_im = ((z1_re * z2_im) + (z1_im * z2_re));

        /* send the real and imaginary results to 
         * make_z() and assign the returned pointer
         * to the result struct */

		if(!polar_in)
        	result_ptr = make_z(result_re, result_im, 0);
		else
		{
			ptr = make_z(result_re, result_im,0);
			result_ptr = rect_to_polar(ptr);
			free(ptr);
		}
	
	return(result_ptr);
}

