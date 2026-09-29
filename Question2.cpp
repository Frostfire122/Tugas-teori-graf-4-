#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <string>

using namespace std;

class DungeonValidator {
private:
    int n;
    unordered_map<int, set<int>> adj;

public:
    DungeonValidator(int num_rooms, const unordered_map<int, vector<int>>& adj_list) {
        n = num_rooms;
        // Convert list representation to set for fast neighbor lookup
        for (const auto& pair : adj_list) {
            adj[pair.first] = set<int>(pair.second.begin(), pair.second.end());
        }
    }

    int degree(int v) const {
        auto it = adj.find(v);
        if (it != adj.end()) {
            return it->second.size();
        }
        return 0;
    }

    // Dirac's Theorem: deg(v) >= n / 2 for all v
    bool checkDiracTheorem() const {
        if (n < 3) return false;
        for (int v = 0; v < n; ++v) {
            if (degree(v) < n / 2.0) {
                return false;
            }
        }
        return true;
    }

    // Ore's Theorem: deg(u) + deg(v) >= n for all non-adjacent pairs (u, v)
    bool checkOreTheorem() const {
        if (n < 3) return false;
        for (int u = 0; u < n; ++u) {
            for (int v = u + 1; v < n; ++v) {
                auto it = adj.find(u);
                bool is_adjacent = (it != adj.end() && it->second.count(v));
                if (!is_adjacent) {
                    if (degree(u) + degree(v) < n) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    // DFS Backtracking search to find all Hamiltonian Paths
    void dfs(int curr, set<int>& visited, vector<int>& path, vector<vector<int>>& valid_paths) const {
        if (path.size() == static_cast<size_t>(n)) {
            valid_paths.push_back(path);  // Valid route traversing all vertices
            return;
        }

        auto it = adj.find(curr);
        if (it != adj.end()) {
            for (int neighbor : it->second) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    path.push_back(neighbor);

                    dfs(neighbor, visited, path, valid_paths);

                    // Backtrack
                    path.pop_back();
                    visited.erase(neighbor);
                }
            }
        }
    }

    // Explore paths starting from every room
    vector<vector<int>> findHamiltonianPaths() const {
        vector<vector<int>> valid_paths;
        for (int start = 0; start < n; ++start) {
            set<int> visited = {start};
            vector<int> path = {start};
            dfs(start, visited, path, valid_paths);
        }
        return valid_paths;
    }

    // Validate dungeon and print results
    void validateAndPrint() const {
        cout << "Room Count (n): " << n << "\n";
        cout << "Dirac Theorem Check: " 
             << (checkDiracTheorem() ? "PASSED" : "FAILED (Sufficient condition only)") << "\n";
        cout << "Ore Theorem Check:   " 
             << (checkOreTheorem() ? "PASSED" : "FAILED (Sufficient condition only)") << "\n";

        vector<vector<int>> paths = findHamiltonianPaths();
        if (!paths.empty()) {
            cout << "Validation Result: VALID DUNGEON\n";
            cout << "Total Valid Routes Found: " << paths.size() << "\n";
            cout << "Sample Route: ";
            for (size_t i = 0; i < paths[0].size(); ++i) {
                cout << paths[0][i] << (i + 1 == paths[0].size() ? "" : " -> ");
            }
            cout << "\n";
        } else {
            cout << "Validation Result: INVALID DUNGEON\n";
            cout << "Statement: No valid path exists in this dungeon layout.\n";
        }
    }
};

int main() {
    
    // Test Case A: Input graph containing a valid Hamiltonian Path
    unordered_map<int, vector<int>> sample_valid_graph = {
        {0, {1, 2, 3}},
        {1, {0, 4}},
        {2, {0, 4}},
        {3, {0, 4}},
        {4, {1, 2, 3}}
    };

    // Test Case B: Input graph with an isolated room (No Hamiltonian Path exists)
    unordered_map<int, vector<int>> sample_invalid_graph = {
        {0, {1, 2}},
        {1, {0, 2}},
        {2, {0, 1}},
        {3, {4}},
        {4, {3}}
    };

    cout << "\n--- Testing Input Graph A (Valid Layout) ---\n";
    DungeonValidator validator_a(5, sample_valid_graph);
    validator_a.validateAndPrint();

    cout << "\n--- Testing Input Graph B (Invalid Layout) ---\n";
    DungeonValidator validator_b(5, sample_invalid_graph);
    validator_b.validateAndPrint();

    return 0;
}