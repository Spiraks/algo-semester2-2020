#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Universe {
    size_t number;
    size_t cost;
};

struct CompareCost {
    bool operator()(const Universe& u1, const Universe& u2) {
        return u1.cost > u2.cost;
    }
};

int main() {
    size_t a, b, M, x, y;
    cin >> a >> b >> M >> x >> y;

    vector<size_t> distance(M, UINT_MAX);
    vector<bool> processed(M, false);
    priority_queue<Universe, vector<Universe>, CompareCost> pq;

    distance[x] = 0;
    pq.push({x, 0});

    while (!pq.empty()) {
        int current_universe = pq.top().number;
        pq.pop();

        if (processed[current_universe]) {
            continue;
        }

        processed[current_universe] = true;

        size_t next_universe_1 = (current_universe + 1) % M;
        size_t next_universe_2 = (current_universe * current_universe + 1) % M;

        if (distance[next_universe_1] > distance[current_universe] + a) {
            distance[next_universe_1] = distance[current_universe] + a;
            pq.push({next_universe_1, distance[next_universe_1]});
        }

        if (distance[next_universe_2] > distance[current_universe] + b) {
            distance[next_universe_2] = distance[current_universe] + b;
            pq.push({next_universe_2, distance[next_universe_2]});
        }
    }

    cout << distance[y] << endl;

    return 0;
}





