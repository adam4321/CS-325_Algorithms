/******************************************************************************
**  Author:       Adam Wright
**  Dage:         11/26/2019
**  Description:  Program that reads from a text file and then tests the 
**                runtime of three different algorithms for solving the bin
**                packing problem.
******************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <ctime>
#include <chrono>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::sort;
using std::greater;
using namespace std::chrono;


/*********************************************************************
** Description:   Defintion of first fit function which takes three
**                arguments. A vector of weights as integers and two 
**                ints with the first being the number of items in 
**                the vector and the last being the capacity of the
**                bin for the current test case.The website Geeks for
**                Geeks at this Url https://www.geeksforgeeks.org/
**                bin-packing-problem-minimize-number-of-used-bins/
**                was used to help put the algorithm together.
*********************************************************************/
int first_fit(vector<int> weight, int n, int c) 
{ 
    // Count of bins
    int count = 0; 
  
    // Create an array to store remaining space in bins 
    vector<int> bin_rem(n); 
  
    // Place items one by one 
    for (int i = 0; i < n; i++) { 
        // Find the first bin that can accommodate weight[i] 
        int j; 
        for (j = 0; j < count; j++) { 
            if (bin_rem[j] >= weight[i]) { 
                bin_rem[j] = bin_rem[j] - weight[i]; 
                break; 
            } 
        } 
  
        // If no bin could accommodate weight[i] 
        if (j == count) { 
            bin_rem[count] = c - weight[i]; 
            count++; 
        } 
    } 
    return count; 
} 


/*********************************************************************
** Description:   Defintion of 1st fit descending function which takes
**                3 arguments. A vector of weights as integers and two 
**                ints with the first being the number of items in 
**                the vector and the last being the capacity of the
**                bin for the current test case.The website Geeks for
**                Geeks at this Url https://www.geeksforgeeks.org/
**                bin-packing-problem-minimize-number-of-used-bins/
**                was used to help put the algorithm together.
*********************************************************************/
int first_fit_descending(vector<int> weight, int n, int c)
{
    // First sort all weights in decreasing order 
    sort(weight.begin(), weight.begin() + n, greater<int>()); 
  
    // Call first fit on sorted list
    return first_fit(weight, n, c);
}


/*********************************************************************
** Description:   Defintion of best fit function which takes three
**                arguments. A vector of weights as integers and two 
**                ints with the first being the number of items in 
**                the vector and the last being the capacity of the
**                bin for the current test case.The website Geeks for
**                Geeks at this Url https://www.geeksforgeeks.org/
**                bin-packing-problem-minimize-number-of-used-bins/
**                was used to help put the algorithm together.
*********************************************************************/
int best_fit(vector<int> weight, int n, int c) 
{ 
    // Count of bins
    int count = 0; 
  
    // Create an array to store remaining space in bins 
    vector<int> bin_rem(n); 
  
    // Place items one by one 
    for (int i = 0; i < n; i++)
    { 
        // Find the best bin that can accomodate weight[i] 
        int j; 
  
        // Initialize minimum space left and index of best bin 
        int min = c + 1, bi = 0; 
  
        for (j = 0; j < count; j++)
        { 
            if (bin_rem[j] >= weight[i] && bin_rem[j] - weight[i] < min) { 
                bi = j; 
                min = bin_rem[j] - weight[i]; 
            } 
        } 
  
        // If no bin can accommodate weight[i] then create a new bin 
        if (min == c + 1)
        { 
            bin_rem[count] = c - weight[i]; 
            count++; 
        } 
        else
        { 
            // Assign the item to best bin 
            bin_rem[bi] -= weight[i];
        } 
    } 
    return count; 
} 


/*********************************************************************
** Description:   Main function reads from the input file bin.txt
*********************************************************************/
int main()
{
    // Open the input file
    ifstream in_file;
    in_file.open("bin.txt");

    cout << endl;
    cout << "*******************************************" << endl;
    cout << "*  Three greedy aproximations for          " << endl;
    cout << "*  solving the bin packing problem         " << endl;
    cout << "**************************************" << endl << endl;

    if (in_file.is_open())
    {
        int num_tests;
        int capacity;
        int num_items;
        int item_weight;
        int test_count = 1;
        vector<int> item_weight_vector;

        while (in_file >> num_tests)
        {
            for (int i = 0; i < num_tests; i++)
            {
                in_file >> capacity;
                in_file >> num_items;

                for (int i = 0; i < num_items; i++)
                {
                    in_file >> item_weight;
                    item_weight_vector.push_back(item_weight);
                }

                // Start time first fit
                auto start = high_resolution_clock::now();
                int ff = first_fit(item_weight_vector, num_items, capacity);

                // Stop time and calculate duration first fit
                auto stop = high_resolution_clock::now();
                auto run_time = duration_cast<microseconds>(stop - start);
                // Convert microseconds to seconds
                auto ff_time = run_time.count() * 0.000001;

                // Start time first fit descending
                start = high_resolution_clock::now();
                int ffd = first_fit_descending(item_weight_vector, num_items, capacity);

                // Stop time and calculate duration first fit descenting
                stop = high_resolution_clock::now();
                run_time = duration_cast<microseconds>(stop - start);
                auto ffd_time = run_time.count() * 0.000001;

                // Start time best fit
                start = high_resolution_clock::now();
                int bf = best_fit(item_weight_vector, num_items, capacity);

                // Stop time and calculate duration best fit
                stop = high_resolution_clock::now();
                run_time = duration_cast<microseconds>(stop - start);
                auto bf_time = run_time.count() * 0.000001;
                

                cout << "Test Case: " << test_count << " ";
                cout << "First Fit: " << ff << ", " <<  ff_time << " sec. ";
                cout << "First Fit Decreasing: " << ffd << ", " <<  ffd_time << " sec. ";
                cout << "Best Fit: " << bf << ", " <<  bf_time << " sec.";
                cout << endl;

                // Clear the vector and increment the test count
                item_weight_vector.clear();
                test_count++;
            }
        }
    }
    else
    {
        cout << "Error, the input file isn't open." << endl;
    }

    // Close the input file
    in_file.close();

    cout << endl;
    cout << "*****************************";
    cout << endl << endl;

    return 0;
}