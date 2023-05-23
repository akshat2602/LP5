#include <bits/stdc++.h>
#include <iostream>
#include <omp.h>
using namespace std;

class Graph
{
public:
    int vertices = 6;
    int edges = 5;
    vector<vector<int>> graph = {{1}, {0, 2, 3}, {1, 4, 5}, {1, 4}, {2, 3}, {2}};
    vector<bool> visited;

    void add_edge(int i, int j)
    {
        graph[i].push_back(j);
        graph[j].push_back(i);
    }

    void print_graph()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << "->";
            for (auto j = graph[i].begin(); j != graph[i].end(); j++)
            {
                cout << *j << " ";
            }
            cout << endl;
        }
    }

    void initialize_visited()
    {
        visited.assign(vertices, false);
    }

    void dfs(int i)
    {
        stack<int> s;
        s.push(i);
        visited[i] = true;

        while (s.empty() != true)
        {
            int current = s.top();
            cout << current << " ";
            s.pop();

            for (auto j = graph[current].begin(); j != graph[current].end(); j++)
            {
                if (visited[*j] == false)
                {
                    s.push(*j);
                    visited[*j] = true;
                }
            }
        }
    }

    void bfs(int i)
    {
        queue<int> s;
        s.push(i);
        visited[i] = true;

        while (s.empty() != true)
        {
            int current = s.front();
            cout << current << " ";
            s.pop();

            for (auto j = graph[current].begin(); j != graph[current].end(); j++)
            {
                if (visited[*j] == false)
                {
                    s.push(*j);
                    visited[*j] = true;
                }
            }
        }
    }

    void parallel_dfs(int i)
    {
        stack<int> s;
        s.push(i);
        visited[i] = true;

        while (s.empty() != true)
        {
            int current = s.top();
            cout << current << " ";

#pragma omp critical
            s.pop();

#pragma omp parallel for
            for (auto j = graph[current].begin(); j != graph[current].end(); j++)
            {
                if (visited[*j] == false)
                {
#pragma omp critical
                    {
                        s.push(*j);
                        visited[*j] = true;
                    }
                }
            }
        }
    }

    void parallel_bfs(int i)
    {
        queue<int> s;
        s.push(i);
        visited[i] = true;

        while (s.empty() != true)
        {
            int current = s.front();
            cout << current << " ";

#pragma omp critical
            s.pop();

#pragma omp parallel for
            for (auto j = graph[current].begin(); j != graph[current].end(); j++)
            {
                if (visited[*j] == false)
                {
#pragma omp critical
                    {
                        s.push(*j);
                        visited[*j] = true;
                    }
                }
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    Graph g;
    cout << "Adjacency list: ";
    g.print_graph();
    g.initialize_visited();

    cout << endl;
    cout << "Depth First Search: ";
    auto start = chrono::high_resolution_clock::now();
    g.dfs(0);
    cout << endl;
    auto end = chrono::high_resolution_clock::now();
    cout << "Time taken:" << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds " << endl;

    cout << "Parallel Depth First Search: ";
    start = chrono::high_resolution_clock::now();
    g.initialize_visited();
    g.parallel_dfs(0);
    cout << endl;
    end = chrono::high_resolution_clock::now();
    cout << "Time taken:" << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds " << endl;

    cout << "Breadth First Search: ";
    start = chrono::high_resolution_clock::now();
    g.initialize_visited();
    g.bfs(0);
    cout << endl;
    end = chrono::high_resolution_clock::now();
    cout << "Time taken:" << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds " << endl;

    cout << "Parallel Breadth First Search: ";
    start = chrono::high_resolution_clock::now();
    g.initialize_visited();
    g.parallel_bfs(0);
    cout << endl;
    end = chrono::high_resolution_clock::now();
    cout << "Time taken:" << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds " << endl;
}