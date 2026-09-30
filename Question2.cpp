#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class DungeonSystem {
private:
    int numRooms;
    unordered_map<int, set<int>> adj;

public:
    // Deliverable 1: Procedural Dungeon Generator
    void generateDungeon(int minRooms = 5, int maxRooms = 8) {
        adj.clear();
        numRooms = minRooms + rand() % (maxRooms - minRooms + 1);
        
        int maxPossibleTunnels = numRooms * (numRooms - 1) / 2;
        int numTunnels = numRooms + rand() % (maxPossibleTunnels - numRooms + 1);

        int tunnelsMade = 0;
        int attempts = 0;
        int maxAttempts = numTunnels * 20;

        while (tunnelsMade < numTunnels && attempts < maxAttempts) {
            attempts++;
            int a = rand() % numRooms;
            int b = rand() % numRooms;

            if (a == b || adj[a].count(b)) continue;

            adj[a].insert(b);
            adj[b].insert(a);
            tunnelsMade++;
        }
    }

    void printDungeonDetails() const {
        cout << "Generated Rooms (n): " << numRooms << "\n";
        cout << "Adjacency List:\n";
        for (int i = 0; i < numRooms; ++i) {
            cout << "  Room " << i << ": ";
            auto it = adj.find(i);
            if (it != adj.end() && !it->second.empty()) {
                for (int neighbor : it->second) cout << neighbor << " ";
            } else {
                cout << "(isolated)";
            }
            cout << "\n";
        }
    }

    // Deliverable 2: DFS Backtracking for Hamiltonian Paths
    void dfs(int curr, vector<bool>& visited, vector<int>& path, vector<vector<int>>& allPaths) const {
        if (path.size() == static_cast<size_t>(numRooms)) {
            allPaths.push_back(path);
            return;
        }

        auto it = adj.find(curr);
        if (it != adj.end()) {
            for (int neighbor : it->second) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    path.push_back(neighbor);

                    dfs(neighbor, visited, path, allPaths);

                    path.pop_back();
                    visited[neighbor] = false;
                }
            }
        }
    }

    // Similarity Check: Calculates edge overlap between two paths
    double calculateSimilarity(const vector<int>& p1, const vector<int>& p2) const {
        int matchingEdges = 0;
        for (size_t i = 0; i < p1.size() - 1; ++i) {
            for (size_t j = 0; j < p2.size() - 1; ++j) {
                if ((p1[i] == p2[j] && p1[i+1] == p2[j+1]) || 
                    (p1[i] == p2[j+1] && p1[i+1] == p2[j])) {
                    matchingEdges++;
                    break;
                }
            }
        }
        return static_cast<double>(matchingEdges) / (numRooms - 1);
    }

    // Filter paths so generated routes are not too similar
    vector<vector<int>> getDiversePaths(const vector<vector<int>>& allPaths, double maxSimilarityThreshold = 0.5) const {
        vector<vector<int>> diversePaths;
        for (const auto& path : allPaths) {
            bool matchesExisting = false;
            for (const auto& selected : diversePaths) {
                if (calculateSimilarity(path, selected) > maxSimilarityThreshold) {
                    matchesExisting = true;
                    break;
                }
            }
            if (!matchesExisting) {
                diversePaths.push_back(path);
            }
        }
        return diversePaths;
    }

    void validateAndPrint() const {
        vector<vector<int>> allPaths;
        for (int start = 0; start < numRooms; ++start) {
            vector<bool> visited(numRooms, false);
            vector<int> path = {start};
            visited[start] = true;
            dfs(start, visited, path, allPaths);
        }

        if (!allPaths.empty()) {
            cout << "Validation Result: VALID DUNGEON\n";
            cout << "Total Valid Routes: " << allPaths.size() << "\n";

            vector<vector<int>> distinctRoutes = getDiversePaths(allPaths, 0.5);
            cout << "Distinct (Non-Similar) Routes Found: " << distinctRoutes.size() << "\n";
            
            cout << "Sample Routes:\n";
            int limit = min(3, static_cast<int>(distinctRoutes.size()));
            for (int r = 0; r < limit; ++r) {
                cout << "  Route " << r + 1 << ": ";
                for (size_t i = 0; i < distinctRoutes[r].size(); ++i) {
                    cout << distinctRoutes[r][i] << (i + 1 == distinctRoutes[r].size() ? "" : " -> ");
                }
                cout << "\n";
            }
        } else {
            cout << "Validation Result: INVALID DUNGEON\n";
            cout << "Statement: No valid path exists in this dungeon layout.\n";
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    DungeonSystem dungeon;
    
    dungeon.generateDungeon(5, 7);
    dungeon.printDungeonDetails();
    cout << "\n";
    dungeon.validateAndPrint();

    return 0;
}
