#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    int n;
    cout << "Enter the size of the matrix and vector (n): ";
    cin >> n;

    vector<vector<int>> A(n, vector<int>(n));
    vector<int> x(n), y_serial(n, 0), y_parallel(n, 0);

    // Input the matrix A
    cout << "Enter the matrix A (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];

    // Input the vector x
    cout << "Enter the vector x (" << n << " elements):\n";
    for (int i = 0; i < n; ++i)
        cin >> x[i];

    // Serial matrix-vector multiplication
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            y_serial[i] += A[i][j] * x[j];
        }
    }

    // Parallel matrix-vector multiplication
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            y_parallel[i] += A[i][j] * x[j];
        }
    }

    // Output the serial result
    cout << "Serial result vector y:\n";
    for (int i = 0; i < n; ++i) {
        cout << y_serial[i] << " ";
    }
    cout << endl;

    // Output the parallel result
    cout << "Parallel result vector y:\n";
    for (int i = 0; i < n; ++i) {
        cout << y_parallel[i] << " ";
    }
    cout << endl;

    return 0;
}
