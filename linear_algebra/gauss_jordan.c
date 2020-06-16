void gauss_jordan(float *matrix, int r, int c)
{
	int i, j, k, offset_1, offset_2, pivot_j;
	float tmp;
	for(i = 0; i < r; i++){
		offset_1 = i * c;
		for(j = 0; j < c && !matrix[offset_1 + j]; j++);
		
		if(matrix[offset_1 + j]){
			pivot_j = j;	
			tmp = (1.0f / matrix[offset_1 + pivot_j]);
			matrix[offset_1 + pivot_j] = 1.0f;

			for(j = pivot_j + 1; j < c; j++)
				matrix[offset_1 + j] *= tmp;

			for(k = 0; k < r; k++){
				
				if(k == i)continue;
				
				offset_2 = k * c;
				tmp = matrix[offset_2 + pivot_j];
				matrix[offset_2 + pivot_j] = 0.0f;

				for(j = pivot_j + 1; j < c; j++)
					matrix[offset_2 + j] -= tmp * matrix[offset_1 + j];
			}
		}
	}
}

int main(int argc, char **argv)
{
	float matrix[9] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
	gauss_jordan(matrix, 3, 3);
}
