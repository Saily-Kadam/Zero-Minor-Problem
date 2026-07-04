#include <bits/stdc++.h>
using namespace std;

// Function to compute determinant of 2×2 matrix
long long determinant2x2(const vector<vector<long long>>& mat) {
    return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
}

int main() {
    ifstream fin("matrices.txt");
    ofstream fout("output.txt");

    if (!fin.is_open()) {
        cerr << "Error: Could not open matrices.txt\n";
        return 1;
    }
    if (!fout.is_open()) {
        cerr << "Error: Could not create output.txt\n";
        return 1;
    }

    fout << "2x2 Matrix Determinant Analysis (Scalars 1–52)\n";
    fout << "==================================================\n\n";

    string line;
    vector<vector<long long>> matrix;
    int matrixCount = 0;

    while (getline(fin, line)) {
        // Skip empty or non-numeric lines
        if (line.empty() || line.find("Matrix") != string::npos) continue;

        stringstream ss(line);
        vector<long long> row;
        long long num;
        while (ss >> num) row.push_back(num);

        if (row.size() == 2) matrix.push_back(row);

        // Once 2 rows collected, process the matrix
        if (matrix.size() == 2) {
            matrixCount++;
            fout << "Matrix #" << matrixCount << "\n";
            fout << "---------------------------\n";
            fout << matrix[0][0] << " " << matrix[0][1] << "\n";
            fout << matrix[1][0] << " " << matrix[1][1] << "\n\n";

            // Base determinant
            long long baseDet = determinant2x2(matrix);
            fout << "Base Determinant = " << baseDet << "\n\n";

            // Determinants for k = 1 to 52
            vector<long long> dets;
            for (int k = 1; k <= 52; k++) {
                long long detK = baseDet * (k * k); // det(kA) = k^2 * det(A)
                dets.push_back(detK);
                fout << "k = " << setw(2) << k << " -> Determinant = " << detK << "\n";
            }

            // First Differences
            fout << "\nFirst Differences:\n";
            vector<long long> firstDiff;
            for (size_t i = 1; i < dets.size(); i++) {
                long long diff = dets[i] - dets[i - 1];
                firstDiff.push_back(diff);
                fout << "Δ(" << i << "→" << i + 1 << ") = " << diff << "\n";
            }

            // Second Differences
            fout << "\nSecond Differences:\n";
            for (size_t i = 1; i < firstDiff.size(); i++) {
                long long diff2 = firstDiff[i] - firstDiff[i - 1];
                fout << "Δ²(" << i << "→" << i + 1 << ") = " << diff2 << "\n";
            }

            fout << "\n------------------------------------------\n\n";
            matrix.clear();
        }
    }

    fout << "Processed " << matrixCount << " matrices successfully.\n";
    fin.close();
    fout.close();

    cout << "✅ Done! Output written to output.txt (" << matrixCount << " matrices)\n";
    return 0;
}

