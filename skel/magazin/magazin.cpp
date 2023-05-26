#include <bits/stdc++.h>
using namespace std;

class Task
{
public:
    void solve()
    {
        read_input();
        // vector<int> result = dfs(1); // Start DFS from node 1
        // unordered_map<int, int> descendantCount = countDescendants(result); // Count descendants for each node
        // print_output(descendantCount);
    }

private:
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100,005
    int N, Q;
    vector<int> adj[NMAX];
    vector<int> parents;
    unordered_map<int, int> hashmap;

    void create_hashmap(const vector<int> &dfsTraversal)
    {
        for (int i = 0; i < dfsTraversal.size(); ++i)
        {
            hashmap[dfsTraversal[i]] = i;
        }
    }


    void read_input()
    {
        ifstream fin("magazin.in");
        ofstream fout("magazin.out");
        fin >> N >> Q;

        parents.resize(N + 1);

        for (int i = 2, u; i <= N; i++)
        {
            fin >> u;
            if (u == 1)
                adj[1].push_back(i);
            else
                adj[u].push_back(i);

            parents[i] = u;
        }

        for (int i = 1; i <= N; i++)
        {
            reverse(adj[i].begin(), adj[i].end());
        }

        vector<int> result = dfs(1); // Start DFS from node 1
        unordered_map<int, int> descendantCount = countDescendants(result); // Count descendants for each node
        create_hashmap(result);
        // print_output(descendantCount);
        // print_vector_output(result);

         for (int i = 0, D, E; i < Q; ++i)
        {

            fin >> D >> E;

            // Accessing the hashmap
            if (hashmap.count(D) != 0) {
                int position = hashmap[D];
                if (position + E < result.size() && E <= descendantCount[D])
                    fout << result[position + E] << "\n";
                else
                    fout << "-1\n";
            } else {
                fout << "Key not found\n";
            }
        }

        fin.close();
    }

    vector<int> dfs(int startNode)
    {
        vector<int> dfsTraversal; // To store the DFS traversal
        vector<bool> visited(N + 1, false);
        stack<int> st;

        st.push(startNode);
        visited[startNode] = true;

        while (!st.empty())
        {
            int currNode = st.top();
            st.pop();
            dfsTraversal.push_back(currNode);

            for (int neigh : adj[currNode])
            {
                if (!visited[neigh])
                {
                    st.push(neigh);
                    visited[neigh] = true;
                }
            }
        }

        return dfsTraversal;
    }

    unordered_map<int, int> countDescendants(const vector<int> &dfsTraversal)
    {
        unordered_map<int, int> descendantCount;

        for (int i = dfsTraversal.size() - 1; i >= 0; --i)
        {
            int node = dfsTraversal[i];
            int count = 0;
            for (int child : adj[node])
            {
                count += descendantCount[child] + 1;
            }
            descendantCount[node] = count;
        }

        return descendantCount;
    }

    void print_output(const unordered_map<int, int> &descendantCount)
    {
        ofstream fout("magazin.out");
        for (const auto& [node, count] : descendantCount)
        {
            fout << "Node " << node << ": Descendants = " << count << "\n";
        }
        fout.close();
    }

    void print_vector_output(const vector<int> &vector)
    {
        ofstream fout("magazin.out");
        for (int i = 0 ; i < vector.size(); ++i)
        {
            fout << vector[i] << " ";
        }

        fout.close();
    }
};

int main()
{
    auto *task = new (nothrow) Task();
    if (!task)
    {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
