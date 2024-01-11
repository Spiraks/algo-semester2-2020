/****************************************************************************
Look What You Made Rick Do
****************************************************************************/

/****************************************************************************
Look What You Made Rick Do
****************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;

    // Чтение матрицы смежности
    vector<vector<bool>> teleportMatrix(N, vector<bool>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            char c;
            cin >> c;
            teleportMatrix[i][j] = c - '0';
        }
    }

    // Поиск путей между вселенными
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                teleportMatrix[i][j] = teleportMatrix[i][j] || (teleportMatrix[i][k] && teleportMatrix[k][j]);
            }
        }
    }

    // Вывод матрицы смежности с учетом путей
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << teleportMatrix[i][j];
        }
        cout << endl;
    }

    return 0;
}