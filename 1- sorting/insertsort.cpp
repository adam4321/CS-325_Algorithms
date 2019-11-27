/************************************************************************
** Program name:   insertsort HW-1 CS325
** Author:         Adam Wright
** Date:           10/4/2019
** Description:    Program that implements insertionsort by taking in data
**                 from a text file called data.txt and outputting the 
**                 sorted data to a file called insert.txt
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
** Description:   Defintion of insertionSort function which sorts an
**                array of integers. It takes an array and the array
**                length as arguments. The website Geeks for Geeks at
**                this Url https://www.geeksforgeeks.org/insertion-sort/
**                was used to help put this algorithm together.
*********************************************************************/
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
    // Open the input file data.txt
    ifstream inFile;
    inFile.open("data.txt");

    // Open the output file insert.txt   
    ofstream outFile;
    outFile.open("insert.txt");

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
            insertionSort(numArray, arrSize);


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