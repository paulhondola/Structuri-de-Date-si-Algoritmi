#include "search.h"

int linear_search(const data_t *arr, const size_t size, const int target) {
    for (size_t i = 0; i < size; i++)
        if (get_key(arr[i]) == target)
            return i;
    return -1;
}

int binary_search(const data_t *arr, const size_t size, const int target){
    size_t left = 0, right = size - 1;
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        if (get_key(arr[mid]) == target)
            return mid;
        if (get_key(arr[mid]) < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int interpolation_search(const data_t *arr, const size_t size, const int target) {
    size_t left = 0, right = size - 1;
    while(left <= right) {
        if(target < get_key(arr[left]) || target > get_key(arr[right]))
            break;

        int mid = left + (right - left) * (target - get_key(arr[left])) / (get_key(arr[right]) - get_key(arr[left]));

        if(get_key(arr[mid]) == target)
            return mid;

        if(get_key(arr[mid]) < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}