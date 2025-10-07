#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 16
#define ALPHABET 2 

typedef struct {
    int nfa_states_bitset;  
    int dfa_state_id;       
} DFAState;

int n, t;  
int transitions[MAX_STATES][ALPHABET][MAX_STATES];  
int dfa_transitions[1 << MAX_STATES][ALPHABET];   
DFAState dfa_states[1 << MAX_STATES];
int dfa_state_count = 0;

int is_in_dfa_states(int bitset) {
    for (int i = 0; i < dfa_state_count; i++) {
        if (dfa_states[i].nfa_states_bitset == bitset)
            return i;
    }
    return -1;
}

// Compute the move of a set of NFA states on symbol 'sym'
int move(int states_bitset, int sym) {
    int result = 0;
    for (int s = 0; s < n; s++) {
        if (states_bitset & (1 << s)) {
            for (int t = 0; t < n; t++) {
                if (transitions[s][sym][t])
                    result |= (1 << t);
            }
        }
    }
    return result;
}

int main() {
    printf("Enter number of states in NFA: ");
    scanf("%d", &n);

    printf("Enter number of transitions: ");
    scanf("%d", &t);

    // Initialize transitions to 0
    memset(transitions, 0, sizeof(transitions));

    printf("Enter transitions (from to symbol[a=0,b=1]):\n");
    for (int i = 0; i < t; i++) {
        int from, to, sym;
        scanf("%d %d %d", &from, &to, &sym);
        transitions[from][sym][to] = 1;
    }

    // Initialize DFA states
    dfa_state_count = 0;
    dfa_states[0].nfa_states_bitset = 1 << 0;  
    dfa_states[0].dfa_state_id = 0;
    dfa_state_count = 1;

    // Initialize all DFA transitions to -1 (no transition)
    for (int i = 0; i < (1 << n); i++)
        for (int sym = 0; sym < ALPHABET; sym++)
            dfa_transitions[i][sym] = -1;

    // Process DFA states
    for (int i = 0; i < dfa_state_count; i++) {
        for (int sym = 0; sym < ALPHABET; sym++) {
            int new_set = move(dfa_states[i].nfa_states_bitset, sym);
            if (new_set == 0) {
                dfa_transitions[i][sym] = -1; 
                continue;
            }

            int idx = is_in_dfa_states(new_set);
            if (idx == -1) {
                idx = dfa_state_count;
                dfa_states[idx].nfa_states_bitset = new_set;
                dfa_states[idx].dfa_state_id = idx;
                dfa_state_count++;
            }
            dfa_transitions[i][sym] = idx;
        }
    }

    // Print DFA transition table
    printf("\nDFA transition table:\n");
    printf("State\tOn a\tOn b\n");
    for (int i = 0; i < dfa_state_count; i++) {
        printf("D%d\t", i);
        for (int sym = 0; sym < ALPHABET; sym++) {
            if (dfa_transitions[i][sym] == -1)
                printf("-\t");
            else
                printf("D%d\t", dfa_transitions[i][sym]);
        }
        printf("\n");
    }

    // Optional: Print which NFA states each DFA state corresponds to
    printf("\nDFA states correspond to NFA states as follows:\n");
    for (int i = 0; i < dfa_state_count; i++) {
        printf("D%d = { ", i);
        int bitset = dfa_states[i].nfa_states_bitset;
        for (int s = 0; s < n; s++) {
            if (bitset & (1 << s))
                printf("q%d ", s);
        }
        printf("}\n");
    }

    return 0;
}
