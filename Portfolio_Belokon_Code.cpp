// MATRIX SLAE CALCULATOR

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// function to solve a system of linear equations
vector<double> solveSystem(vector<vector<double>>& A, vector<double>& B) {
    int n = A.size();

    // determinant of the matrix
    double det = 1.0;
    for (int i = 0; i < n; i++) {
        // checking for matrix singularity (if a zero is encountered on the diagonal)
        if (abs(A[i][i]) < 1e-10) {
            cout << "Singular matrix, checking for infinite solutions..." << endl;
            // set determinant to zero
            det = 0.0;
            break;
        }

        // еransforming the matrix into upper-triangular form
        for (int j = i + 1; j < n; j++) {
            double ratio = A[j][i] / A[i][i];
            for (int k = 0; k < n; k++) {
                A[j][k] -= ratio * A[i][k];
            }
            B[j] -= ratio * B[i];
        }
        // сalculating the determinant
        det *= A[i][i];
    }
    cout << "Determinant: " << det << endl;

    // сhecking if the determinant is close to zero
    if (abs(det) < 1e-10) {
        // if the det is equal to 0
        // checking the system for homogeneity (presence of non-zero constants)
        bool hasNonZeroConstant = false;
        for (int i = 0; i < n; i++) {
            if (abs(B[i]) >= 1e-10) {
                hasNonZeroConstant = true;
                break;
            }
        }

        if (hasNonZeroConstant) {
            cout << "Infinitely many solutions." << endl;
            // returning an empty vector as there are inf. many solutions
            return {};
        }
        else {
            cout << "No solutions." << endl;
            // returning an empty vector as there are no solutions
            return {};
        }
    }

    // finding solutions using back substitution (Gauss elimination)

    vector<double> x(n);

    for (int i = n - 1; i >= 0; i--) {
        x[i] = B[i] / A[i][i];
        for (int j = 0; j < i; j++) {
            B[j] -= A[j][i] * x[i];
        }
    }
    // returning the vector containing solutions
    return x;
}

int main() {
    int size;
    cout << "Enter the size of the matrix (2-10): ";
    cin >> size;

    if (size < 2 || size > 10) {
        cout << "Invalid matrix size. Please enter a size between 2 and 10." << endl;
        return 1;
    }

    vector<vector<double>> A(size, vector<double>(size));
    vector<double> B(size);

    // inputting matrix coef and const
    cout << "Enter the coefficients of the matrix and the constants for each equation:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Equation " << i + 1 << ":" << endl;
        for (int j = 0; j < size; j++) {
            cout << "Coefficient " << j + 1 << ": ";
            cin >> A[i][j];
        }
        cout << "Constant term: ";
        cin >> B[i];
    }

    // obtaining solutions to the system of equations
    vector<double> x = solveSystem(A, B);

    // outputting the solutions
    if (!x.empty()) {
        cout << "Solution:" << endl;
        for (int i = 0; i < size; i++) {
            cout << " x" << i + 1 << " = " << x[i] << endl;
        }
    }

    return 0;
}
