/******************************************************************************
**  Author:       Adam Wright 
**  Description:  This project reads 
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
** Description:   Defintion of 
*********************************************************************/
int first_fit(vector<int> &weight, int n, int c) 
{ 
    // Initialize result (Count of bins) 
    int res = 0; 
  
    // Create an array to store remaining space in bins 
    // there can be at most n bins 
    vector<int> bin_rem(n); 
  
    // Place items one by one 
    for (int i = 0; i < n; i++) { 
        // Find the first bin that can accommodate weight[i] 
        int j; 
        for (j = 0; j < res; j++) { 
            if (bin_rem[j] >= weight[i]) { 
                bin_rem[j] = bin_rem[j] - weight[i]; 
                break; 
            } 
        } 
  
        // If no bin could accommodate weight[i] 
        if (j == res) { 
            bin_rem[res] = c - weight[i]; 
            res++; 
        } 
    } 
    return res; 
} 


/*********************************************************************
** Description:   Defintion of 
*********************************************************************/
int first_fit_descending(vector<int> &weight, int n, int c)
{
    // First sort all weights in decreasing order 
    sort(weight.begin(), weight.begin() + n, greater<int>()); 
  
    // Now call first fit for sorted items 
    return first_fit(weight, n, c);
}


/*********************************************************************
** Description:   Defintion of 
*********************************************************************/
int best_fit(vector<int> &weight, int n, int c) 
{ 
    // Initialize result (Count of bins) 
    int res = 0; 
  
    // Create an array to store remaining space in bins 
    // there can be at most n bins 
    vector<int> bin_rem(n); 
  
    // Place items one by one 
    for (int i = 0; i < n; i++)
    { 
        // Find the best bin that can accomodate weight[i] 
        int j; 
  
        // Initialize minimum space left and index of best bin 
        int min = c + 1, bi = 0; 
  
        for (j = 0; j < res; j++)
        { 
            if (bin_rem[j] >= weight[i] && bin_rem[j] - weight[i] < min) { 
                bi = j; 
                min = bin_rem[j] - weight[i]; 
            } 
        } 
  
        // If no bin could accommodate weight[i] then create a new bin 
        if (min == c + 1)
        { 
            bin_rem[res] = c - weight[i]; 
            res++; 
        } 
        else
        { 
            // Assign the item to best bin 
            bin_rem[bi] -= weight[i];
        } 
    } 
    return res; 
} 


/*********************************************************************
** Description:   Main function reads from the input file bin.txt
*********************************************************************/
int main()
{
    // Open the input file
    ifstream inFile;
    inFile.open("bin.txt");

    cout << endl;
    cout << "*******************************************" << endl;
    cout << "*  Three greedy aproximations for          " << endl;
    cout << "*  solving the bin packing problem         " << endl;
    cout << "**************************************" << endl << endl;

    if (inFile.is_open())
    {
        int num_tests;
        int capacity;
        int num_items;
        int item_weight;
        int test_count = 1;
        vector<int> item_weight_vector;

        while (inFile >> num_tests)
        {
            for (int i = 0; i < num_tests; i++)
            {
                inFile >> capacity;
                inFile >> num_items;

                for (int i = 0; i < num_items; i++)
                {
                    inFile >> item_weight;
                    item_weight_vector.push_back(item_weight);
                }

                // Start time first fit
                auto start = high_resolution_clock::now();
                int ff = first_fit(item_weight_vector, num_items, capacity);

                // Stop time and calculate duration first fit
                auto stop = high_resolution_clock::now();
                auto run_time = duration_cast<microseconds>(stop - start);
                // Convert microseconds to seconds
                int ff_time = run_time.count() * 0.000001;

                // Start time first fit descending
                start = high_resolution_clock::now();
                int ffd = first_fit_descending(item_weight_vector, num_items, capacity);

                // Stop time and calculate duration first fit descenting
                stop = high_resolution_clock::now();
                run_time = duration_cast<microseconds>(stop - start);
                int ffd_time = run_time.count() * 0.000001;

                // Start time best fit
                start = high_resolution_clock::now();
                int bf = best_fit(item_weight_vector, num_items, capacity);

                // Stop time and calculate duration best fit
                stop = high_resolution_clock::now();
                run_time = duration_cast<microseconds>(stop - start);
                int bf_time = run_time.count() * 0.000001;
                

                cout << "Test Case: " << test_count << " ";
                cout << "First Fit: " << ff << ", " <<  ff_time << "sec. ";
                cout << "First Fit Decreasing: " << ffd << ", " <<  ffd_time << "sec. ";
                cout << "Best Fit: " << bf << ", " <<  bf_time << "sec.";
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
    inFile.close();

    cout << endl;

    return 0;
}