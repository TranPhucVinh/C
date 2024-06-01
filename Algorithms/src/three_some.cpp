int remove_all_duplicates(vector<vector<int>> &vec) {
    std::sort(vec.begin(), vec.end());
    vector<vector<int>>::iterator last = std::unique(vec.begin(), vec.end());

    int new_sz = std::distance(vec.begin(), last);// New size

    return new_sz;
}

vector<vector<int>> threeSum(vector<int>& nums) {
    int target = 0;

    vector<vector<int>> found_members;
    sort(nums.begin(), nums.end());

    for (int i = 0; i+1 < nums.size(); i++) {
        if (i > 0 && nums[i] == nums[i - 1]) {
           continue;
        }

        int left = i + 1;
        int right = nums.size() - 1;

        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == target) {
                found_members.push_back({nums[i], nums[left], nums[right]});

                while (left < right && nums[left] == nums[left + 1]) {
                    left++;
                }

                while (left < right && nums[right] == nums[right - 1]) {
                    right--;
                }
                
                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }

    // Case: nums = [0,0,0,0], which will return { [0,0,0], [0,0,0]}
    int new_sz = remove_all_duplicates(found_members);

    found_members.resize(new_sz);

    return found_members;

}
