void simplex(float *matrix, int r, int c, int v_c)
{
	int i, j, min_i, min_j, offset_1, offset_2;
	float tmp, min, pos_inf;
	
	pos_inf = 1.0f / 0.0f;
	min = pos_inf;

	for(j = 0; j < v_c; j++)
		if(min > matrix[j]){
			min = matrix[j];
			min_j = j;
		}

	while(min < 0){
		min = pos_inf;
		for(i = 1; i < r; i++){
			offset_1 = i * c;
			tmp = matrix[offset_1 + c - 1] / matrix[offset_1 + min_j];
			if(min > tmp){
				min = tmp;
				min_i = i;
			}
		}

		offset_1 = min_i * c;
		tmp = (1 / matrix[offset_1 + min_j]);
		
		for(j = 0; j < c; j++)
			matrix[offset_1 + j] *= tmp;

		for(i = 0; i < r; i++){
			if(i == min_i)
				continue;

			offset_2 = i * c;
			tmp = matrix[offset_2 + min_j];
			for(j = 0; j < c; j++){
				matrix[offset_2 + j] -= tmp * matrix[offset_1 + j];
			}
		}

		min = pos_inf;
		for(j = 0; j < v_c; j++)
			if(min > matrix[j]){
				min = matrix[j];
				min_j = j;
			}
	}
}

int main(int argc, char **argv)
{
	float table[] = {
		-5.0f,	-9.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
		3.0f,	4.0f,	1.0f,	0.0f,	0.0f,	0.0f,	2400.0f,
		1.0f,	2.0f,	0.0f,	1.0f,	0.0f,	0.0f,	900.0f,
		2.0f,	3.0f,	0.0f,	0.0f,	1.0f,	0.0f,	1500.0f,
		2.0f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	1200.0f
	};
	simplex(table, 5, 7, 3);
}
