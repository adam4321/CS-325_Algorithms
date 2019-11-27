/************************************************************
**  Author:       Adam Wright
**  Date:         11/4/19
**  Description:  Implementation of a program in c++ which 
**                takes in a text file from the command line
**                and returns whether wrestling matches are
**                possible, and if so, which pairings.
************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;
using std::queue;
using std::map;


struct wrestler
{
	string name;
	string role;
	bool visited;
};

const string NOT_SET = "NOT_SET";

/******************************************************************************
**  Description: Implementation of Breadth first search to check if the set of 
**               rivalries is bipartite and thus possible. The first vertex is
**               set as a babyface and then each neighbor is set to the opposite
**               role, starting with a heel, until all vertices have been searched.
**               If any neighbor is already set to the same role, then the graph 
**               is not bipartite and the function returns false. The function
**               takes a vector of vectors, a map of the wrestlers and their index,
**               an array for the babyface output, and and array for the heel ouput
**               as references. This url https://www.geeksforgeeks.org/bipartite-graph/
**               on the website Geeks for Geeks was viewed in putting this 
**               function together.
*******************************************************************************/
bool graph_BFS(vector< vector <wrestler*> > &graph, map<string,int> data, vector<string> &babyfaces, vector<string> &heels)
{
    
    string babyface = "babyface";
    string heel = "heel";
	queue< vector <wrestler*> > bfs_queue;

	// Search all unvisited vertices
	for (unsigned i = 0; i < graph.size(); i++)
	{
		if (!graph[i][0]->visited)
		{
			// Set first vertex as a babyface and add to babyfaces and queue
			graph[i][0]->role = babyface;
			babyfaces.push_back(graph[i][0]->name);
			bfs_queue.push(graph[i]);

			while (!bfs_queue.empty())
			{
				// Pull the current vertex from the queue
				vector<wrestler*> cur_node = bfs_queue.front();
				cur_node[0]->visited = true;
				bfs_queue.pop();

				// Search the vertex's neighbors
				for (unsigned j = 1; j < cur_node.size(); j++)
				{
					// Check if the vertx has been visited
					if (cur_node[j]->visited == false)
					{
                        // Set babyfaces's neighbor to heel and add to heels
						if (cur_node[j]->role == NOT_SET && cur_node[0]->role == babyface)
						{
							cur_node[j]->role = heel;
							heels.push_back(cur_node[j]->name);
						}

                        // Set heel's neighbor to babyface and add to babyfaces
						else if (cur_node[j]->role == NOT_SET && cur_node[0]->role == heel)
						{
							cur_node[j]->role = babyface;
							babyfaces.push_back(cur_node[j]->name);
						}

                        // End and return false if not Bipartite
						else if (cur_node[j]->role == cur_node[0]->role)
						{
							return false;
						}

						// Add vertex's neighbor to the queue
						bfs_queue.push(graph[data[cur_node[j]->name]]);
					}
				}
			}
		}
	}

    // If the search doesn't fail then return true
    return true;
}


int main(int argc, char* argv[])
{
    cout << endl;
    cout << "**************************************" << endl;
    cout << "*        Wrestler Match Maker        *"<< endl;
    cout << "**************************************" << endl;
    cout << endl;


	if (argc != 2)
	{
		cout << "Please enter the test file as a Cli argument" << endl;
	}
    else
    {
        ifstream inFile;
        string fileName;
        fileName = argv[1];

        // Open the test file
        inFile.open(fileName);

        // Continue if the data file (act.txt) is open
        if (inFile.is_open())
        {
            int size;                // Num wrestlers
            int edges;               // Num rivalries
            bool possible;           // Whether the graph is bipartite
            string temp_name;        // Input wrestler name
            vector<string> names;    // Wrestler names
            vector<string> babyfaces;  // Output babyfaces
            vector<string> heels;      // Output heels
            map<string, int> data;   // Wrestler hash for name and index
            

            // Pull wrestlers from file
            inFile >> size;
            vector< vector < wrestler*> > graph(size);  // Create the graph

            for (int i = 0; i < size; i++)
            {
                inFile >> temp_name;
                data[temp_name] = i;        // Hash wrestler and index
                names.push_back(temp_name);
            }

            // Create the wrestler vertices
            for (unsigned i = 0; i < graph.size(); i++)
            {
                graph[i].push_back(new wrestler);

                // Name the vertices and set their attributes
                graph[i][0]->name = names[i]; 
                graph[i][0]->role = NOT_SET; 
                graph[i][0]->visited = false;
            }

            // Edges set to the number of rivalries 
            inFile >> edges;

            // Pull the rivalries and set as graph's edges
            for (int i = 0; i < edges; i++)
            {
                string rival_one;
                string rival_two;
                
                inFile >> rival_one;
                inFile >> rival_two;
                
                // Creating the connections of the graph
                int idx_riv_1 = data[rival_one];
                int idx_riv_2 = data[rival_two];
                 
                graph[idx_riv_1].push_back(graph[idx_riv_2][0]);
                graph[idx_riv_2].push_back(graph[idx_riv_1][0]);
            }


            // Close file then call BFS and capture bool
            inFile.close();
            possible = graph_BFS(graph, data, babyfaces, heels);
            
            // Print results to console
            if (possible)
            {
                cout << "Yes, possible" << endl << endl;
                cout << "Babyfaces: ";
                for (unsigned i = 0; i < babyfaces.size(); i++)
                {
                    cout << babyfaces[i] << " ";
                }
                cout << endl;

                cout << "Heels: "; 
                for (unsigned i = 0; i < heels.size(); i++)
                {
                    cout << heels[i] << " ";
                }
                cout << endl;
            }
            else
            {
                cout << "Impossible" << endl;
            }

            // Free wrestler structs
            for (unsigned i = 0; i < graph.size(); i++)
            {
                delete graph[i][0];
            }
        }
        else
        {
            cout << "Error, the input file isn't open" << endl;
            cout << "Enter the test file name along with the program name" << endl;
        }
    }

    cout << endl;
	return 0;
}