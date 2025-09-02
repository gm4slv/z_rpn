#include "defs.h"

const float PI = 3.14159265359;

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


/* this is a simplified divide funtion that uses the existing
 * invert_z and multiply_z functions 
 *
 * this might become the default divide_z() function  */

struct z_number *divide2_z(struct z_number *z1, struct z_number *z2)
{
	struct z_number *result_ptr;
	struct z_number *z3;
	int polar_in = 0;	
	if(z1->polar)
	{
		z1 = polar_to_rect(z1);
		polar_in = 1;
	}
	if(z2->polar)
	{
		z2 = polar_to_rect(z2);
		polar_in = 1;
	}

	z3 = invert_z(z2);
	
	result_ptr = multiply_z(z1,z3);

	if(polar_in)
		result_ptr = rect_to_polar(result_ptr);

	free(z3);

	return(result_ptr);
}



struct z_number *invert_z(struct z_number *z1)
{
	struct z_number *result_ptr;
	struct z_number *ptr;
	float result_re;
	float result_im;
	float z1_re; /*  these are the signed real & imaginary parts    */
	float z1_im; /*  made by reference to the z->sign... char       */
	int polar_in = 0;

	if(z1->polar)
	{
		z1 = polar_to_rect(z1);

		polar_in = 1;

	
	/*  make the signed version of real & imaginary parts
         *  of z1 and z1 to allow the calculation to be made */

        /* real parts */
        if( z1->sign_zre[0] == '-')
        {
                z1_re = z1->abs_zre * -1;
        }
        else
        {
                z1_re = z1->abs_zre;
        }


        /* Imaginary parts */

        if( z1->sign_zim[0] == '-')
        {
                z1_im = z1->abs_zim;
        }
        else
        {
                z1_im = z1->abs_zim * -1;
        }
		
		free(z1);
	}
	else
	{
	/*  make the signed version of real & imaginary parts
         *  of z1 and z1 to allow the calculation to be made */

        /* real parts */
        if( z1->sign_zre[0] == '-')
        {
                z1_re = z1->abs_zre * -1;
        }
        else
        {
                z1_re = z1->abs_zre;
        }


        /* Imaginary parts */

        if( z1->sign_zim[0] == '-')
        {
                z1_im = z1->abs_zim;
        }
        else
        {
                z1_im = z1->abs_zim * -1;
        }
		
	}
		
 /* calculate the real and imaginary result */
        result_re = (z1_re / (z1_re * z1_re + z1_im * z1_im) ) ;
        result_im = ( z1_im /( z1_re * z1_re + z1_im * z1_im)) ;

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

struct z_number *rect_to_polar(struct z_number *z1)
{
	struct z_number *result_ptr;
	float result_re;
	float result_im;
	float z1_re; /*  these are the signed real & imaginary parts    */
	float z1_im; /*  made by reference to the z->sign... char       */
	
	
	/*  make the signed version of real & imaginary parts
         *  of z1 and z1 to allow the calculation to be made */

        /* real parts */
        if( z1->sign_zre[0] == '-')
        {
                z1_re = z1->abs_zre * -1;
        }
        else
        {
                z1_re = z1->abs_zre;
        }


        /* Imaginary parts */

        if( z1->sign_zim[0] == '-')
        {
                z1_im = z1->abs_zim * -1;
        }
        else
        {
                z1_im = z1->abs_zim;
        }


        result_re = sqrt((z1_re * z1_re ) + (z1_im * z1_im)) ;
        result_im = 180 * atan(z1_im / z1_re) / PI;
		
		/* work out the quadrant */

		if ( z1_re >= 0 && z1_im < 0 )		/* 4th quadrant */
		{
			result_im = result_im ;
		}
		else if  ( z1_re < 0 && z1_im < 0 )	/* 3rd quadrant */
		{
			result_im = result_im - 180;
		}
		else if( z1_re < 0 && z1_im >= 0) 	/* 2nd quadrant */
		{
			result_im = result_im + 180;
		}
		else								/* 1st quadrant */
		{
		;
		}


        /* send the real and imaginary results to 
         * make_z() and assign the returned pointer
         * to the result struct */
        result_ptr = make_z(result_re, result_im, 1);

	return(result_ptr);
}


struct z_number *polar_to_rect(struct z_number *z1)
{
	struct z_number *result_ptr;
	float angle_rad;
	float result_re;
	float result_im;
	float z1_re; /*  these are the signed real & imaginary parts    */
	float z1_im; /*  made by reference to the z->sign... char       */
	
	
	/*  make the signed version of real & imaginary parts
         *  of z1 and z1 to allow the calculation to be made */

        /* real parts */
        if( z1->sign_zre[0] == '-')
        {
                z1_re = z1->abs_zre * -1;
        }
        else
        {
                z1_re = z1->abs_zre;
        }


        /* Imaginary parts */

        if( z1->sign_zim[0] == '-')
        {
                z1_im = z1->abs_zim * -1;
        }
        else
        {
                z1_im = z1->abs_zim;
        }

		
		angle_rad = 2*PI * z1_im / 360;

		result_re = z1_re * cos(angle_rad);
        result_im = z1_re * sin(angle_rad);

        /* send the real and imaginary results to 
         * make_z() and assign the returned pointer
         * to the result struct */
        result_ptr = make_z(result_re, result_im, 0);
		printf("In polar_to_rect() returning %p \n", result_ptr);

	return(result_ptr);
}

struct z_number *conjugate_z(struct z_number *z1)
{
	struct z_number *result_ptr;
	struct z_number *ptr;
	float result_re;
	float result_im;
	float z1_re; /*  these are the signed real & imaginary parts    */
	float z1_im; /*  made by reference to the z->sign... char       */
	int polar_in = 0;	
	
	if(z1->polar)
	{
		z1 = polar_to_rect(z1);
		polar_in = 1;
	
	
	
	/*  make the signed version of real & imaginary parts
         *  of z1 and z1 to allow the calculation to be made */

        /* real parts */
        if( z1->sign_zre[0] == '-')
        {
                z1_re = z1->abs_zre * -1;
        }
        else
        {
                z1_re = z1->abs_zre;
        }


        /* Imaginary parts */

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
	/*  make the signed version of real & imaginary parts
         *  of z1 and z1 to allow the calculation to be made */

        /* real parts */
        if( z1->sign_zre[0] == '-')
        {
                z1_re = z1->abs_zre * -1;
        }
        else
        {
                z1_re = z1->abs_zre;
        }


        /* Imaginary parts */

        if( z1->sign_zim[0] == '-')
        {
                z1_im = z1->abs_zim * -1;
        }
        else
        {
                z1_im = z1->abs_zim;
        }
	}
 /* calculate the real and imaginary result */
        result_re = z1_re ;
        result_im = -1 * z1_im ;

        /* send the real and imaginary results to 
         * make_z() and assign the returned pointer
         * to the result struct */
		if(!polar_in)
        	result_ptr = make_z(result_re, result_im, 0);
		else
		{
			ptr = make_z(result_re, result_im, 0);
			result_ptr = rect_to_polar(ptr);
			free(ptr);
		}

	return(result_ptr);
}


struct z_number *dot_product(struct z_number *z1, struct z_number *z2)
{
	struct z_number *result_ptr;
	struct z_number *z3;
	
	if(z1->polar)
	{
		z1 = polar_to_rect(z1);
	}
	if(z2->polar)
	{
		z2 = polar_to_rect(z2);
	}
	
	
	z3 = conjugate_z(z2);

	result_ptr= multiply_z(z1, z3);

	/* dot product is the Re part... so set Im to zero ... BUT it isn't displayed in
	 * print_result() anyway  */

	result_ptr->abs_zim = 0;

	free(z3);

	return(result_ptr);
}

struct z_number *cross_product(struct z_number *z1, struct z_number *z2)
{
	struct z_number *result_ptr;
	struct z_number *z3;
	struct z_number *z4;
	struct z_number *z5;
	struct z_number *z6;
	struct z_number *z7;
	struct z_number *z8;
	
	if(z1->polar)
	{
		z1 = polar_to_rect(z1);
	}
	if(z2->polar)
	{
		z2 = polar_to_rect(z2);
	}
	
	
	z3 = conjugate_z(z1);
	z4 = conjugate_z(z2);
	z5 = make_z(0,2,0);
	
	z6 = multiply_z(z2,z3);
	z7 = multiply_z(z1,z4);
	z8 = subtract_z(z6, z7);
	
	result_ptr = divide_z(z8, z5);

	/* I originally tried to do the calculation in one long function call to make_z() using
	 * only z1, z1 and "Local"  z3, z4 and 	z5  rather than making more "Local" temporary 
	 * z_numbers as intermediate values (now z6, z7 and z8).
	 *
	 * this lead to memory leak - I think due to calling multiply_z() and subtract_z() from within
	 * the  call to make_z();
	 *
	 * I got the correct answer, but memory leaked, despite calling free(z3), free(z4) and free(z5).
	 *
	 * Now I calculate the intermediate parts as new z_numbers and they are ALL free'd at the end:
	 */

	free(z3);	
	free(z4);
	free(z5);
	free(z6);
	free(z7);
	free(z8);


	/* cross product is the Re part... so set Im to zero */

	/* result_ptr->abs_zim = 0;  ---- commented out - it /should/ calculate out to zero
	 * but it isn't displayed in print_result() anyway */
	
	return(result_ptr);
}

struct z_number *uvec_z(struct z_number *z1)
{
	struct z_number *result_ptr;
	struct z_number *z3;
	float z1_re;
	float z1_im;
	float z3_re;
	
	if(z1->polar)
	{
		z1 = polar_to_rect(z1);
	}

	z3 = rect_to_polar(z1);
	
	z3_re = z3->abs_zre;
	
    /* real parts */
    if( z1->sign_zre[0] == '-')
    {
		z1_re = z1->abs_zre * -1;
    }
    else
	{
		z1_re = z1->abs_zre;
	}
	
	/* Imaginary parts */

    if( z1->sign_zim[0] == '-')
	{
		z1_im = z1->abs_zim * -1;
    }
    else
    {
        z1_im = z1->abs_zim;
    }

	z1_re = z1_re / z3_re;
	z1_im = z1_im / z3_re;
	
	result_ptr = make_z(z1_re, z1_im, 0);

	free(z3);

	return(result_ptr);
}






struct z_number *add_z(struct z_number *z1, struct z_number *z2)
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
        result_re = z1_re + z2_re;
        result_im = z1_im + z2_im;

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



struct z_number *subtract_z(struct z_number *z1, struct z_number *z2)
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
        result_re = z1_re - z2_re;
        result_im = z1_im - z2_im;

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



struct z_number *divide_z(struct z_number *z1, struct z_number *z2)
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
	
		result_re = ((z1_re * z2_re)/(z2_re*z2_re + z2_im*z2_im)
                 + (z1_im * z2_im)/(z2_re*z2_re + z2_im*z2_im));
 
		result_im = ((z1_im * z2_re)/(z2_re*z2_re + z2_im*z2_im)
                 - (z1_re * z2_im)/(z2_re*z2_re + z2_im*z2_im));



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

