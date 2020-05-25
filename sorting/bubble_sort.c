#define SWAP(x, y) {x = x + y; y = x - y; x = x - y;}

void bubble_sort(int arr[], int len)
{
	int i, j;
	for(i = 0; i < len - 1; i++){
		for(j = 0; j < len - i - 1; j++){
			if(arr[j] > arr[j + 1])
				SWAP(arr[j], arr[j + 1]);
		}
	}
}

int main(int argc, char **argv)
{
	int arr[] = {3, 1, 5, 9, 6, 0, 8, 2, 7, 4};
	bubble_sort(arr, 10);
}
