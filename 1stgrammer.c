#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 10
#define MAX_RULES 10
#define MAX_TERMINALS 10
#define MAX_INPUT_LENGTH 50

typedef struct {
    char symbol;
    char first[MAX_TERMINALS];
    int first_count;
} NonTerminal;

NonTerminal non_terminals[MAX_SYMBOLS];
int num_non_terminals = 0;
int num_rules = 0;

typedef struct {
    char lhs;
    char rhs[MAX_RULES][MAX_INPUT_LENGTH];
    int rhs_count;
} Production;

Production productions[MAX_SYMBOLS];

// Function to find a non-terminal index by its symbol
int find_non_terminal_index(char symbol) {
    for (int i = 0; i < num_non_terminals; i++) {
        if (non_terminals[i].symbol == symbol) {
            return i;
        }
    }
    return -1;
}

// Function to add a terminal to the First set
void add_to_first(char symbol, char terminal) {
    int index = find_non_terminal_index(symbol);
    if (index != -1) {
        NonTerminal* nt = &non_terminals[index];
        // Check if terminal is already in the First set
        for (int i = 0; i < nt->first_count; i++) {
            if (nt->first[i] == terminal) {
                return;
            }
        }
        // Add terminal to First set
        nt->first[nt->first_count++] = terminal;
    }
}

// Function to compute the First set of a non-terminal recursively
void compute_first(char symbol) {
    int index = find_non_terminal_index(symbol);
    if (index == -1) return;
    
    NonTerminal* nt = &non_terminals[index];
    if (nt->first_count > 0) return; // Already computed

    for (int i = 0; i < num_rules; i++) {
        Production* prod = &productions[i];
        if (prod->lhs == symbol) {
            for (int j = 0; j < prod->rhs_count; j++) {
                char* rhs = prod->rhs[j];
                if (rhs[0] == symbol) continue; // Avoid direct recursion
                
                if (rhs[0] >= 'a' && rhs[0] <= 'z') {
                    add_to_first(symbol, rhs[0]);
                } else {
                    compute_first(rhs[0]);
                    for (int k = 0; k < non_terminals[find_non_terminal_index(rhs[0])].first_count; k++) {
                        char terminal = non_terminals[find_non_terminal_index(rhs[0])].first[k];
                        if (terminal != '\0') { // Check for ε
                            add_to_first(symbol, terminal);
                        }
                    }
                    if (find_non_terminal_index(rhs[0]) != -1) {
                        int rhs_index = find_non_terminal_index(rhs[0]);
                        if (strchr(non_terminals[rhs_index].first, '\0')) { // Check for ε
                            int i = 1;
                            while (rhs[i] != '\0') {
                                if (rhs[i] >= 'a' && rhs[i] <= 'z') {
                                    add_to_first(symbol, rhs[i]);
                                    break;
                                } else {
                                    compute_first(rhs[i]);
                                    for (int k = 0; k < non_terminals[find_non_terminal_index(rhs[i])].first_count; k++) {
                                        char terminal = non_terminals[find_non_terminal_index(rhs[i])].first[k];
                                        if (terminal != '\0') { // Check for ε
                                            add_to_first(symbol, terminal);
                                        }
                                    }
                                    if (!strchr(non_terminals[find_non_terminal_index(rhs[i])].first, '\0')) { // Check for ε
                                        break;
                                    }
                                    i++;
                                }
                            }
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }
}

// Function to print the First sets
void print_first_sets() {
    printf("First Sets:\n");
    for (int i = 0; i < num_non_terminals; i++) {
        NonTerminal* nt = &non_terminals[i];
        printf("First(%c) = {", nt->symbol);
        for (int j = 0; j < nt->first_count; j++) {
            if (nt->first[j] == '\0') {
                printf("ε");
            } else {
                printf("%c", nt->first[j]);
            }
            if (j < nt->first_count - 1) {
                printf(", ");
            }
        }
        printf("}\n");
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char lhs;
    char rhs[MAX_INPUT_LENGTH];

    printf("Enter the number of non-terminals: ");
    scanf("%d", &num_non_terminals);
    getchar(); // Consume the newline character

    for (int i = 0; i < num_non_terminals; i++) {
        printf("Enter non-terminal %d symbol: ", i + 1);
        scanf("%c", &non_terminals[i].symbol);
        getchar(); // Consume the newline character
        non_terminals[i].first_count = 0;
    }

    printf("Enter the number of production rules: ");
    scanf("%d", &num_rules);
    getchar(); // Consume the newline character

    for (int i = 0; i < num_rules; i++) {
        printf("Enter production rule %d (e.g., S -> a | A ε): ", i + 1);
        fgets(input, sizeof(input), stdin);

        // Parse the production rule
        sscanf(input, "%c -> %[^\n]", &lhs, rhs);
        productions[i].lhs = lhs;

        // Split the rhs into different productions
        char* token = strtok(rhs, "|");
        productions[i].rhs_count = 0;
        while (token != NULL) {
            // Remove leading and trailing whitespaces
            while (*token == ' ') token++;
            char* end = token + strlen(token) - 1;
            while (end > token && (*end == ' ' || *end == '\n')) end--;
            *(end + 1) = '\0';

            strcpy(productions[i].rhs[productions[i].rhs_count++], token);
            token = strtok(NULL, "|");
        }
    }

    // Initialize the First sets
    for (int i = 0; i < num_non_terminals; i++) {
        compute_first(non_terminals[i].symbol);
    }

    // Print First sets
    print_first_sets();

    return 0;
}
