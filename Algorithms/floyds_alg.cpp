#include <bits/stdc++.h>
using namespace std;
 
// Function to find the duplicate
// value in the given array arr[]
void findDuplicate(int arr[])
{
 
    // Initialise variables
    int tortoise = arr[0];
    int hare = arr[0];
 
    // Loop till we find the
    // duplicate element
    while (1) {
 
        tortoise = arr[tortoise];
 
        // Hare moves with twice
        // the speed of tortoise
        hare = arr[arr[hare]];
        if (tortoise == hare)
            break;
    }
 
    tortoise = arr[0];
 
    // Loop to get start point
    // of the cycle as start
    // point will be the duplicate
    // element
    while (tortoise != hare) {
        tortoise = arr[tortoise];
        hare = arr[hare];
    }
 
    // Print the duplicate element
    cout << tortoise;
}
 
// Example Code
int main()
{
    // Given array
    int arr[] = { 2, 6, 4, 1, 3, 1, 5 };
 
    // Function Call
    findDuplicate(arr);
 
    return 0;
}
