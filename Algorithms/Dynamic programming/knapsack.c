#include <stdio.h>

#define MAX_WEIGHTS 7
#define TOTAL_ITEMS  5

static inline int MAX(int a, int b) {
    return ((a) > (b) ? (a) : (b));
} 

static inline int MIN(int a, int b) {
   return ((a) < (b) ? (a) : (b));
}

int main() {
    int k_tbl[TOTAL_ITEMS + 1][MAX_WEIGHTS + 1];// Knapsack table
    int w[TOTAL_ITEMS + 1] = {0, 3, 1, 3, 4, 2}; // Store the weight of each item
    int v[TOTAL_ITEMS + 1] = {0, 2, 2, 4, 5, 3}; // Store the value of each item

    for (int _item_idx = 0; _item_idx <= TOTAL_ITEMS; _item_idx++) {
        // _c_idx: Capacity index, it's also the current capacity we use to 
        //         measure the max total value based on total current items
        for (int _c_idx = 0; _c_idx <= MAX_WEIGHTS; _c_idx++) {
            if ( (_c_idx == 0) || (_item_idx == 0) ) {
                k_tbl[_item_idx][_c_idx] = 0;
                continue;
            }
            if (w[_item_idx] > _c_idx) k_tbl[_item_idx][_c_idx] = k_tbl[_item_idx-1][_c_idx];
            else {
                k_tbl[_item_idx][_c_idx] = MAX(k_tbl[_item_idx-1][_c_idx], v[_item_idx] + k_tbl[_item_idx-1][_c_idx - w[_item_idx]]);
            }
        }
    }

    // View the whole knapsack table
    for (int _item_idx = 0; _item_idx <= TOTAL_ITEMS; _item_idx++) {
        for (int _c_idx = 0; _c_idx <= MAX_WEIGHTS; _c_idx++) {
            printf("%d ", k_tbl[_item_idx][_c_idx]);
        }
        printf("\n");
    }

    printf("MAX %d\n",  k_tbl[TOTAL_ITEMS][MAX_WEIGHTS]);

    // Display the chosen item. 1 for chosen, 0 for not chosen
    int chosen_items[TOTAL_ITEMS + 1] = {0, 0, 0, 0, 0, 0};
    int _c_idx = MAX_WEIGHTS;
    int _tmp_k_tbl; // A temp variable points to the knapsack table to keep track of the chosen item
    for (int _item_idx = TOTAL_ITEMS; _item_idx >= 0; _item_idx--) {
        if (_c_idx >= 0) {
            _tmp_k_tbl = k_tbl[_item_idx][_c_idx];
            if (_tmp_k_tbl != k_tbl[_item_idx-1][_c_idx]) {
                chosen_items[_item_idx] = 1;
                _c_idx = _c_idx - w[_item_idx];
            } 
           _tmp_k_tbl = k_tbl[_item_idx - 1][_c_idx];
        }
    }

    for (int i = 0; i <= TOTAL_ITEMS; i++) printf("%d ", chosen_items[i]);
    printf("\n");
}
