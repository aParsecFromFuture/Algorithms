#include <stdlib.h>
#define MIN(x, y, z) ((x < y && x < z)? x : ((y < z)? y : z))

int levenshtein(const char *s1, const char *s2)
{
	int i, j, m = 1, n = 1, d, index, *D;
	const char *tmp;

	tmp = s1;
	while(*(tmp++) != '\0')m++;

	tmp = s2;
	while(*(tmp++) != '\0')n++;
	
	D = malloc(sizeof(int) * m * n);

	for(i = 0; i < m; i++)
		D[i * n] = i;

	for(i = 0; i < n; i++)
		D[i] = i;

	for(i = 1; i < m; i++)
		for(j = 1; j < n; j++){
			index = i * n + j;
			D[index] = MIN(D[index - 1] + 1, 
				       D[index - n] + 1, 
				       D[index - n - 1] + ((s1[i - 1] == s2[j - 1])? 0 : 1));
		}

	d = D[m * n - 1];
	free(D);

	return d;
}

int main(int argc, char **argv)
{
	int levenshtein_distance = levenshtein("austria", "australia");
}
