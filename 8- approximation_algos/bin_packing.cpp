/******************************************************************************
**  Author:       Adam Wright 
**  Description:  
******************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::endl;
using std::greater;
using std::ifstream;
using std::vector;

vector<int> item_Weight_Vector;


/*********************************************************************
** Description:   Defintion of 
*********************************************************************/
int firstFit(int capacity, vector<int> item_Weights)
{
    vector<int> binCapLeft;
    binCapLeft.push_back(capacity);

    for (int i = 0; i < item_Weights.size(); i++)
    {
        bool canFit = true;

        for (int j = 0; j < binCapLeft.size(); j++)
        {
            if (item_Weights[i] <= binCapLeft[j])
            {
                binCapLeft[j] -= item_Weights[i];
                canFit = false;
                break;
            }
        }

        if (canFit == true)
        {
            binCapLeft.push_back(capacity);
            binCapLeft[binCapLeft.size() - 1] -= item_Weights[i];
        }
    }

    return binCapLeft.size();
}


/*********************************************************************
** Description:   Defintion of 
*********************************************************************/
int firstFitD(int capacity, vector<int> item_Weights)
{
    sort(item_Weights.begin(), item_Weights.end(), greater<int>());
    int ffd = firstFit(capacity, item_Weights);
    return ffd;
}


/*********************************************************************
** Description:   Defintion of 
*********************************************************************/
int bestFit(int capacity, vector<int> item_Weights)
{
    vector<int> binCapLeft;
    binCapLeft.push_back(capacity);
    vector<int> bestbin;

    for (int i = 0; i < item_Weights.size(); i++)
    {
        bool cantFit = true;

        for (int j = 0; j < binCapLeft.size(); j++)
        {
            while (item_Weights[i] <= binCapLeft[j])
            {
                bestbin.push_back(j);
                i++;
            }

            if (bestbin.size() >= 1)
            {
                int k = max(bestbin.value);
                binCapLeft[k] -= item_Weights[i];
                cantFit = false;
                break;
            }
        }

        if (cantFit == true)
        {
            binCapLeft.push_back(capacity);
            binCapLeft[binCapLeft.size() - 1] -= item_Weights[i];
        }
    }

    return binCapLeft.size();
}


/*********************************************************************
** Description:   Main 
*********************************************************************/
int main()
{
    // Open the input file
    ifstream inFile;
    inFile.open("bin.txt");

    cout << endl;
    cout << "**************************************" << endl;
    cout << "*  Last to Start: Activity Selector  *"<< endl;
    cout << "**************************************" << endl;

    if (!inFile)
    {
        cout << "File does not exist" << endl;
    }


    int data;
    int num_of_test;
    int capacity, item_weight = 0;
    int totalItems = 0;
    int testCasesCount = 0;

    while (inFile >> num_of_test)
    {
        for (int i = 0; i < num_of_test; i++)
        {
            inFile >> capacity;
            inFile >> totalItems;

            for (int i = 0; i < totalItems; i++)
            {
                inFile >> item_weight;

                item_Weight_Vector.push_back(item_weight);
            }

            testCasesCount++;
            int ff = firstFit(capacity, item_Weight_Vector);
            int ffd = firstFitD(capacity, item_Weight_Vector);
            item_Weight_Vector.clear();

            cout << "Test Case: "
                 << testCasesCount
                 << " First Fit: "
                 << ff
                 << ", First Fit Decreasing: "
                 << ffd
                 << endl;
        }
    }

    // Close the input file
    inFile.close();

    cout << endl;
    
    return 0;
}