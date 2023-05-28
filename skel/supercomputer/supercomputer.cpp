#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    /* solve task */
    void solve() {
        /* read input */
        read_input();
        /* store results */
        int resultA = startA(inDegree, datasets);
        int resultB = startB(inDegree, datasets);
        /* find min */
        print_output(min(resultA, resultB));
    }

 private:
    /* max node */
    static constexpr int NMAX = (int)1e5 + 5;
    int n, m;

    vector<int> adj[NMAX];
    vector<int> inDegree;
    vector<int> datasets;

    /* open file and read input data */
    void read_input() {
        ifstream fin("supercomputer.in");
        fin >> n >> m;
        inDegree.resize(n + 1, 0);
        datasets.resize(n + 1);
        for (int i = 1; i <= n; i++)
            fin >> datasets[i];
        for (int i = 1, u, v; i <= m; i++) {
            fin >> u >> v;
            adj[u].push_back(v);
            inDegree[v]++;
        }
        fin.close();
    }

    /* calculate sets starting from A */
    int startA(vector<int> inDegree, const vector<int>& datasets) {
        vector<int> topsort;
        queue<int> A, B;
        int context = 0;

        /* topological sort */
        for (int i = 1; i <= n; i++) {
            if (inDegree[i] == 0 && datasets[i] == 1)
                A.push(i);
            if (inDegree[i] == 0 && datasets[i] == 2)
                B.push(i);
        }

        /* both queues empty */
        while (!A.empty() || !B.empty()) {
            /* free first */
            while (!A.empty()) {
                int node = A.front();
                A.pop();
                topsort.push_back(node);
                for (int neighbor : adj[node]) {
                    inDegree[neighbor]--;
                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 1)
                        A.push(neighbor);

                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 2)
                        B.push(neighbor);
                }
            }

            /* next dates */
            if (!B.empty())
                context++;

            /* free second */
            while (!B.empty()) {
                int node = B.front();
                B.pop();
                topsort.push_back(node);
                for (int neighbor : adj[node]) {
                    inDegree[neighbor]--;
                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 1)
                        A.push(neighbor);
                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 2)
                        B.push(neighbor);
                }
            }

            /* next dates */
            if (!A.empty())
                context++;
        }

        return context;
    }

    /* calculate sets starting from B */
    int startB(vector<int> inDegree, const vector<int>& datasets) {
        vector<int> topsort;
        queue<int> A, B;
        int context = 0;

        /* topological sort */
        for (int i = 1; i <= n; i++) {
            if (inDegree[i] == 0 && datasets[i] == 1)
                A.push(i);
            if (inDegree[i] == 0 && datasets[i] == 2)
                B.push(i);
        }

        /* both queues empty*/
        while (!A.empty() || !B.empty()) {
            /* free first */
            while (!B.empty()) {
                int node = B.front();
                B.pop();
                topsort.push_back(node);
                for (int neighbor : adj[node]) {
                    inDegree[neighbor]--;
                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 1)
                        A.push(neighbor);
                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 2)
                        B.push(neighbor);
                }
            }

            /* next dates */
            if (!A.empty())
                context++;

            /* free second */
            while (!A.empty()) {
                int node = A.front();
                A.pop();
                topsort.push_back(node);
                for (int neighbor : adj[node]) {
                    inDegree[neighbor]--;
                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 1)
                        A.push(neighbor);

                    if (inDegree[neighbor] == 0 && datasets[neighbor] == 2)
                        B.push(neighbor);
                }
            }

            /* next dates */
            if (!B.empty())
                context++;
        }

        return context;
    }

    /* open file and print output */
    void print_output(int result) {
        ofstream fout("supercomputer.out");
        fout << result << '\n';
        fout.close();
    }
};

int main() {
    auto *task = new (nothrow) Task();
    task->solve();
    delete task;
    return 0;
}
