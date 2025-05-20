/* Information Theory HW4 Arimoto-Blahut Algorithm Implementation */
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cmath>
using namespace std;

int main() {
    // Set up the parameters
    int r = 3;
    int s = 3;
    /*double P[r][s] = {
        {1.0/3, 1.0/3, 1.0/6, 1.0/6},
        {1.0/6, 1.0/3, 1.0/6, 1.0/3}
    };*/
    /*double P[r][s] = {
        {1.0, 0},
        {1.0/2, 1.0/2}
    };*/
    /*double P[r][s] = {
        {1.0/2, 1.0/2, 0, 0, 0},
        {0, 1.0/2, 1.0/2, 0, 0},
        {0, 0, 0, 1.0/2, 1.0/2},
        {0, 0, 0, 1.0/2, 1.0/2}
    };*/
    double P[r][s] = {
        {0.6, 0.3, 0.1},
        {0.7, 0.1, 0.2},
        {0.5, 0.05, 0.45}
    };
    /*double P[r][s] = {  // self-constructed transition matrix 
        {0.1532, 0.0573, 0.2586, 0.1751, 0.3558},
        {0.0734, 0.3836, 0.1117, 0.1930, 0.2383},
        {0.1004, 0.1301, 0.4068, 0.1497, 0.2130},
        {0.3057, 0.1729, 0.1173, 0.2220, 0.1821},
        {0.1112, 0.1494, 0.1037, 0.4663, 0.1694}
    };*/
    double p_n[r], q_n[s], I_n[r];
    double D_n, max_I_n;
    double threshold = 1e-10;
    int counter = 0;

    // ========= Initialize p_n =========
    for (int i = 0; i < r; i++) {
        p_n[i] = 1.0 / r; // uniform distribution
    }
    // ========= Arimoto-Blahut Algorithm Iteration =========
    while (true) { // while true until converged
        counter++;
        cout << "Iteration: " << counter << endl;
        // === Calculate q_n ===
        for (int j = 0; j < s; j++) { // j for y and i for x
            q_n[j] = 0;
            for (int i = 0; i < r; i++) {
                q_n[j] += p_n[i] * P[i][j];
            }
        }
        // === Calculate I_n ===
        for (int i = 0; i < r; i++) {
            I_n[i] = 0;
            for (int j = 0; j < s; j++) {
                if (P[i][j] == 0) {  // avoid calculation error
                    I_n[i] += 0; 
                }
                else {
                    I_n[i] += P[i][j] * log(P[i][j] / q_n[j]);
                }
            }
        }
        // === Calculate D_n ===
        D_n = 0;
        for (int i = 0; i < r; i++) {
            D_n += p_n[i] * exp(I_n[i]);
        }
        // === Update p_n ===
        for (int i = 0; i < r; i++) {
            p_n[i] = p_n[i] * exp(I_n[i]) / D_n;
        }

        // === Check for convergence === 
        max_I_n = 0;
        for (int i = 0; i < r; i++) {
            if (max_I_n < I_n[i]) {
                max_I_n = I_n[i];
            }
        }
        if (max_I_n - log(D_n) < threshold) { // converged and break
            cout << endl << "Converged!" << endl;
            break;
        }
        else { // not converged and do next iteration
            cout << "Difference: " << max_I_n - log(D_n) << endl << endl; 
        }
    }

    // ========= Correctness check =========
    // Following "How to Maximize a Concave Function" Corollary 2 to examine
    cout << endl << "Correctness check (in e-base): " << endl;
    for (int i = 0; i < r; i++) {
        cout << setprecision(20) << "I_n[" << i << "] = " << I_n[i] << endl;
    }
    // ========= Output the results =========
    cout << endl << "Input distribution: " << endl;
    for (int i = 0; i < r; i++) {
        cout << setprecision(20) << "p_n[" << i << "] = " << p_n[i] << endl;
    }
    cout << endl << "Channel capacity (in 2-based): " << endl;
    double I;
    for (int i = 0; i < r; i++) {
        I += p_n[i] * I_n[i];
    }
    cout << setprecision(20) << "I = " << I / log(2) << endl;
    return 0;
}




