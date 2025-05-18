/*
    Information Theory HW4 Arimoto-Blahut Algorithm Implementation
*/
#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

int main() {
    // Set up the parameters
    int r = 3;
    int s = 3;
    double p_n[r], q_n[s], I_n[r];
    double D_n, max_I_n;
    double P[r][s] = {
        {0.6, 0.3, 0.1},
        {0.7, 0.1, 0.2},
        {0.5, 0.05, 0.45}
    };
    double threshold = 0.00000000001;
    int counter = 0;

    // Initialize p_n
    for (int i = 0; i < r; i++) {
        p_n[i] = 1.0 / r;
    }

    // Arimoto-Blahut Algorithm
    //for (int iter = 0; iter < 10; iter++) {
    while (true) {
        counter++;
        cout << "Iteration count: " << counter << endl;

        // Calculate q_n
        for (int j = 0; j < s; j++) {
            q_n[j] = 0;
            for (int i = 0; i < r; i++) {
                q_n[j] += p_n[i] * P[i][j];
            }
        }

        // Calculate I_n
        for (int i = 0; i < r; i++) {
            I_n[i] = 0;
            for (int j = 0; j < s; j++) {
                I_n[i] += P[i][j] * log(P[i][j] / q_n[j]);
            }
        }

        // Calculate D_n
        D_n = 0;
        for (int i = 0; i < r; i++) {
            D_n += p_n[i] * exp(I_n[i]);
        }

        // Update p_n
        for (int i = 0; i < r; i++) {
            p_n[i] = p_n[i] * exp(I_n[i]) / D_n;
        }

        for (int i = 0; i < r; i++) {
            cout << p_n[i] << " ";
        }
        cout << endl;

        // Check for convergence
        max_I_n = 0;
        for (int i = 0; i < r; i++) {
            if (max_I_n < I_n[i]) {
                max_I_n = I_n[i];
            }
        }
        if (max_I_n - log(D_n) < threshold) {
            cout << endl << "Converged!" << endl;
            break;
        }
        else {
            cout << "Difference: " << max_I_n - log(D_n) << endl;
        }
    }

    // Output the results
    cout << "Iteration count: " << counter << endl;
    for (int i = 0; i < r; i++) {
        cout << "p_n[" << i << "] = " << p_n[i] << endl;
    }

    cout << endl << "Correctness check: " << endl;
    for (int i = 0; i < r; i++) {
        cout << "I_n[" << i << "] = " << I_n[i] << endl;
    }

    return 0;
}




