#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

// Function to merge two halves of a vector
void merge(vector<int>& vec, int left, int mid, int right) {
    // Calculate sizes of two halves
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors for left and right halves
    vector<int> L(n1), R(n2);

    // Copy data to temporary vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = vec[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = vec[mid + 1 + j];

    // Merge the temporary vectors back into vec[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vec[k++] = L[i++];
        } else {
            vec[k++] = R[j++];
        }
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        vec[k++] = L[i++];
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        vec[k++] = R[j++];
    }
}

// Function to perform merge sort
void mergeSort(vector<int>& vec, int left, int right) {
    // Base case: return if the array has only one element
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Recursively sort the first and second halves
        #pragma omp parallel sections
        {
            // Sort the left half in parallel
            #pragma omp section
            mergeSort(vec, left, mid);

            // Sort the right half in parallel
            #pragma omp section
            mergeSort(vec, mid + 1, right);
        }

        // Merge the sorted halves
        merge(vec, left, mid, right);
    }
}

int main() {
    // Define a vector of size 10 with predefined values
    vector<int> data = {9, 7, 5, 3, 1, 2, 4, 6, 8, 10};

    // Display the original vector
    cout << "Original Vector: ";
    for (int num : data) {
        cout << num << " ";
    }
    cout << endl;

    // Perform merge sort on the vector
    mergeSort(data, 0, data.size() - 1);

    // Display the sorted vector
    cout << "Sorted Vector: ";
    for (int num : data) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

