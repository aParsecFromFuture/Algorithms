#include <stdlib.h>
#define POS_INF 100000

int* least_cost(int *table, int c_source, int c_dest)
{
	int i, j, index, s_index, d_index, l_index, min, min_i, min_j, *used_row, *used_col, *M;

	used_row = calloc(c_source, sizeof(int));
	used_col = calloc(c_dest, sizeof(int));
	M = calloc(c_source * c_dest, sizeof(int));

	l_index = (c_source + 1) * (c_dest + 1) - 1;

	while(table[l_index] > 0){
		min = POS_INF;
		for(i = 0; i < c_source; i++){
			for(j = 0; j < c_dest; j++){
				index = i * (c_dest + 1) + j;
				if(!used_row[i] && !used_col[j] && min > table[index]){
					min = table[index];
					min_i = i;
					min_j = j;
				}
			}
		}

		index = min_i * c_dest + min_j;
		s_index = min_i * (c_dest + 1) + c_dest;
		d_index = c_source * (c_dest + 1) + min_j;

		if(table[s_index] < table[d_index]){
			M[index] = table[s_index];
			table[d_index] -= table[s_index];
			table[l_index] -= table[s_index];
			table[s_index] = 0;
			used_row[min_i] = 1;
		}else{
			M[index] = table[d_index];
			table[s_index] -= table[d_index];
			table[l_index] -= table[d_index];
			table[d_index] = 0;
			used_col[min_j] = 1;
		}
	}
	free(used_row);free(used_col);
	return M;
}

int main(int argc, char **argv)
{
	int table[] = {
		6,	9,	5,	5,	8,	10,	5,	200, 
		8,	2,	4,	5,	5,	10,	8,	300,
		12,	8,	6,	10,	16,	4,	8,	150,
		10,	16,	8,	5,	6,	12,	6,	250,
		16,	12,	14,	8,	10,	16,	4,	100,
		100,	50,	75,	200,	150,	225,	200,	1000,};

	int *M = least_cost(table, 5, 7);
}



