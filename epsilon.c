#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
#define ALPHABET 2  // e.g., 2 symbols: a (0), b (1)

int n;  // number of states
int epsilon[MAX][MAX];
int transition[MAX][ALPHABET][MAX]; // transition[from][symbol][to] = 1
int new_transition[MAX][ALPHABET][MAX]; // resulting NFA without epsilon
int closure[MAX][MAX];
int visited[MAX];

void dfs(int start, int state) {
    if (!visited[start]) {
        visited[start] = 1;
        closure[state][start] = 1;
        for (int i = 0; i < n; i++) {
            if (epsilon[start][i])
                dfs(i, state);
        }
    }
}

void compute_epsilon_closure() {
    for (int i = 0; i < n; i++) {
        memset(visited, 0, sizeof(visited));
        dfs(i, i);
    }
}

void compute_new_transitions() {
    for (int state = 0; state < n; state++) {
        for (int a = 0; a < ALPHABET; a++) {
            int temp[MAX] = {0};

            // For each p in î-closure(state)
            for (int p = 0; p < n; p++) {
                if (closure[state][p]) {
                    // For each q such that p --a--> q
                    for (int q = 0; q < n; q++) {
                        if (transition[p][a][q]) {
                            // For each r in î-closure(q)
                            for (int r = 0; r < n; r++) {
                                if (closure[q][r]) {
                                    temp[r] = 1;
                                }
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < n; i++) {
                if (temp[i]) {
                    new_transition[state][a][i] = 1;
                }
            }
        }
    }
}

void print_transitions() {
    for (int i = 0; i < n; i++) {
        for (int a = 0; a < ALPHABET; a++) {
            printf("From  q%d on %c -> ", i, 'a' + a);
            int has = 0;
            for (int j = 0; j < n; j++) {
                if (new_transition[i][a][j]) {
                    printf("q%d ", j);
                    has = 1;
                }
            }
            if (!has) printf("-");
            printf("\n");
        }
    }
}

int main() {
    int ecount, tcount;
    printf("Enter number of states: ");
    scanf("%d", &n);

    // Initialize
    memset(epsilon, 0, sizeof(epsilon));
    memset(transition, 0, sizeof(transition));
    memset(new_transition, 0, sizeof(new_transition));
    memset(closure, 0, sizeof(closure));

    printf("Enter number of epsilon transitions: ");
    scanf("%d", &ecount);
    printf("Enter epsilon transitions (from to):\n");
    for (int i = 0; i < ecount; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        epsilon[from][to] = 1;
    }

    printf("Enter number of symbol transitions: ");
    scanf("%d", &tcount);
    printf("Enter transitions (from to symbol[a=0, b=1]):\n");
    for (int i = 0; i < tcount; i++) {
        int from, to, sym;
        scanf("%d %d %d", &from, &to, &sym);
        transition[from][sym][to] = 1;
    }

    compute_epsilon_closure();
    compute_new_transitions();

    printf("\nResulting NFA (without epsilon transitions):\n");
    print_transitions();

    return 0;
}
