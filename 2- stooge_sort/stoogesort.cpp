/************************************************************************
** Program name:   insertsort HW-2 CS325
** Author:         Adam Wright
** Date:           10/10/2019
** Description:    Program that implements stoogesort by taking in data
**                 from a text file called data.txt and outputting the 
**                 sorted data to a file called insert.txt. This sorting
**                 algorithm is a slow recursive algorithm.
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
    // Open the input file data.txt
    ifstream inFile;
    inFile.open("data.txt");

    // Open the output file stooge.txt   
    ofstream outFile;
    outFile.open("stooge.txt");

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
            stoogeSort(numArray, 0, arrSize - 1);


            // Print out the sorted values to stooge.txt
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