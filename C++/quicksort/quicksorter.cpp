// Quicksorter in C++

#include <iostream>

using namespace std;

int *quicksort(int len, int *arr) {
	if (len == 0 || len == 1) {
		return arr;
	}

	int n = arr[0];
	int temp1[len];
	int temp2[len];
	int l = 0, r = 0;
	for (int i = 1; i < len; i++) {
		if (arr[i] < n) { 
			temp1[l++] = arr[i];
		} 
		else { 
			temp2[r++] = arr[i];
		}
	}
	
	int *sorted = (int *) malloc(sizeof(int) * len);
	for (int i = 0; i < l; i++) { 
		sorted[i] = quicksort(l, temp1)[i];
	}
	sorted[l] = n;	
	for (int i = 0; i < r; i++) {
		sorted[l+i+1] = quicksort(r, temp2)[i];
	}
	
	return sorted;
}

int main(int argc, char *argv[]) {
	int arr[argc-1];
	for (int i = 1; i < argc; i++) {
		arr[i-1] = atoi(argv[i]);
	}
	
	int *sorted = quicksort(argc - 1, arr);
	for (int i = 0; i < argc - 1; i++) {
		cout << sorted[i] << " ";
	}
	cout << endl;
	free(sorted);
	
	return 0;
}
