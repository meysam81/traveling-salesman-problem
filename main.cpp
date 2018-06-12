#include <iostream>
#include <math.h>
#include <bits/stdc++.h>
#include <set>
#include <vector>



using namespace std;



int tsp();
int cost(int, set<int>);


vector<vector<int>> adj;
const int v = 4;


int main()
{
    adj = vector<vector<int>>({ { 0, 20, 42, 35 },
                                { 20, 0, 30, 34 },
                                { 42, 30, 0, 12 },
                                { 35, 34, 12, 0 }});
    cout << "minimum hamiltonian cycle (tsp) is: " << tsp () << endl;
}
int tsp()
{
    int min = INT16_MAX;
    set<int> middles;


    for (int i = 1; i < v; ++i)
        middles.insert(i);


    for (int j = 1; j < v; ++j)
    {
        int hold = adj[0][j];
        hold += cost(j, middles);
        if (min > hold)
            min = hold;
    }

    return min;
}

int cost (int position, set<int> s)
{
    if (s.size() == 0)
        return adj[position][0];
    else
    {
        int min = INT16_MAX;

        set<int>::const_iterator f1 = s.find(position);
        if (f1 != s.end())
            s.erase(f1);


        for (set<int>::const_iterator ii = s.begin(); ii != s.end(); ++ii)
        {
            int i = *ii;

            set<int> tmp = s;
            set<int>::const_iterator f2 = tmp.find(i);
            if (f2 != tmp.end())
                tmp.erase(f2);

            int hold = adj[position][i];
            hold += cost (i, tmp);

            if (min > hold)
                min = hold;

        }
        return min;
    }
}
