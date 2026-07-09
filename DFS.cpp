#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void DFS1(vector<vector<int>>& G, vector<int>& Mark, int pos) {
    Mark[pos] = 1;
    for (int i = 0; i < G[pos].size(); i++) {
        int neighbor = G[pos][i];
        if (Mark[neighbor] == 0) {
            DFS1(G, Mark, neighbor);
        }
    }
}

void DFS2(vector<vector<int>>& G, vector<int>& Mark, int pos_x, int pos_y,
    stack<int>& st, bool& flag) {
    Mark[pos_x] = 1;
    st.push(pos_x);

    for (int i = 0; i < G[pos_x].size() && !flag; i++) {
        int neighbor = G[pos_x][i];

        if (Mark[neighbor] == 0) {
            DFS2(G, Mark, neighbor, pos_x, st, flag);
        }
        else if (Mark[neighbor] == 1 && neighbor != pos_y) {
            st.push(neighbor);
            flag = true;
            return;
        }
    }

    if (!flag) {
        st.pop();
    }
}

int main() {
    setlocale(LC_ALL, "RU");

    int n, m;
    cin >> n >> m;

    vector<vector<int>> G(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    vector<int> MarkComp(n + 1, 0);
    int count = 0;
    vector<vector<int>> Components;

    for (int i = 1; i <= n; i++) {
        if (MarkComp[i] == 0) {
            count++;
            vector<int> component;

            vector<int> MarkTemp(n + 1, 0);
            vector<int> stack;
            stack.push_back(i);
            MarkTemp[i] = 1;

            while (!stack.empty()) {
                int v = stack.back();
                stack.pop_back();
                component.push_back(v);
                MarkComp[v] = 1;

                for (int j = 0; j < G[v].size(); j++) {
                    int neighbor = G[v][j];
                    if (MarkTemp[neighbor] == 0) {
                        MarkTemp[neighbor] = 1;
                        stack.push_back(neighbor);
                    }
                }
            }
            Components.push_back(component);
        }
    }

    cout << count << endl;
    for (int i = 0; i < Components.size(); i++) {
        cout << "Компонента " << i + 1 << " (размером " << Components[i].size() << "): ";
        for (int v : Components[i]) {
            cout << v << " ";
        }
        cout << endl;
    }

    vector<int> MarkCycle(n + 1, 0);
    stack<int> st;
    bool cycleFound = false;
    vector<int> Cycle;

    for (int start = 1; start <= n && !cycleFound; start++) {
        if (MarkCycle[start] == 0) {
            DFS2(G, MarkCycle, start, -1, st, cycleFound);
        }
    }

    if (cycleFound) {
        cout << "Цикл существует" << endl;
        vector<int> temp;
        while (!st.empty()) {
            temp.push_back(st.top());
            st.pop();
        }

        for (int i = temp.size() - 1; i >= 0; i--) {
            cout << temp[i];
            if (i > 0) cout << " => ";
        }
        cout << endl;

        cout << "Цикл: ";
        for (int i = 0; i < Cycle.size(); i++) {
            cout << Cycle[i];
            if (i < Cycle.size() - 1) cout << " -> ";
        }
        cout << endl;
        cout << "Длина цикла: " << Cycle.size() - 1 << " рёбер" << endl;

        cout << "Вершины: ";
        for (int i = 0; i < Cycle.size(); i++) {
            cout << Cycle[i] << " ";
        }
        cout << endl;

    }
    else {
        cout << "Цикла нет" << endl;
    }
    return 0;
}
