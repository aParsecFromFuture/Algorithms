#define EPSILON 0.001f
#define IS_ZERO(x) ((x < EPSILON && x > -EPSILON)? 1 : 0)

void gauss_jordan(float *matrix, int r, int c)
{
	int i, j, k, offset_1, offset_2, pivot_j;
	float div_num;
	for(i = 0; i < c; i++){
		offset_1 = i * c;
		for(j = 0; j < c && IS_ZERO(matrix[offset_1 + j]); j++);
		
		if(!IS_ZERO(matrix[offset_1 + j])){
			pivot_j = j;	
			div_num = (1.0f / matrix[offset_1 + pivot_j]);

			for(; j < c; j++)
				matrix[offset_1 + j] *= div_num;

			for(k = 0; k < r; k++){
				
				if(k == i)continue;
				
				offset_2 = k * c;
				div_num = matrix[offset_2 + pivot_j];

				for(j = pivot_j; j < c; j++)
					matrix[offset_2 + j] -= div_num * matrix[offset_1 + j];
			}
		}
	}
}

int main(int argc, char **argv)
{
	float matrix[9] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
	gauss_jordan(matrix, 3, 3);
}
