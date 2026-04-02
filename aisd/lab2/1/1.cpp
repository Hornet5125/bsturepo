#include <iostream>
#include <vector>
using namespace::std;
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        vector<int> arr(100001);
        for (int i = 0; i < nums.size(); i ++) {
            arr[nums[i] + 50000] += 1;
        }        
        for (int index = 0, i = 0; i < arr.size(); i++){
            for (int j = 0; j < arr[i]; j ++) {
                nums[index] = i - 50000;
                index ++;
            }
        }
        return nums;        
    }
};
int main(){
    Solution sol;
    vector<int> nums = {5, 2, 3, 1, -5, 10, 0};
    vector<int> sorted = sol.sortArray(nums);   
    for (int num : sorted) {
        cout << num << " ";
    }
    cout << endl;
}