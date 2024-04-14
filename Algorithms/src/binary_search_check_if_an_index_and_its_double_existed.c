class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        std::sort(arr.begin(), arr.end());// Sort array to non-decreasing order

        cout << endl;

        for (int i=0; i < arr.size(); i++){
            if (i+1 <= arr.size()-1) {
                if (arr[i] < 0) {
                    // Only search for the divisble number of 2
                    // Case: {-485, -242}: False
                    if (!(arr[i] % 2)) search_number(arr[i]/2, arr, i+1, arr.size()-1);
                }
                else search_number(arr[i]*2, arr, i+1, arr.size()-1);
            }
            if (found) return found;
        }
        return found;
    }

    bool found = false;// Mark if the target is found

    /*
        Return:
        * Index of the found target
        * the index when binary search recursive function search_number()
        ends when target is inside [lower bound, upper bound]
    */
    int search_number(int target, vector<int>& array, int start_index, int end_index) {
        int middle = 0;
        if (start_index == end_index) {
            if (target == array[start_index]){
                found = true;
                return start_index;
            } else {
                found = false;
                return start_index;
            }
        }
        middle = (start_index + end_index)/2;// Middle index
        if (target == array[middle]) {
            found = true;
            return middle;
        }
        else if (target > array[middle]){
            return search_number(target, array, middle+1, end_index);
        } else {
            return search_number(target, array, start_index, middle);
        }
        
        return 0;
    }
};