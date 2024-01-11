/****************************************************************************
Районы, кварталы, жилые массивы

Фрэнку опять прилетел новый заказ. Однако в этот раз город играет по очень странным правилам: все дороги в городе односторонние и связывают только офисы нанимателей перевозчика. Множество офисов, между любыми двумя из которых существует путь, образуют квартал, если нельзя добавить никакие другие, чтобы условие выполнялось. Фрэнку интересно, каково минимальное количество односторонних дорог нужно ещё построить, чтобы весь город стал квраталом.

Нумерация ведётся с 1. Петли допустимы.

Ввод:
Первая строка содержит пару целых чисел n и m (1 ≤ n ≤ 10^5, 0 ≤ m ≤ 10^5) — количество вершин и рёбер заданного ориентированного графа.
Следующие m строк содержат описания рёбер, по одному в строке. Каждая из строк содержит по два целых числа a и b (1 ≤ a, b ≤ n) — начало и конец ребра.

Вывод: Выведите одно число — количество дорог, которые нужно добавить, чтобы весь город стал одним кварталом.

 | in  | out |
 |-----|-----|
 | 2 1 |  1  |
 | 1 2 |     |

 | in  | out |
 |-----|-----|
 | 4 3 |  2  |
 | 1 2 |     |
 | 3 2 |     |
 | 2 4 |     |

 | in  | out |
 |-----|-----|
 | 5 4 |  2  |
 | 1 2 |     |
 | 3 2 |     |
 | 2 4 |     |
 | 2 5 |     |

****************************************************************************/

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <unordered_set>

using namespace std;

class Graph
{
public:
    explicit Graph(size_t n) : edgesFrom(n), edgesInto(n) {}
    ~Graph() = default;
    void AddEdge(size_t first, size_t second);
    size_t size() const;
    size_t Condense() const;
    void DFS(size_t vertex, vector<bool> &visited, vector<size_t> &order) const;
    void ReverseDFS(size_t vertex, vector<bool> &visited, vector<size_t> &SCC) const;
    void Print() const;
    const vector<size_t> &GetNeighbours(size_t vertex) const;
    size_t GetSCC(size_t vertex, const vector<vector<size_t>> &SCCs) const;
    size_t CalcEdge() const;

private:
    vector<vector<size_t>> edgesFrom;
    vector<vector<size_t>> edgesInto;
};

const vector<size_t> &Graph::GetNeighbours(size_t vertex) const
{
    return edgesFrom[vertex];
}

size_t Graph::size() const
{
    return edgesFrom.size();
}

void Graph::AddEdge(size_t first, size_t second)
{
    if (first == second)
        return;
    edgesFrom[first].push_back(second);
    edgesInto[second].push_back(first);
}

size_t Graph::Condense() const
{
    
    vector<vector<size_t>> condensedEdgesFrom;
    vector<vector<size_t>> condensedEdgesInto;

    vector<bool> visited(size(), false);
    vector<size_t> order;

    for (size_t i = 0; i < size(); i++)
    {
        if (!visited[i])
        {
            DFS(i, visited, order);
        }
    }

    visited.assign(size(), false);
    vector<size_t> SCCs(size());
    size_t size_SCCs = 0;
    for (auto it = order.rbegin(); it != order.rend(); ++it)
    {
        vector<size_t> SCC;
        size_t current = *it;
        if (!visited[current])
        {
            ReverseDFS(current, visited, SCC);
            
            for(auto v : SCC){
                SCCs[v]=size_SCCs;
            }
            size_SCCs++;
        }
    }

    Graph condensedGraph(size_SCCs);
    for (size_t i = 0; i < SCCs.size(); i++)
    {
        for (const auto &neighbour : GetNeighbours(i))
        {
            if (SCCs[i] != SCCs[neighbour])
            {
                condensedGraph.AddEdge(SCCs[i], SCCs[neighbour]);
            }
        }
    }

    return condensedGraph.CalcEdge();
}

size_t Graph::GetSCC(size_t vertex, const vector<vector<size_t>> &SCCs) const
{
    for (size_t i = 0; i < SCCs.size(); i++)
    {
        for (auto v : SCCs[i])
        {
            if (v == vertex)
            {
                return i;
            }
        }
    }
    return 0;
}

void Graph::DFS(size_t vertex, vector<bool> &visited, vector<size_t> &order) const
{
    visited[vertex] = true;

    for (auto neighbour : edgesInto[vertex])
    {
        if (!visited[neighbour])
        {
            DFS(neighbour, visited, order);
        }
    }

    order.push_back(vertex);
}

void Graph::ReverseDFS(size_t vertex, vector<bool> &visited, vector<size_t> &SCC) const
{
    visited[vertex] = true;
    SCC.push_back(vertex);

    for (auto neighbour : edgesFrom[vertex])
    {
        if (!visited[neighbour])
        {
            ReverseDFS(neighbour, visited, SCC);
        }
    }
}

void Graph::Print() const
{
    for (const auto &vect : edgesFrom)
    {
        for (auto v : vect)
        {
            cout << v << " ";
        }
        cout << endl;
    }
}

size_t Graph::CalcEdge() const
{
    if (this->size() < 2)
        return 0;

    size_t count_empty_from = 0;
    size_t count_empty_into = 0;

    for (size_t i = 0; i < this->size(); i++)
    {
        if(edgesFrom[i].empty())
            count_empty_from++;
        if(edgesInto[i].empty())
            count_empty_into++;
        
    }

    return count_empty_from > count_empty_into ? count_empty_from : count_empty_into;
}

int main()
{
    size_t n;
    cin >> n;
    Graph g(n);
    size_t m;
    cin >> m;
    for (size_t i = 0; i < m; ++i)
    {
        size_t a = 0;
        size_t b = 0;
        cin >> a >> b;
        g.AddEdge(a - 1, b - 1);
    }
    cout << g.Condense() << endl;
    return 0;
}
