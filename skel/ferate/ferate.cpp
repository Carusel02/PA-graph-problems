#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    /* solve problem */
    void solve() {
        /* read & solve */
        read_input();
        /* print output */
        print_output(get_result());
    }

 private:
    /* max nodes */
    static constexpr int NMAX = (int)1e5 + 5;
    /* N = nr nodes, M = nr train lines, S = source node */
    int N, M, S;

    /* vectors */
    vector<int> adj[NMAX];
	vector<int> enter[NMAX];
	vector<bool> in;
	vector<bool> out;

    /* vectors */
    vector<int> parent;
    vector<int> found;
    vector<int> low_link;
    stack<int> nodes_stack;
    vector<bool> in_stack;

    void read_input() {
        ifstream fin("ferate.in");
        fin >> N >> M >> S;
		/* resize in & out vectors */
        in.resize(N + 1, false);
		out.resize(N + 1, false);

        for (int i = 1, x, y; i <= M ; i++) {
            fin >> x >> y;
			out[x] = true;
			in[y] = true;
            adj[x].push_back(y);
			enter[y].push_back(x);
        }
        fin.close();
    }

    vector<vector<int>> get_result() {
        return tarjan_scc();
    }

    vector<vector<int>> tarjan_scc() {
        /* resize vectors */
        parent = vector<int>(N + 1, -1);
        found = vector<int>(N + 1, -1);
        low_link = vector<int>(N + 1, -1);
        in_stack = vector<bool>(N + 1, false);

        /* declare vector with all scc components */
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
        /* start dfs tarjan */
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

	vector<int> dfs(int start) {
        /* start normal dfs */
		vector<int> dfs;
        vector<bool> visited(N + 1, false);
        stack<int> S;

        S.push(start);
        visited[start] = true;

        while (!S.empty()) {
            int node = S.top();
            S.pop();
            dfs.push_back(node);

            for (int neigh : adj[node]) {
                if (!visited[neigh]) {
                    S.push(neigh);
                    visited[neigh] = true;
                }
            }
        }

        return dfs;
    }

    /* open file and answer all questions s*/
    void print_output(const vector<vector<int>>& all_sccs) {
        ofstream fout("ferate.out");

        /* create a hashmap for every node we can access already from S */
		unordered_map<int, int> hashmap;
		vector<int> access = dfs(S);
		for (int i = 0; i < access.size(); i++) {
			hashmap[access[i]] = 1;
		}

        /* create result = nr lines train */
		int result = 0;

        /* for every scc */
        for (const auto& scc : all_sccs) {
            /* build one train line initial = false */
			bool add = false;

            /* for every node from scc */
			for (auto node : scc) {
                /* if we can access => add false */
				if(hashmap.count(node) == 1) {
					add = false;
					break;
				}

				/* if it s only one & we dont have access & it s isolated => add true*/
				if(scc.size() == 1 && hashmap.count(node) == 0 && in[node] == false) {
					add = true;
					break;
				}

				/* if there are more components */
				if(scc.size() > 1) {
					/* for every neigh -> node */
					for(auto vecin : enter[node]) {
						auto it = find(scc.begin(), scc.end(), vecin);
						/* if it s from outside */
						if(it == scc.end()) {
							/* false and next iteration */
                            add = false;
							goto muchie;
						} else {
                            /* scc component it s isolated */
							add = true;
						}
					}
				}
            }

muchie:
			/* increment */
            if (add == true)
				result++;
        }

        /* print result */
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
