/************************************************************************
** Program name:   insertsort HW-3 CS325
** Author:         Adam Wright
** Date:           10/16/2019
** Description:    Program that implements a shopping spree for a set of
**                 families. The values are used are read from the input
**                 file shopping.txt 
**                 (first line is # of test cases then remaining are tests)
**                 (next line the # of following lines for items)
**                 (n number of lines of pairs of price and weight tuples)
**                 (integer for number of family members)
**                 (n number of lines for max weight carried by ith member)
************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::sort;


/*********************************************************************
** Description:   Defintion of a maximum comparator function which
**                takes two integers as arguments and returns the 
**                larger integer.
*********************************************************************/
int maximum(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}


/*********************************************************************
** Description:   Defintion of ideal items dynamic programming
**                algorithm which is an implementation of a solution
**                to the knapsack problem. It takes an array of weights
**                an array of prices, a number of items the person can
**                carry, the max weight a person can carry, and an
**                output vector by reference for the persons ideal item
**                numbers that they should choose. It returns the max
**                price as an int representing the ideal set of items.
**                This website Geeks for Geeks at this url 
**             https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
**                was viewed in putting together this algorithm.
*********************************************************************/
int ideal_items(int weights[], int prices[], int num_items, int max_weight, vector<int>& fam_vec)
{
    // Vector of vectors for family member's ideal items
    vector< vector<int> > shop_table(num_items+1, vector<int> (max_weight+1));

    // Run for current number of items
    for (int i = 0; i <= num_items; i++)
    {
        // Run until family member's max carry weight is reached 
        for (int j = 0; j <= max_weight; j++)
        {
            // If there are no items or they can't carry any weight
            if (i == 0 ||  j == 0)
            {
                shop_table[i][j] = 0;
            }
            // The current family member has weight remaining to carry
            else if (weights[i-1] <= j)
            {
                shop_table[i][j] = maximum(prices[i-1] + shop_table[i-1][j-weights[i-1]], shop_table[i-1][j]);
            }
            // Enter the previous item
            else
            {
                shop_table[i][j] = shop_table[i-1][j];
            }
        }
    }

    // Enter the current family member's results into the vector
    int result = shop_table[num_items][max_weight];
    int weight = max_weight;

    for (int i = num_items; i > 0 && result > 0; i--)
    {
        if (result == shop_table[i-1][weight])
        {
            continue;
        }
        else
        {
            fam_vec.push_back(i);

            result = result - prices[i-1];
            weight = weight - weights[i-1];
        }
    }

    // Return the best total price for the current family member
    return shop_table[num_items][max_weight];;
}


int main()
{
    // Open the input file shopping.txt
    ifstream inFile;
    inFile.open("shopping.txt");

    // Open the output file results.txt   
    ofstream outFile;
    outFile.open("results.txt");

    // Declare the needed containers
    int num_test_cases;
    int num_items;
    int family_size;
    int max_weight;
    int prices[100];
    int weights[100];
    

    // Continue if the input and output files open
    if (inFile.is_open() && outFile.is_open())
    {
        // First line of shopping.txt is # of test cases
        inFile >> num_test_cases;

        // Run for the given number of test cases
        for (int i = 0; i < num_test_cases; i++)
        {
            // Next line the number of items
            inFile >> num_items;

            // Read in item values for current test case
            for (int j = 0; j < num_items; j++)
            {
                inFile >> prices[j];
                inFile >> weights[j];
            }

            // Prepare the family variables for current test case
            inFile >> family_size;
            int max_price = 0;
            vector< vector<int> > fam_vec(100);

            // Call the algorithm for each family member
            for (int k = 0; k < family_size; k++)
            {
                inFile >> max_weight;
                max_price = max_price + ideal_items(weights, prices, num_items, max_weight, fam_vec[k]);
            }


            // Output the current test case results to results.txt 
            outFile << "Test Case " << i+1 << endl;
            outFile << "Total Price " << max_price << endl;
            outFile << "Member Items" << endl;
            
            // Print items for each family member
            for (int l = 0; l < family_size; l++)
            {
                // Sort the ideal items in ascending order
                sort(fam_vec[l].begin(), fam_vec[l].end());
                outFile << "    " << l + 1 << ": ";
                
                // Output the ideal items
                for (unsigned m = 0; m < fam_vec[l].size(); m++)
                {
                    outFile << fam_vec[l][m] << " ";
                }
                outFile << endl;
            }
            outFile << endl;

            // Clear the items vector for the next test case
            fam_vec.clear();
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