/****************************************************************************
За молоком

Леон и Матильда собрались пойти в магазин за молоком. Их хочет поймать Стэнсфилд, поэтому нашим товарищам нужно сделать это как можно быстрее. Каково минимальное количество улиц, по которым пройдёт хотя бы один из ребят (либо Матильда, либо Леон, либо оба вместе)?

Граф связный и неориентированный. Вершины нумеруются с 1.

Ввод:
Первая строка содержит количество вершин n (1 ≤ n ≤ 10^5), количество ребер m (0 ≤ m ≤ 10^5) и номера вершин графа leon, matilda, milk, в которых находятся соответственно Леон, Матильда и магазин с молоком.
Следующие m строк содержат ребра графа. В каждой строке два числа, разделенные пробелом, если между i и j существует ребро. Гарантируется, что в графе нет петель и мультиребер.

Вывод: Одно число – количество ребер.


  in       | out
 ----------|-----
 3 2 1 2 3 |  2
 1 3       |
 2 3       |


  in       | out
 ----------|-----
 3 2 1 2 3 |  2
 1 3       |
 1 2       |

  in       | out
 ----------|-----
 7 8 1 7 3 |  2
 2 4       |
 4 1       |
 4 7       |
 4 5       |
 5 6       |
 3 6       |
 3 8       |
 8 7       |
 2 8       |


****************************************************************************/

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
 
using namespace std;
 
class Graph{
public:
    explicit Graph(size_t n): edges(n){}
    ~Graph() = default;
    void AddEdge(size_t first, size_t second);
    size_t size() const;
    const vector<size_t>& GetNeighbours(size_t vertex) const;
private:
    vector<vector<size_t>> edges;
};
 
const vector<size_t>& Graph::GetNeighbours(size_t vertex) const{
    return edges[vertex];
}

size_t Graph::size() const{
    return edges.size();
}

void Graph::AddEdge(size_t first, size_t second){
    edges[first].push_back(second);
    edges[second].push_back(first);
}
 


// Функция для поиска кратчайших путей из одной вершины до всех остальных
void Calc(const Graph& graph, size_t start, vector<size_t>& distances){
    vector<short> colors(graph.size());
    queue<size_t> q;
    q.push(start);
    colors[start] = 1;
    distances[start] = 0;
    while(!q.empty()){
        size_t it = q.front();
        size_t dist = distances[it];
        vector<size_t> neighbours = graph.GetNeighbours(it);
        for(size_t i = 0; i < neighbours.size(); ++i){
            if(colors[neighbours[i]] == 0){
                distances[neighbours[i]] = dist + 1;
                colors[neighbours[i]] = 1;
                q.push(neighbours[i]);
            }
        }
        colors[it] = 2;
        q.pop();
    }
}

int main(){
    size_t n;
    cin >> n;
    Graph g(n);
    size_t m;
    cin >> m;
    size_t Leon, Matilda, milk;
    cin >> Leon >> Matilda >> milk;
    for(size_t i = 0; i < m; ++i){
        size_t a = 0;
        size_t b = 0;
        cin >> a >> b;
        g.AddEdge(a - 1, b - 1);
    }

    vector<size_t> wayLeon(n);
    vector<size_t> wayMatild(n);
    vector<size_t> wayToMilk(n);

	Calc(g, Leon - 1, wayLeon);
    Calc(g, Matilda - 1, wayMatild);
    Calc(g, milk - 1, wayToMilk);
    

    size_t minimum = n; 
    for(size_t i = 0; i < n; ++i){
        if((wayLeon[i] + wayMatild[i] + wayToMilk[i]) < minimum){
            minimum = wayLeon[i] + wayMatild[i] + wayToMilk[i];
        }
    }

    cout << minimum;
    return 0;
}
