/************************************************************************
** Program name:   last_to_l HW-4 CS325
** Author:         Adam Wright
** Date:           10/22/2019
** Description:    Program that implements an alteration of CLRS first
**                 to finish which instead finds the last activity to
**                 start. It parses the data in act.txt for the activity
**                 data. It uses the implementation of mergesort from HW1
**                 for sorting. 
**                 act.txt:
**                     - single digit = the number of activities to follow
**                     - 3 digits = activity number, l, finish time
************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::deque;
using std::ifstream;
using std::istringstream;


/*********************************************************************
** Description:   Defintion of the merge function which sorts and
**                merges the subarrays of integers as a helper function.
**                It takes a 2d vector, leftmost index, the middle index
**                and the right index which is arraylength - 1 as 
**                arguments. The website Geeks for Geeks at this Url
**                https://www.geeksforgeeks.org/merge-sort/ was viewed
**                to help put the algorithm together.
*********************************************************************/
void merge(vector < vector<int> > &arr, int l, int m, int r)
{
	int x = l;
	int y = m;

	// Create temporary 2D vector
	vector < vector<int> > temp(r, vector<int>(arr[l].size()));
	int index = l;

	while (x < m && y < r)
	{
		// Copy data to temp array based on second row element
		if (arr[x][1] <= arr[y][1])
		{
			temp[index] = arr[y];
			index++;
			y++;
		}
		else if (arr[y][1] <= arr[x][1])
		{
			temp[index] = arr[x];
			index++;
			x++;
		}
	}

    // Copy the remaining elements of x
	while (x < m)
	{
		temp[index] = arr[x];
		index++;
		x++;
	}

    // Copy the remaining elements of y
	while (y < r)
	{
		temp[index] = arr[y];
		index++;
		y++;
	}

	for (x = l; x < r; x++)
	{
		arr[x] = temp[x];
	}
}

/*********************************************************************
** Description:   Defintion of mergeSort function which sorts an
**                array of integers. It takes a 2d vector, left index,
**                and the right index which is length - 1 as arguments.
**                The website Geeks for Geeks at this Url
**                https://www.geeksforgeeks.org/merge-sort/ was viewed
**                to help put the algorithm together.
*********************************************************************/
void mergeSort(vector < vector<int> > &arr, int l, int r)
{
	if (l + 1 == r)
	{
		return;
	}

	int m = (l + r) / 2;

	// Sort 1st and 2nd half
	mergeSort(arr, l, m);
	mergeSort(arr, m, r);

	merge(arr, l, m, r);
}

/*********************************************************************
** Description:   Defintion of greedy last to start function which 
**                selects the most activities. It takes a 2d vector,
**                an output deque, and the number of vector rows.
**                The website Geeks for Geeks at this Url
**                https://www.geeksforgeeks.org/activity-selection-
**                problem-greedy-algo-1/ was viewed to help put
**                the algorithm together.
*********************************************************************/
void last_start(vector< vector<int> > &sets, deque<int> &activities, int n)
{
    // The last activity is always selected
    activities.push_front(sets[0][0]);

    // Holder for current last activity
    int holder = sets[0][1];

    for (int i = 0; i < n-1; i++)
    {
        if (sets[i+1][2] <= holder)
        {
            activities.push_front(sets[i+1][0]);
            holder = sets[i+1][1];
        }
    }
}


int main()
{
    // Declare the needed containers
    int test_case = 1;
    int num_sets;
    int num;

    // Open the input file
    ifstream inFile;
    inFile.open("act.txt");

    cout << endl;
    cout << "**************************************" << endl;
    cout << "*  Last to Start: Activity Selector  *"<< endl;
    cout << "**************************************" << endl;


    // Continue if the data file (act.txt) is open
    if (inFile.is_open())
    {
        while (!inFile.eof())
        {
            inFile >> num_sets;

            // Vector rows are num sets and columns are each set
            vector< vector<int> > sets(num_sets, vector<int> (3));

            // Output vector
            deque<int> activities;

            // Loop through the current num of sets
            for (int i = 0; i < num_sets; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    inFile >> num;
                    sets[i][j] = num;
                }
            }


            // Sort the start column in descending order(sets[row][1])
            mergeSort(sets, 0, sets.size());

            // Greedy algorithm to 
            last_start(sets, activities, num_sets);


            cout << endl;
            cout << "Set " << test_case << endl;
            cout << "Number of activities selected = " << activities.size() << endl;
            cout << "Activities: ";


            // Print the ideal activities
            for (unsigned i = 0; i < activities.size(); i++)
            {
                cout << activities[i] << ' ';
            }

            // Increment the test case
            test_case++;

            // Clear the output array for the next set
            activities.clear();

            cout << endl;
        }
    }
    else
    {
        cout << "Error, the input file isn't open." << endl;
    }

    // Close the input file
    inFile.close();

    cout << endl;

    return 0;
}