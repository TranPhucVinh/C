#include <stdio.h>

int find_last_occurrence(int *array, int start_index, int end_index) {
    int arr_sz = end_index+1;
    int middle = 0;
    if (start_index == end_index) {
        if (array[arr_sz-1] >= 0) return -1;// As there is no negative number inside array
        else return start_index;
    }

    middle = (start_index + end_index)/2;// Middle index

    if (array[middle] < 0){
        if (middle + 1 < arr_sz && array[middle + 1] >= 0) return middle;
        return find_last_occurrence(array, middle+1, end_index);
    } else {        
        return find_last_occurrence(array, start_index, middle);
    }
}

int find_first_occurrence(int *array, int start_index, int end_index) {
    int arr_sz = end_index+1;
    int middle = 0;
    if (start_index == end_index) {
        if (array[arr_sz-1] >= 0) return -1;// As there is no negative number inside array
        else return start_index;
    }

    middle = (start_index + end_index)/2;// Middle index

    if (array[middle] < 0) {
        return find_first_occurrence(array, start_index, middle);;
    }
    else {
        return find_first_occurrence(array, middle+1, end_index);
    }
}

int main() {
    int array[] = {8, 6, 4, 0, -1, -1, -1, -2, -3, -4, -5};
    // int array[] = {-8};
    int n = sizeof(array) / sizeof(int);

    printf("Total negative number: %d\n", find_last_occurrence(array, 0, n) - find_first_occurrence(array, 0, n) + 1);

    return 0;
}
