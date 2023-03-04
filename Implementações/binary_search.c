#include <stdio.h>

int binary_search(int arr[], int n, int key) {
    int ini = 0;
    int fim = n-1;

    while(ini <= n) {
        int mid = (ini + fim)/2;

        if(arr[mid] == key) {
            return mid;
        }
        else if(arr[mid] > key) {
            fim = mid - 1;
        }
        else {
            ini = mid + 1;
        }
    }

    return -1;
}

int binary_search_recursive(int arr[], int ini, int fim, int key)
{
	if(ini > fim) return -1;

	if(ini == fim) 
    {
		if(arr[ini] == key)
			return ini;
		else
			return -1;
	}

	int mid = (ini + fim)/2;

	if(arr[mid] < key)  return binary_search_recursive(arr, mid+1, fim, key);
	
	if(arr[mid] == key) return binary_search_recursive(arr, ini, mid, key);
	
	else 				   return binary_search_recursive(arr, fim, mid-1, key);
	
}

int main()
{
    int arr[] = {1,8,3,9,5,4,3};
    int n = sizeof(arr)/sizeof(int);

    printf("%d\n",binary_search_recursive(arr, 0, n-1, 9));    
}