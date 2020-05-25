#include <stdlib.h>
#define POS_INF 100000

int* nw_corner(int *table, int c_source, int c_dest)
{
	int i = 0, j, index, s_index, d_index, l_index, min, min_j, *used_col, *M;

	used_col = calloc(c_dest, sizeof(int));
	M = calloc(c_source * c_dest, sizeof(int));

	l_index = (c_source + 1) * (c_dest + 1) - 1;

	while(table[l_index] > 0){
		min = POS_INF;
		for(j = 0; j < c_dest; j++){
			index = i * (c_dest + 1) + j;
			if(!used_col[j] && min > table[index]){
				min = table[index];
				min_j = j;
			}
		}

		index = i * c_dest + min_j;
		s_index = i * (c_dest + 1) + c_dest;
		d_index = c_source * (c_dest + 1) + min_j;

		if(table[s_index] < table[d_index]){
			M[index] = table[s_index];
			table[d_index] -= table[s_index];
			table[l_index] -= table[s_index];
			table[s_index] = 0;
			i++;
		}else{
			M[index] = table[d_index];
			table[s_index] -= table[d_index];
			table[l_index] -= table[d_index];
			table[d_index] = 0;
			used_col[min_j] = 1;
		}
	}
	free(used_col);
	return M;
}

int main(int argc, char **argv)
{
	int table[] = {
		6,	8,	10,	150, 
		7,	11,	11,	175, 
		4,	5,	12,	275, 
		200,	100,	300,	600};
	int *M = nw_corner(table, 3, 3);
}
