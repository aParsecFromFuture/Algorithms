#include <stdlib.h>

char* LCS(const char *s1, const char *s2)
{
	int i, j, l, m = 1, n = 1, index, *D, *H;
	const char *tmp;
	char *s3;

	tmp = s1;
	while(*(tmp++) != '\0')m++;

	tmp = s2;
	while(*(tmp++) != '\0')n++;
	
	D = calloc(m * n, sizeof(int));
	H = calloc(m * n, sizeof(int));

	for(i = 1; i < m; i++)
		for(j = 1; j < n; j++){
			index = i * n + j;
			if(s1[i - 1] == s2[j - 1]){
				D[index] = D[index - n - 1] + 1;
				H[index] = 0;
			}else{
				if(D[index - n] > D[index - 1]){
					D[index] = D[index - n];
					H[index] = 1;
				}else{
					D[index] = D[index - 1];
					H[index] = 2;
				}
			}
		}
	
	l = D[m * n - 1];
	s3 = malloc(sizeof(char) * (l + 1));
	s3[l] = 0;

	i = m - 1;
	j = n - 1;
	l = l - 1;
	while(i != 0 && j != 0){
		index = i * n + j;
		if(H[index] == 0){
			s3[l--] = s1[i - 1];
			i--; j--;
		}else{
			if(H[index] == 1){
				i--;
			}else{
				j--;
			}
		}
	}

	free(D);free(H);
	return s3;
}

int main(int argc, char **argv){
	char *s1 = LCS("austria", "australia");
}
