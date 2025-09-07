#include "defs.h"

struct z_number *make_mem(struct z_number *x, int opcode2)
{

	float real;
	float im;
	int polar;

	struct z_number *mem_ptr;

	printf("In make_mem with opcode %d, re %.3f, im %.3f \n", opcode2, x->abs_zre, x->abs_zim);

	if(x->sign_zre[0] == '-')
		real = x->abs_zre * -1;
	else
		real = x->abs_zre ;
	if(x->sign_zim[0] == '-')
		im = x->abs_zim * -1;
	else
		im = x->abs_zim;

	im = x->abs_zim;
	polar = x->polar;
	
	mem_ptr = make_z(real, im, polar);

	return mem_ptr;
}


void push_mem(struct z_number **stack, struct z_number *mem)
{

	float real;
	float im;
	int polar;
	if(mem->sign_zre[0] == '-')
		real = mem->abs_zre * -1;
	else
		real = mem->abs_zre;
	if(mem->sign_zim[0] == '-')
		im = mem->abs_zim * -1;
	else
		im = mem->abs_zim;

	polar = mem->polar;
	
	printf("In push_mem with real %.3f, im %.3f\n", real, im);

	stack_raise(stack, real, 0, im, 0, polar);
}

