#include "defs.h"


struct z_number *make_lastx(struct z_number *x)
{
	struct z_number *lastx_ptr;
	float real;
	float im;
	int polar;

	if(x->sign_zre[0] == '-')
		real = x->abs_zre * -1;
	else
		real = x->abs_zre;

	if(x->sign_zim[0] == '-')
		im = x->abs_zim * -1;
	else
		im = x->abs_zim;

	polar = x->polar;

	lastx_ptr = make_z(real, im, polar);

	return lastx_ptr;
}




