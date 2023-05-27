#include <bits/stdc++.h>
#define MAX_NODE 100000
using namespace std;


class Task {

public:
    void solve() {    
        solve_task();
    }

private:
    
    /* N = number of nodes, Q = number of questions */
    int N, Q;

    /* adj[node] = adj list */
    vector<int> adj[MAX_NODE];

    /* resolve task */
    void solve_task(void) {
        
        /* open file for tests */
        ifstream fin("magazin.in");
        ofstream fout("magazin.out");
        /* read N and Q */
        fin >> N >> Q;

        /* read adj list */
        for (int i = 2, u; i <= N; i++) {
            fin >> u;
            if (u == 1)
                adj[1].push_back(i);
            else
                adj[u].push_back(i);
        }

        /* reverse for correct order */
        for (int i = 1; i <= N; i++)
            reverse(adj[i].begin(), adj[i].end());
        
        /* store DFS in result starting from 0 */
        int *result = dfs(1);
        
        /* create hashmap = position */
        int *hashmap = new int[N + 1];
        for (int i = 0; i < N; i++)
            hashmap[result[i]] = i;
        
        /* number of each descendants for every node */
        int  *descendantCount = countDescendants(result); 

        /* read questions */
        for (int i = 0, D, E; i < Q; i++) {

            fin >> D >> E;

            int position = hashmap[D];
            if (position + E < N && E <= descendantCount[D])
                fout << result[position + E] << "\n";
            else
                fout << "-1\n";
        }

        delete[] descendantCount;
        delete[] result;
        delete[] hashmap;
        fin.close();
        fout.close();
    }

    /* calculate DFS */
    int *dfs(int startNode) {   
        /* store DFS traversal */
        int *dfsTraversal = new int[N + 1];
        int *visited = new int[N + 1];
        stack<int> st;

        st.push(startNode);
        visited[startNode] = true;

        int count = 0;

        while (!st.empty()) {
            int currNode = st.top();
            st.pop();
            dfsTraversal[count++] = currNode;

            for (int neigh : adj[currNode])
            {
                if (!visited[neigh])
                {
                    st.push(neigh);
                    visited[neigh] = true;
                }
            }
        }

        delete[] visited;
        return dfsTraversal;
    }

    int *countDescendants(int *dfsTraversal)
    {
        int *descendantCount = new int[N + 1];

        for (int i = N - 1; i >= 0; --i)
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

};

int main() {
    auto *task = new (nothrow) Task();
    task->solve();
    delete task;
    return 0;
}
