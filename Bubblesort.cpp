#include <iostream>
#include <vector>
#include <omp.h>

void parallelBubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    
    // Parallelize the outer loop (each iteration represents a pass through the array)
    #pragma omp parallel for
    for (int i = 0; i < n - 1; i++) {
        // Use OpenMP to parallelize the inner loop (comparisons and swaps)
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    std::cout << "Original array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    parallelBubbleSort(arr);
    
    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
