#include <stdlib.h>

float* nw_corner(float *table, int c_source, int c_dest)
{
	int i = 0, j, min_j, index, supply, demand, balance;
       	int *used_col;
	float min, pos_inf = 1.0f / 0.0f;
	float *M;

	used_col = calloc(c_dest, sizeof(int));
	M = calloc(c_source * c_dest, sizeof(int));

	balance = (c_source + 1) * (c_dest + 1) - 1;

	while(table[balance] > 0){
		min = pos_inf;
		for(j = 0; j < c_dest; j++){
			index = i * (c_dest + 1) + j;
			if(!used_col[j] && min > table[index]){
				min = table[index];
				min_j = j;
			}
		}

		index = i * c_dest + min_j;
		supply = i * (c_dest + 1) + c_dest;
		demand = c_source * (c_dest + 1) + min_j;

		if(table[supply] < table[demand]){
			M[index] = table[supply];
			table[demand] -= table[supply];
			table[balance] -= table[supply];
			table[supply] = 0;
			i++;
		}else{
			M[index] = table[demand];
			table[supply] -= table[demand];
			table[balance] -= table[demand];
			table[demand] = 0;
			used_col[min_j] = 1;
		}
	}
	free(used_col);
	return M;
}

int main(int argc, char **argv)
{
	float table[] = {
		6,	9,	5,	5,	8,	10,	5,	200, 
		8,	2,	4,	5,	5,	10,	8,	300,
		12,	8,	6,	10,	16,	4,	8,	150,
		10,	16,	8,	5,	6,	12,	6,	250,
		16,	12,	14,	8,	10,	16,	4,	100,
		100,	50,	75,	200,	150,	225,	200,	1000,};

	float *M = nw_corner(table, 5, 7);
}
