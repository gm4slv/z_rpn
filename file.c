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
	for(int i = 0;i<10;++i)

		fwrite(state[i], sizeof(struct z_number),1,zstate);

	fwrite(lastx, sizeof(struct z_number),1, zstate);

	fclose(zstate);
	puts("...state saved");

}

void read_state(struct z_number **state, struct z_number *lastx)
{
	struct z_number *r_state;
	struct z_number *r_last;

	FILE *zstate;
	int s;
	int l;

	zstate = fopen("mem.db", "r");
	if(!zstate)
	{
		puts("can't open mem.db");
		return;
	}

	while(!feof (zstate))
	{
		for(int i = 0;i<10;++i)
		{
			s = fread(r_state, sizeof(struct z_number), 1, zstate);
			if(s == 0)
				break;
			state[i]->abs_zre =  r_state->abs_zre;
			state[i]->abs_zim =  r_state->abs_zim;
			state[i]->sign_zre[0] = r_state->sign_zre[0];
			state[i]->sign_zim[0] = r_state->sign_zim[0];
			state[i]->polar = r_state->polar;

		}
		s = fread(r_state, sizeof(struct z_number), 1, zstate);
		if(s == 0)
			break;
		lastx->abs_zre =  r_state->abs_zre;
		lastx->abs_zim =  r_state->abs_zim;
		lastx->sign_zre[0] = r_state->sign_zre[0];
		lastx->sign_zim[0] = r_state->sign_zim[0];
		lastx->polar = r_state->polar;
			
	}
	fclose(zstate);
	printf("\nState retrieved...");
}



