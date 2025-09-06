#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define SIZE 10
#define VERSION "v0.5"

struct z_number {
	char sign_zre[2]; /* sign members have 2 bytes to pad the whole */
					  /* struct out to 16 bytes */
	char sign_zim[2]; /* this makes it align in memory and prevents valgrind  */
	float abs_zre;    /* warnings when saving state file */
	float abs_zim;    /* the additional chars are just assigned */
	int polar;        /* a letter in make_z and are read back into */
					  /* the stack and last-x when the state is read */
   					  /* at start-up, to keep valgrind happy */	
};


/*********************************************
 * function prototypes                       *
 *
 * *******************************************/

/* a function to create the struct (pointer) when given the 
 * real and imaginary parts of a complex number */
struct z_number *make_z(float zre, float zim, int p );

/* a funtion to add two complex numbers and put the result into 
 * result struct */
struct z_number *add_z(struct z_number *z1, struct z_number *z2);
/* function to subtract two complex numbers */
struct z_number *subtract_z(struct z_number *z1, struct z_number *z2);
/* function to calculate the inverse of a complex number */
struct z_number *invert_z(struct z_number *z1);
/* function to multiply 2 complex numbers */
struct z_number *multiply_z(struct z_number *z1, struct z_number *z2);
/* function to multiply 2 complex numbers */
struct z_number *divide_z(struct z_number *z1, struct z_number *z2);
struct z_number *divide2_z(struct z_number *z1, struct z_number *z2);
/* funtions to convert from Rect -> Polar -> */
struct z_number *rect_to_polar(struct z_number *z1);
struct z_number *polar_to_rect(struct z_number *z1);
/* functions for dot and cross products */
struct z_number *dot_product(struct z_number *z1, struct z_number *z2);
struct z_number *cross_product(struct z_number *z1, struct z_number *z2);
/* function to find the complex conjugate of a complex number */
 struct z_number *conjugate_z(struct z_number *z1);
/* function to find the unit vector of a complex number */
struct z_number *uvec_z(struct z_number *z1);

struct z_number *clear_z(void);

void stack_raise(struct z_number **p, float real,int real_null, float im, int im_null, int make_polar);

struct z_number *make_lastx(struct z_number *x);

void push_lastx(struct z_number **stack, struct z_number *lastx);

void show_stack(struct z_number **p, struct z_number *last_x);

void save_state(struct z_number **state, struct z_number *lastx);
void read_state(struct z_number **state, struct z_number *lastx);

void help(void);


