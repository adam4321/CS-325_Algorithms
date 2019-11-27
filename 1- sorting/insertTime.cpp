/************************************************************************
** Program name:   insertTime HW-1 CS325
** Author:         Adam Wright
** Date:           10/4/2019
** Description:    Program that counts the runtime of insertionsort and
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
** Description:   Defintion of insertionSort function which sorts an
**                array of integers. It takes an array and the array
**                length as arguments. The website Geeks for Geeks at
**                this Url https://www.geeksforgeeks.org/insertion-sort/
**                was used to help put the algorithm together.
********************************************************************/
void insertionSort(deque<int> &arr, int n)  
{  
    for (int i = 1; i < n; i++) 
    {
        int key = arr[i];  
        int j = i - 1;  
  
        // If element is greater than key, move it's position right
        while (j >= 0 && arr[j] > key) 
        {  
            arr[j + 1] = arr[j];  
            j = j - 1;  
        }

        arr[j + 1] = key;  
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
    cout << "*****************************************" << endl;
    cout << "An Exploration of Insertionsort Runtimes" << endl;
    cout << "*****************************************";
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
        insertionSort(numArray, arrSize);

        // Stop time and calculate duration
        auto stop = high_resolution_clock::now();
        auto runTime = duration_cast<microseconds>(stop - start);

        // Convert microseconds to seconds
        time = runTime.count() * 0.000001;


        // Print out the array size and runtime
        cout << iter <<" Array Size: " << arrSize;
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