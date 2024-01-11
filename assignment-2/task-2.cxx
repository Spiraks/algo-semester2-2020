/****************************************************************************
Rick for the Weekend
****************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Teleportation {
    int source;
    int destination;
    int cost;
};

struct Node {
    int universe;
    int cost;
    int consecutiveFlights;

    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

int FindMinCost(int N, int M, int K, int S, int F, const vector<Teleportation>& teleportations) {
    vector<vector<int>> dp(N + 1, vector<int>(K + 1, INT_MAX));
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dp[S][0] = 0;
    pq.push({S, 0, 0});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int u = current.universe;
        int currentCost = current.cost;
        int consecutiveFlights = current.consecutiveFlights;

        if (u == F) {
            return currentCost;
        }

        if (consecutiveFlights < K) {
            for (const Teleportation& teleportation : teleportations) {
                if (teleportation.source == u) {
                    int v = teleportation.destination;
                    int cost = teleportation.cost;

                    if (dp[v][consecutiveFlights + 1] > currentCost + cost) {
                        dp[v][consecutiveFlights + 1] = currentCost + cost;
                        pq.push({v, currentCost + cost, consecutiveFlights + 1});
                    }
                }
            }
        }
    }

    return -1;
}

int main() {
    int N, M, K, S, F;
    cin >> N >> M >> K >> S >> F;

    vector<Teleportation> teleportations(M);
    for (int i = 0; i < M; ++i) {
        cin >> teleportations[i].source >> teleportations[i].destination >> teleportations[i].cost;
    }

    int result = FindMinCost(N, M, K, S, F, teleportations);

    cout << result << endl;

    return 0;
}

