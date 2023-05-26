#include <bits/stdc++.h>
using namespace std;

class Task
{
public:
    void solve()
    {   
        read_input();
        int resultA = startA(inDegree, datasets);
        int resultB = startB(inDegree, datasets);

        if(resultA < resultB)
            print_output(resultA);
        else
            print_output(resultB);

    }

private:
    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // n = numar de noduri, m = numar de muchii/arce
    int n, m;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    vector<int> adj[NMAX];
    vector<int> inDegree; // numarul de muchii de intrare pentru fiecare nod
    vector<int> datasets; // dataset[node] = setul de date al nodului node

    // citire date de intrare
    void read_input()
    {
        ifstream fin("supercomputer.in");
        fin >> n >> m;
        inDegree.resize(n + 1, 0);
        datasets.resize(n + 1);
        for (int i = 1; i <= n; i++)
        {
            fin >> datasets[i];
        }
        for (int i = 1, u, v; i <= m; i++)
        {
            fin >> u >> v; // arc (x, y)
            adj[u].push_back(v);
            inDegree[v]++;
        }
        fin.close();
    }

    // calculare topological sort
    int startA(vector<int> inDegree, const vector<int>& datasets)
    {
        vector<int> topsort;
        queue<int> A, B;

        int result = 0;

        // for every node with inDegree = 0 and dataset = 1 / 2
        for (int i = 1; i <= n; i++)
        {   
            if (inDegree[i] == 0 && datasets[i] == 1)
                A.push(i);
            if (inDegree[i] == 0 && datasets[i] == 2)
                B.push(i);
            
        }

        while (!A.empty() || !B.empty())
        {
            while (!A.empty())
            {
                int node = A.front();
                A.pop();
                topsort.push_back(node);
                for (int neighbor : adj[node])
                {
                    inDegree[neighbor]--;
                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 1)
                        A.push(neighbor);

                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 2)
                        B.push(neighbor);
                }
            }

            if (!B.empty())
                result++;

            while (!B.empty())
            {
                int node = B.front();
                B.pop();
                topsort.push_back(node);
                for (int neighbor : adj[node])
                {
                    inDegree[neighbor]--;
                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 1)
                        A.push(neighbor);
                
                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 2)
                        B.push(neighbor);
                    
                }
            }

            if (!A.empty())
                result++;
        }

        return result;
    }

    int startB(vector<int> inDegree, const vector<int>& datasets)
    {
        vector<int> topsort;
        queue<int> A, B;

        int result = 0;

        // for every node with inDegree = 0 and dataset = 1 / 2
        for (int i = 1; i <= n; i++)
        {   
            if (inDegree[i] == 0 && datasets[i] == 1)
                A.push(i);
            
            if (inDegree[i] == 0 && datasets[i] == 2)
                B.push(i);
            
        }

        while (!A.empty() || !B.empty())
        {
            while (!B.empty())
            {
                int node = B.front();
                B.pop();
                topsort.push_back(node);
                for (int neighbor : adj[node])
                {
                    inDegree[neighbor]--;
                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 1)
                        A.push(neighbor);
                
                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 2)
                        B.push(neighbor);
                    
                }
            }

            if (!A.empty())
                result++;

            while (!A.empty())
            {
                int node = A.front();
                A.pop();
                topsort.push_back(node);
                for (int neighbor : adj[node])
                {
                    inDegree[neighbor]--;
                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 1)
                        A.push(neighbor);

                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 2)
                        B.push(neighbor);
                }
            }

            if (!B.empty())
                result++;
        }

        return result;
    }

    void print_output(int result) {
        ofstream fout("supercomputer.out");
        fout << result << '\n';
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main()
{
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto *task = new (nothrow) Task(); // hint: cppreference/nothrow
    if (!task)
    {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}