#include <stdio.h>

int binsearch(int x,int* arr,int n);


int main()
{
	int arr[] = {1,2,3,4,5};
	int n = 5;
	int x = 5;

	int result = binsearch(x,arr,n);
	if(result != -1){
		printf("Target FOUND at Index: %d\n",result);
	}else{
		printf("Target NOT FOUND!!\n");
	}
	
	return 0;
}


int binsearch(int x,int* arr,int n){
	int low = 0;
	int high = n - 1;
	int mid = 0;

	while (low <= high) {
    		mid = (low + high) / 2;
    		if (x > arr[mid]){
        		low = mid + 1;
		}else{
        		high = mid - 1;  // covers both < and ==
		}
	}
	return (x == arr[low]) ? low : -1; 
}
