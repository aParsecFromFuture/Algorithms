#include <stdlib.h>

int MCOP(int dim_list[][2], int n)
{
	int i, j, k, l, cost, min_cost, *p, *M;

	p = malloc(sizeof(int) * (n + 1));
	
	for(i = 0; i < n; i++)
		p[i] = dim_list[i][0];

	p[n] = dim_list[n - 1][1];

	M = calloc(n * n, sizeof(int));
	
	for(i = 0; i < n; i++)
		M[i * n + i] = 0;

	for(l = 2; l <= n; l++)
		for(i = 0; i < n - l + 1; i++){
			j = i + l - 1;
			min_cost = M[(i + 1) * n + j] + (p[i] * p[i + 1] * p[j + 1]);
			for(k = i + 1; k < j; k++){
				cost = M[i * n + k] + M[(k + 1) * n + j] + (p[i] * p[k + 1] * p[j + 1]);
				if(min_cost > cost){
					min_cost = cost;
				}
			}
			M[i * n + j] = min_cost;
		}

	return M[n - 1];
}

int main(int argc, char **argv)
{
	int matrices[4][2] = {{6, 3}, {3, 4}, {4, 7}, {7, 5}};
	int cost = MCOP(matrices, 4);
}
