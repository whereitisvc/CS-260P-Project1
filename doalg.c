#include <stdio.h>

int select(int* Best, int i, int k);
int loc_binarySearch(int* Best, int key, int low, int high);
void swapShift(int* Best, int k, int key );

int doalg(int n, int k, int* Best){
	int i;
    //initialize a default Best array with size k and all -1.
	for (i = 0; i < k; i++) {
		Best[i] = -1;
	}
    //compare and select the k largest elements in array Best
	for (i = 1; i <= n; i++){
		select(Best, i, k);
	}
	return 1;
}

int select(int* Best, int i, int k){
    /* ===========================================================
    if i is larger than the last item of the Best array,
    replace the last item of the k size Best array with element i.
    Then, use binary search to find the best location to put i.
    return 0 if do not need to insert
    return 1 after insert element i
    ============================================================*/
	if (Best[k-1] == -1 || COMPARE(Best[k-1], i) == 2){
		Best[k-1] = i;
        int loc = loc_binarySearch(Best, k-1, 0, k-1);
        swapShift(Best, k, loc); // swap and shift the array down
        return 1;
	}
	else
		return 0; // if not larger, then do not need to insert
}

int loc_binarySearch(int* Best, int key, int low, int high){
    /* ===========================================================
    locate the position of key in the Best array
    return the index of the position
	---------------------------------------------------------------
	Adapted from https://www.geeksforgeeks.org/binary-search/
    ============================================================*/
	int mid = (high + low) / 2; // find middle index
	if (low == high){ // return index if low and high are the same
		return low;
	}
    // if key is larger than mid, update high <- mid
	if (Best[mid] == -1 || COMPARE(Best[key], Best[mid]) == 1){
		return loc_binarySearch(Best, key, low, mid);
	}
    else{
		return loc_binarySearch(Best, key, mid+1, high);
    }
}

void swapShift(int* Best, int k, int key){
    /* ===========================================================
    insert the compared (larger) item Best[k-1] of the array Best
	to loc, then shift down the rest of the elements.
    ============================================================*/
	int temp = Best[k-1];
	int i;
	for (i = k-1; i > key; i--){
		Best[i] = Best[i-1];
	}
	Best[key] = temp;
}
