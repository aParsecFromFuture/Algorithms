void insertion_sort(int arr[], int len)
{
	int i, j;
	for(i = 1; i < len; i++){
		j = i - 1;

		while(j >= 0 && arr[j] > arr[i]){
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = arr[i];
	}
}

int main(){
	int arr[] = {3, 1, 5, 9, 6, 0, 8, 2, 7, 4};
	insertion_sort(arr, 10);
}
