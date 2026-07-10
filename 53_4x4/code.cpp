#include <bits/stdc++.h>
using namespace std;

// Function to compute determinant of 4×4 matrix
long long determinant4x4(vector<vector<long long>> a) {
    long long det = 0;
    for (int p = 0; p < 4; p++) {
        vector<vector<long long>> sub(3, vector<long long>(3));
        for (int i = 1; i < 4; i++) {
            int colIndex = 0;
            for (int j = 0; j < 4; j++) {
                if (j == p) continue;
                sub[i - 1][colIndex++] = a[i][j];
            }
        }
        long long subdet =
            sub[0][0]*(sub[1][1]*sub[2][2] - sub[1][2]*sub[2][1])
          - sub[0][1]*(sub[1][0]*sub[2][2] - sub[1][2]*sub[2][0])
          + sub[0][2]*(sub[1][0]*sub[2][1] - sub[1][1]*sub[2][0]);

        det += (p % 2 == 0 ? 1 : -1) * a[0][p] * subdet;
    }
    return det;
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

    fout << "4x4 Matrix Determinant Analysis (Scalars 1–52)\n";
    fout << "==================================================\n\n";

    string line;
    vector<vector<long long>> matrix;
    int matrixCount = 0;

    while (getline(fin, line)) {
        if (line.empty() || line.find("Matrix") != string::npos) continue;

        stringstream ss(line);
        vector<long long> row;
        long long num;
        while (ss >> num) row.push_back(num);

        if (row.size() == 4) matrix.push_back(row);

        if (matrix.size() == 4) {
            matrixCount++;
            fout << "Matrix #" << matrixCount << "\n";
            fout << "---------------------------\n";
            for (auto &r : matrix) {
                for (auto v : r) fout << setw(6) << v << " ";
                fout << "\n";
            }

            long long baseDet = determinant4x4(matrix);
            fout << "\nBase Determinant = " << baseDet << "\n\n";

            // Determinants for k = 1 to 52
            vector<long long> dets;
            for (int k = 1; k <= 52; k++) {
                long long detK = baseDet * pow(k, 4); // det(kA) = k^4 * det(A)
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
            vector<long long> secondDiff;
            for (size_t i = 1; i < firstDiff.size(); i++) {
                long long diff2 = firstDiff[i] - firstDiff[i - 1];
                secondDiff.push_back(diff2);
                fout << "Δ²(" << i << "→" << i + 1 << ") = " << diff2 << "\n";
            }

            // Third Differences
            fout << "\nThird Differences:\n";
            vector<long long> thirdDiff;
            for (size_t i = 1; i < secondDiff.size(); i++) {
                long long diff3 = secondDiff[i] - secondDiff[i - 1];
                thirdDiff.push_back(diff3);
                fout << "Δ³(" << i << "→" << i + 1 << ") = " << diff3 << "\n";
            }

            // Fourth Differences
            fout << "\nFourth Differences:\n";
            for (size_t i = 1; i < thirdDiff.size(); i++) {
                long long diff4 = thirdDiff[i] - thirdDiff[i - 1];
                fout << "Δ⁴(" << i << "→" << i + 1 << ") = " << diff4 << "\n";
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

