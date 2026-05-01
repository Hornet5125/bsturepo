#include <iostream>
#include <vector>
#include <algorithm>
using namespace::std;
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        return nums;
    }
};
int main(){
    Solution sol;
    vector<int> nums = {1,3,2};
    vector<int> sorted = sol.sortArray(nums);
    for (int num : sorted){
        cout << num << " ";
    }
    return 0;
}