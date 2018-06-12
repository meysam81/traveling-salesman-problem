#include <iostream> // cout, endl
#include <bits/stdc++.h> // INT16_MAX
#include <set> // standard c++ std::set
#include <vector> // standard c++ std::vector
#include <iomanip> // setw


using namespace std;



int tsp(); // main algorithm
int cost(int, set<int>); // compute cost for the tsp() function

vector<vector<int>> adj; // adjacency matrix to store edge weights
const int v = 4; // number of nodes
vector<int> minimumPath(v + 1, -1); // to store the path
int counter = 0;

int main() // no explanation needed here!
{

    // to store adjacency matrix, we use constructor of vector as in:
    // vector < value_type > (initializer_list < value_type > __I)
    adj = vector<vector<int>>({ { 0, 10, 15, 20 },
                                { 10, 0, 35, 25 },
                                { 15, 35, 0, 30 },
                                { 20, 25, 30, 0 } });
    cout << "minimum hamiltonian cycle (tsp) is: " << tsp () << endl;
    for (auto& i : minimumPath)
        cout << i << setw(3);
    cout << endl;
}


int tsp()
{
    // consider infinity as the current minimum, and reduce it if possible
    // of course it is possible because our graph is a complete undirected weighted network
    int min = INT16_MAX;

    // a set to store unvisited nodes
    set<int> middles;

    // we start from index 0, so we are not going to add it to unvisited set
    for (int i = 1; i < v; ++i)
        middles.insert(i);

    // every node other than 0 is passed to the algorithm so that it computes the minimum tour
    // and when it returns we add that to:
    //     1. STARTING EDGE from node 0 to the node that starts the minimum tour
    //     2. ENDING EDGE from the last node in the tsp_tour to node zero
    //        because we start from zero and come back to it when it is done
    //        so we have a hamiltonian cycle starting from node zero
    minimumPath[0] = 0; // we start from zero
    counter++;
    for (int j = 1; j < v; ++j)
    {
        int hold = adj[0][j]; // STARTING EDGE

        hold += cost(j, middles); // the minimum tour from a node other than zero to a node before zero
        if (min > hold) // store minimum tour if we haven't stored it already
            min = hold;
    }
    minimumPath[v] = 0;
    counter++;


    return min; // final result
}

int cost (int position, // "position" is the starting node of the minimum tour
          set<int> s) // the subset containing the unvisited nodes
{
    if (s.size() == 0) // if we have visited all the nodes in the network
    {
        minimumPath[(v - 1) - s.size()] = position;
        return adj[position][0]; // ENDING EDGE
    }
    else
    {
        int min = INT16_MAX; // an upper bound, that makes every other tour in the network a lesser cost

        // remove our current node from unvisited nodes
        set<int>::const_iterator f1 = s.find(position);
        if (f1 != s.end())
            s.erase(f1);


        // for every unvisited network
        for (set<int>::const_iterator ii = s.begin(); ii != s.end(); ++ii)
        {
            int i = *ii; // store the value of the current node for example node number 1

            // again remove the next node from unvisited nodes
            set<int> tmp = s;
            set<int>::const_iterator f2 = tmp.find(i);
            if (f2 != tmp.end())
                tmp.erase(f2);



            int hold = adj[position][i]; // the next tour starts from i, so store the edge from "position" to "i"
            hold += cost (i, tmp); // compute the minimum tsp_tour recursivel

            if (min > hold) // if we do not have a lesser value of the current computation, save it
            {
                min = hold;
            }

        }
        minimumPath[(v - 1) - (v - 1 - s.size())] = position;
        return min;
    }
}
