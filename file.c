#include "defs.h"


void save_state(struct z_number **state, struct z_number *lastx)
{
	FILE *zstate;

	zstate = fopen("mem.db", "w");
	if(!zstate)
	{
		puts("can't open mem.db");
		exit(1);
	}
	for(int i = 0;i<SIZE;++i)

		fwrite(state[i], sizeof(struct z_number),1,zstate);

	fwrite(lastx, sizeof(struct z_number),1, zstate);

	fclose(zstate);
	puts("...state saved");

}

void read_state(struct z_number **state, struct z_number *lastx)
{

/* a "local" struct just for this function, not declared as a
 * pointer and therefore the members are accessed by 
 *
 * 	r_state.abs_zre  instead of r_state->abs_zre
 *
 * 	etc....
 * 	*/


	struct z_number r_state;

	FILE *zstate;
	int s;

	zstate = fopen("mem.db", "r");
	if(!zstate)
	{
		puts("can't open mem.db");
		return;
	}
	
	/* the file has 11 items, one per stack entry PLUS the 
	 * lastx - assuming a SIZE of 10....
	 *
	 * It would be better to use i<SIZE+1 here instead of 11 */

	while(!feof (zstate))
	{
		for(int i = 0;i<SIZE+1;++i)
		{
			s = fread(&r_state, sizeof(struct z_number), 1, zstate);
			if(s == 0)
				break;
			if(i<SIZE)
			{
				state[i]->abs_zre =  r_state.abs_zre;
				state[i]->abs_zim =  r_state.abs_zim;
				state[i]->sign_zre[0] = r_state.sign_zre[0];
				state[i]->sign_zim[0] = r_state.sign_zim[0];
				state[i]->polar = r_state.polar;
				}
			else
			{	
			lastx->abs_zre =  r_state.abs_zre;
			lastx->abs_zim =  r_state.abs_zim;
			lastx->sign_zre[0] = r_state.sign_zre[0];
			lastx->sign_zim[0] = r_state.sign_zim[0];
			lastx->polar = r_state.polar;
			}
		}
	}

	fclose(zstate);
	printf("\nState retrieved...");
}



