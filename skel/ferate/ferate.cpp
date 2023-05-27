#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    int N, M, S;

    
    vector<int> adj[NMAX];
	vector<int> enter[NMAX];
	vector<bool> in;
	vector<bool> out;

    vector<int> parent;
    vector<int> found;
    vector<int> low_link;
    stack<int> nodes_stack;
    vector<bool> in_stack;

    void read_input() {
        ifstream fin("ferate.in");
        fin >> N >> M >> S;
		in.resize(N + 1, false);
		out.resize(N + 1, false);

        for (int i = 1, x, y; i <= M ; i++) {
            fin >> x >> y;
			out[x] = true;
			in[y] = true;
            adj[x].push_back(y); // arc (x, y)
			enter[y].push_back(x); // arc (y, x)
        }
        fin.close();
    }

    vector<vector<int>> get_result() {
        //
        // TODO: Găsiți componentele tare conexe  (CTC / SCC) ale grafului orientat cu n noduri, stocat în adj.
        //
        // Rezultatul se va returna sub forma unui vector, fiecare element fiind un SCC (adică tot un vector).
        // * nodurile dintr-un SCC pot fi găsite în orice ordine
        // * SCC-urile din graf pot fi găsite în orice ordine
        //
        // Indicație: Folosiți algoritmul lui Tarjan pentru SCC.
        //

        return tarjan_scc();
    }

    vector<vector<int>> tarjan_scc() {

        parent = vector<int>(N + 1, -1);
        found = vector<int>(N + 1, -1);
        low_link = vector<int>(N + 1, -1);
        in_stack = vector<bool>(N + 1, false);

        vector<vector<int>> all_sccs;
        int timestamp = 0;
        for (int node = 1; node <= N; ++node) {
            if (parent[node] == -1) {
                parent[node] = node;


                dfs_tarjan(node, timestamp, all_sccs);
            }
        }

        return all_sccs;
    }

    void dfs_tarjan(int node, int& timestamp, vector<vector<int>>& all_sccs) {

        found[node] = ++timestamp;
        low_link[node] = found[node];
        nodes_stack.push(node);
        in_stack[node] = true;

        for (auto neigh : adj[node]) {

            if (parent[neigh] != -1) {
                if (in_stack[neigh]) {
                    low_link[node] = min(low_link[node], found[neigh]);
                }
                continue;
            }

            parent[neigh] = node;
            dfs_tarjan(neigh, timestamp, all_sccs);
            low_link[node] = min(low_link[node], low_link[neigh]);
        }

        if (low_link[node] == found[node]) {
            vector<int> scc;
            do {
                auto x = nodes_stack.top();
                nodes_stack.pop();
                in_stack[x] = false;

                scc.push_back(x);
            } while (scc.back() != node);

            all_sccs.push_back(scc);
        }
    }

	  vector<int> dfs(int startNode) {
        
		vector<int> dfsTraversal;
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

    void print_output(const vector<vector<int>>& all_sccs) {
        ofstream fout("ferate.out");
        // fout << all_sccs.size() << '\n';

		unordered_map<int, int> hashmap;
		vector<int> dfsTraversal = dfs(S);
		for (int i = 0; i < dfsTraversal.size(); i++) {
			hashmap[dfsTraversal[i]] = 1;
		}		


		int result = 0;

        for (const auto& scc : all_sccs) {
			
			bool add = false;
			
			for (auto node : scc) {
				
				if(hashmap.count(node) == 1) {
					add = false;
					break;
				}
				
				// daca scc are un singur nod si nu are vecini
				if(scc.size() == 1 && hashmap.count(node) == 0 && in[node] == false) {	
					add = true;
					break;
				}


				// daca scc are mai multe noduri
				if(scc.size() > 1) {	
					
					// se leaga alt nod de scc
					for(auto vecin : enter[node]) {
						
						auto it = find(scc.begin(), scc.end(), vecin);
						
						if(it == scc.end()) {
							add = false;
							goto muchie;
						} else {
							add = true;
						}					
					
					}
					
					
				}

                // fout << node << ' ';
            }

muchie:
			if(add == true) {
				result++;
			}

            // fout << '\n';
        }


		fout << result << '\n';
        fout.close();
    }
};

int main() {

    auto* task = new (nothrow) Task();
    task->solve();
    delete task;
    return 0;
}