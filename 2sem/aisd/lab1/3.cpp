#include <iostream>
#include <vector> 
using namespace::std;
int binary_search(vector<int> arr,int target){
    int left = 0;
    int i = 0;
    int right = arr.size() - 1;
    for (; left <= right;i++) {
        int mid = left + (right - left) / 2; 
        if (arr[mid] == target){
            cout << "Количество итераций: " << i << endl;
            return mid;
        }
        if (arr[mid] < target){
            left = mid + 1;
        }
        else right = mid - 1;
    }
    return -1;
}
int interpolation_search(vector<int> arr,int target){
    int low = 0;
    int i = 0;
    int high = arr.size() - 1;
    for (;low <= high && target >= arr[low] && target <= arr[high];i++) {
        if (low == high) {
            if (arr[low] == target){
                return low;
            }
            return -1;
        }
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]));
        if (arr[pos] == target){
            cout << "Количество итераций: " << i << endl;
            return pos;
        }
        if (arr[pos] < target){
            low = pos + 1;
        }
        else{
            high = pos - 1;
        }
    }
    return -1; 
}
int main(){
    vector<int> arr = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
    int target = 512;
    binary_search(arr, target);
    return 0;
}