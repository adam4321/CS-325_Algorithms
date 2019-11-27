/************************************************************************
** Program name:   mergeTime HW-1 CS325
** Author:         Adam Wright
** Date:           10/4/2019
** Description:    Program that counts the runtime of mergesort and 
**                 outputs the results to the terminal.
************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <deque>
#include <ctime>
#include <chrono>

using std::cout;
using std::endl;
using std::string;
using std::deque;
using namespace std::chrono;


/*********************************************************************
** Description:   Defintion of the merge function which sorts and
**                merges the subarrays of integers as a helper function.
**                It takes a deque, the leftmost index, the middle index
**                and the right index which is arraylength - 1 as 
**                arguments. The website Geeks for Geeks at this Url
**                https://www.geeksforgeeks.org/merge-sort/ was viewed
**                to help put the algorithm together.
*********************************************************************/
void merge(deque<int> &arr, int l, int m, int r)
{ 
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
  
    // Create temp arrays
    int *L = new int [n1];
    int *R = new int [n2];
  
    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }

    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m+1 + j];
    }
  
    // Merge the temp arrays back into arr[l...r]
    i = 0; // Index of first subarray 
    j = 0; // Index of second subarray 
    k = l; // Index of merged subarray

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    // Copy the remaining elements of L
    while (i < n1)
    { 
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

/*********************************************************************
** Description:   Defintion of mergeSort function which sorts an
**                array of integers. It takes a deque, the left index,
**                and the right index which is length - 1 as arguments.
**                The website Geeks for Geeks at this Url
**                https://www.geeksforgeeks.org/merge-sort/ was viewed
**                to help put the algorithm together.
*********************************************************************/
void mergeSort(deque<int> &arr, int l, int r)
{ 
    if (l < r)
    {
        int m = (l + r) / 2;
  
        // Sort the first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
  
        merge(arr, l, m, r);
    }
}


int main()
{
    // Seed the random function
    srand(time(NULL));

    // Declare the necessary containers
    deque<int> numArray;
    int arrSize = 3000;
    double time;
    int iter = 1;

    cout << endl << endl;
    cout << "*************************************" << endl;
    cout << "An Exploration of Mergesort Runtimes" << endl;
    cout << "*************************************";
    cout << endl << endl;

    // Run the sorting for 3,000 - 30,000
    while (arrSize <= 30000)
    {
        // Fill the deque with random numbers 0 - 10,000
        int i = 0;
        while (i < arrSize)
        {
            int random = rand() % 10000;
            numArray.push_back(random);
            i++;
        }


        // Start time
        auto start = high_resolution_clock::now();

        // One loop of the sort
        mergeSort(numArray, 0, arrSize - 1);

        // Stop time and calculate duration
        auto stop = high_resolution_clock::now();
        auto runTime = duration_cast<microseconds>(stop - start);

        // Convert microseconds to seconds
        time = runTime.count() * 0.000001;


        // Print out the array size and runtime
        cout << iter << " Array Size: " << arrSize;
        cout << "    Time: " << time << " sec." << endl;
        iter++;


        // Increment the arrSize by 3,000
        arrSize += 3000;

        // Clear the deque
        numArray.clear();
    }

    cout << endl;
    cout << "*****************************";
    cout << endl << endl;

    return 0;
}