/************************************************************************
** Program name:   insertTime HW-2 CS325
** Author:         Adam Wright
** Date:           10/10/2019
** Description:    Program that counts the runtime of stoogesort and
**                 outputs the results to the terminal. This sorting
**                 algorithm is a slow recursive algorithm
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
** Description:   Defintion of stoogeSort function which sorts an
**                array of integers. It takes an array and 2 ints
**                which represent the current range to sort. If there
**                are more than 2 elements then 3 recursive calls are 
**                made to sort the 1st 2/3, then the 2nd 2/3, and then
**                the 1st 2/3 again. I viewed the website GeeksforGeeks
**                https://www.geeksforgeeks.org/stooge-sort/ while
**                working on this algorithm.
*********************************************************************/
void stoogeSort(deque<int> &arr, int l, int r)  
{
    // If leftmost value > rightmost value then swap
    if (arr[l] > arr[r])
    {
        int temp = arr[l];
        arr[l] = arr[r];
        arr[r] = temp;
    }

    // If range has 2+ elements
    if (r - l + 1 > 2)
    {
        int t = (r - l + 1) / 3;
        
        stoogeSort(arr, l, r - t);
        stoogeSort(arr, l + t, r);
        stoogeSort(arr, l, r - t);
    } 
}


int main()
{
    // Seed the random function
    srand(time(NULL));

    // Declare the necessary containers
    deque<int> numArray;
    int arrSize = 150;
    double time;
    int iter = 1;

    cout << endl << endl;
    cout << "*****************************************" << endl;
    cout << "An Exploration of StoogeSort Runtimes" << endl;
    cout << "*****************************************";
    cout << endl << endl;

    // Run the sorting for 150 - 1,500
    while (arrSize <= 1500)
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
        stoogeSort(numArray, 0, arrSize - 1);

        // Stop time and calculate duration
        auto stop = high_resolution_clock::now();
        auto runTime = duration_cast<microseconds>(stop - start);

        // Convert microseconds to seconds
        time = runTime.count() * 0.000001;


        // Print out the array size and runtime
        cout << iter <<" Array Size: " << arrSize;
        cout << "    Time: " << time << " sec." << endl;
        iter++;


        // Increment the arrSize by 150
        arrSize += 150;

        // Clear the deque
        numArray.clear();
    }

    cout << endl;
    cout << "*****************************";
    cout << endl << endl;
   
    return 0;
}