#define SWAP(x, y) {x = x + y; y = x - y; x = x - y;}

void selection_sort(int arr[], int len)
{
	int i, j, min_index;
	for(i = 0; i < len - 1; i++){
		min_index = i;
		for(j = i + 1; j < len; j++){
			if(arr[min_index] > arr[j])
				min_index = j;
		}
		SWAP(arr[min_index], arr[i]);
	}
}

int main()
{
	int arr[] = {3, 1, 5, 9, 6, 0, 8, 2, 7, 4};
	selection_sort(arr, 10);
}
