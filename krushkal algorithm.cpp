#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Edge {
    int src, dest, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};
class DSU {
private:
    vector<int> parent;
    vector<int> rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find_set(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find_set(parent[i]); // Path compression
    }

    // Union of two sets based on Rank
    bool union_sets(int u, int v) {
        int root_u = find_set(u);
        int root_v = find_set(v);

        // If they belong to the same set, a cycle would form
        if (root_u == root_v) {
            return false; 
        }
        if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
        } else if (rank[root_u] > rank[root_v]) {
            parent[root_v] = root_u;
        } else {
            parent[root_v] = root_u;
            rank[root_u]++;
        }
        return true;
    }
};
void kruskalMST(int numVertices, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());

    DSU dsu(numVertices);
    vector<Edge> mst; // To store the edges of the final MST
    int totalWeight = 0;

    // 2. Iterate through sorted edges
    for (const auto& edge : edges) {
        // If combining src and dest components doesn't form a cycle
        if (dsu.union_sets(edge.src, edge.dest)) {
            mst.push_back(edge);
            totalWeight += edge.weight;
        }

        // Optimization: An MST always contains exactly (V - 1) edges
        if (mst.size() == numVertices - 1) {
            break;
        }
    }

    // Print the resulting MST
    cout << "Edges in the constructed MST:\n";
    cout << "Source -- Destination : Weight\n";
    for (const auto& edge : mst) {
        cout << edge.src << " -- " << edge.dest << " : " << edge.weight << "\n";
    }
    cout << "Minimum Spanning Tree Total Weight: " << totalWeight << "\n";
}

int main() {
    // Example Graph Data
    int numVertices = 4; // Nodes are 0, 1, 2, 3
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskalMST(numVertices, edges);

    return 0;
}
