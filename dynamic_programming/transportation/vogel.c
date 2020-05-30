#include <stdlib.h>

float* vogel(float *table, int c_source, int c_dest)
{
	int i, j, balance, min_i, min_j, supply, demand, offset, tmp;
	int *used_row, *used_col;
	float *M;
	float penalty, max_penalty, min_1, min_2, pos_inf, neg_inf;

	M = calloc(c_source * c_dest, sizeof(float));
	used_row = calloc(c_source, sizeof(int));
	used_col = calloc(c_dest, sizeof(int));

	balance = (c_source + 1) * (c_dest + 1) - 1;
	pos_inf =  1.0f / 0.0f;
	neg_inf = -1.0f / 0.0f;

	while(table[balance] != 0){
		max_penalty = neg_inf;

		for(i = 0; i < c_source; i++){
			if(used_row[i])
				continue;

			min_1 = pos_inf;
			min_2 = pos_inf;
			offset = i * (c_dest + 1);

			for(j = 0; j < c_dest; j++){
				if(used_col[j])
					continue;
				
				if(min_1 > table[offset + j]){
					min_2 = min_1;
					min_1 = table[offset + j];
					tmp = j;
				}else if(min_2 > table[offset + j]){
					min_2 = table[offset + j];
				}
			}
			penalty = min_2 - min_1;

			if(max_penalty < penalty){
				max_penalty = penalty;
				min_i = i;
				min_j = tmp;
			}
		}
	
		for(j = 0; j < c_dest; j++){
			if(used_col[j])
				continue;
			
			min_1 = pos_inf;
			min_2 = pos_inf;
			
			for(i = 0; i < c_source; i++){
				if(used_row[i])
					continue;
				
				offset = i * (c_dest + 1);

				if(min_1 > table[offset + j]){
					min_2 = min_1;
					min_1 = table[offset + j];
					tmp = i;
				}else if(min_2 > table[offset + j]){
					min_2 = table[offset + j];
				}
			}
			penalty = min_2 - min_1;
			
			if(max_penalty < penalty){
				max_penalty = penalty;
				min_i = tmp;
				min_j = j;
			}
		}

		supply = min_i * (c_dest + 1) + c_dest;
		demand = c_source * (c_dest + 1) + min_j;

		if(table[supply] < table[demand]){
			M[c_dest * min_i + min_j] = table[supply];
			table[balance] -= table[supply];
			table[demand] -= table[supply];
			table[supply] = 0;
			used_row[min_i] = 1;
		}else{
			M[c_dest * min_i + min_j] = table[demand];
			table[balance] -= table[demand];
			table[supply] -= table[demand];
			table[demand] = 0;
			used_col[min_j] = 1;
		}
	}

	free(used_row);
	free(used_col);
	return M;
}

int main(int argc, char **argv){
	float table[] = {6.0f, 8.0f, 10.0f, 150.0f, 7.0f, 11.0f, 11.0f, 175.0f, 4.0f, 5.0, 12.0f, 275.0f, 200.0f, 100.0f, 300.0f, 600.0f};
	float *M = vogel(table, 3, 3);
}
