/************************************************************************
** Program name:   mergesort HW-1 CS325
** Author:         Adam Wright
** Date:           10/4/2019
** Description:    Program that implements mergesort by taking in data
**                 from a text file called data.txt and outputting the 
**                 sorted data to a file called merge.txt
************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::getline;
using std::ofstream;
using std::istringstream;
using std::deque;


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
    // Open the input file data.txt
    ifstream inFile;
    inFile.open("data.txt");

    // Open the output file insert.txt   
    ofstream outFile;
    outFile.open("merge.txt");

    // Declare the needed containers
    string line;
    int num;
    int arrSize;
    deque<int> numArray;

    // File I/O and sorting
    if (inFile.is_open() && outFile.is_open())
    {
        while (getline(inFile, line))
        {
            // Input the current line into the deque
            istringstream ss(line);

            for (string line; ss >> num; )
            {
                numArray.push_back(num);
            }


            // Set the array size with the stored first value
            arrSize = numArray[0];

            // Remove the array size number from deque[0]
            numArray.pop_front();

            // Sort the current deque
            mergeSort(numArray, 0, arrSize - 1);


            // Print out the sorted values to insert.txt
            for (int i = 0; i < arrSize; i++)
            {
                outFile << numArray[i];
            }

            outFile << '\n';

            // Clear the deque
            numArray.clear();
        }
    }
    else
    {
        cout << "The was an error in opening the necessary files" << endl;
    }

    // Close the input and output files
    inFile.close();
    outFile.close();

    return 0;
}