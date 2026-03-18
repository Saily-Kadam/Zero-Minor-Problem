#include <bits/stdc++.h>
using namespace std;

// Function to compute determinant using recursion
double determinant(vector<vector<double>> mat) {
    int n = mat.size();
    if (n == 1) return mat[0][0];
    if (n == 2) return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];

    double det = 0;
    for (int p = 0; p < n; p++) {
        vector<vector<double>> submat(n - 1, vector<double>(n - 1));
        for (int i = 1; i < n; i++) {
            int colIndex = 0;
            for (int j = 0; j < n; j++) {
                if (j == p) continue;
                submat[i - 1][colIndex++] = mat[i][j];
            }
        }
        det += mat[0][p] * pow(-1, p) * determinant(submat);
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

    fout << "Matrix Determinant Analysis Report\n";
    fout << "==================================\n\n";

    string line;
    vector<vector<double>> matrix;
    int matrixCount = 0;

    while (getline(fin, line)) {
        if (line.find("Matrix #") != string::npos) {
            if (!matrix.empty()) {
                matrixCount++;
                int n = matrix.size();

                fout << "Matrix #" << matrixCount << " (" << n << "x" << n << ")\n";
                fout << "----------------------------------\n";

                // Step 1: Compute determinants for scalars 2–16
                vector<double> dets;
                for (int s = 2; s <= 16; s++) {
                    vector<vector<double>> scaled = matrix;
                    for (int i = 0; i < n; i++)
                        for (int j = 0; j < n; j++)
                            scaled[i][j] *= s;

                    double det = determinant(scaled);
                    dets.push_back(det);
                    fout << "Scalar " << s << " => Determinant = " << det << "\n";
                }

                // Step 2: First differences
                vector<double> firstDiff;
                fout << "\nFirst Differences:\n";
                for (size_t i = 1; i < dets.size(); i++) {
                    double diff = dets[i] - dets[i - 1];
                    firstDiff.push_back(diff);
                    fout << "Δ(" << (i+1) << "," << i << ") = " << diff << "\n";
                }

                // Step 3: Second differences
                fout << "\nSecond Differences:\n";
                for (size_t i = 1; i < firstDiff.size(); i++) {
                    double diff2 = firstDiff[i] - firstDiff[i - 1];
                    fout << "Δ²(" << (i+2) << "," << (i+1) << "," << i << ") = " << diff2 << "\n";
                }

                fout << "\n----------------------------------\n\n";
                matrix.clear();
            }
        } else {
            // Parse numeric lines only
            stringstream ss(line);
            vector<double> row;
            double num;
            while (ss >> num) row.push_back(num);
            if (!row.empty()) matrix.push_back(row);
        }
    }

    // process the last matrix if file doesn’t end with "Matrix #"
    if (!matrix.empty()) {
        matrixCount++;
        int n = matrix.size();

        fout << "Matrix #" << matrixCount << " (" << n << "x" << n << ")\n";
        fout << "----------------------------------\n";

        vector<double> dets;
        for (int s = 2; s <= 16; s++) {
            vector<vector<double>> scaled = matrix;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    scaled[i][j] *= s;

            double det = determinant(scaled);
            dets.push_back(det);
            fout << "Scalar " << s << " => Determinant = " << det << "\n";
        }

        vector<double> firstDiff;
        fout << "\nFirst Differences:\n";
        for (size_t i = 1; i < dets.size(); i++) {
            double diff = dets[i] - dets[i - 1];
            firstDiff.push_back(diff);
            fout << "Δ(" << (i+1) << "," << i << ") = " << diff << "\n";
        }

        fout << "\nSecond Differences:\n";
        for (size_t i = 1; i < firstDiff.size(); i++) {
            double diff2 = firstDiff[i] - firstDiff[i - 1];
            fout << "Δ²(" << (i+2) << "," << (i+1) << "," << i << ") = " << diff2 << "\n";
        }

        fout << "\n----------------------------------\n\n";
    }

    fout << "Processed " << matrixCount << " matrices successfully.\n";
    fin.close();
    fout.close();

    cout << "✅ Done! Results saved to output.txt (" << matrixCount << " matrices)\n";
    return 0;
}

