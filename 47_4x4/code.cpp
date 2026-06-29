#include <bits/stdc++.h>
using namespace std;

// Function to compute determinant of 4x4 matrix using expansion by minors
double determinant4x4(const vector<vector<double>> &m) {
    double det = 0;
    for (int p = 0; p < 4; p++) {
        vector<vector<double>> submat(3, vector<double>(3));
        for (int i = 1; i < 4; i++) {
            int colIndex = 0;
            for (int j = 0; j < 4; j++) {
                if (j == p) continue;
                submat[i - 1][colIndex++] = m[i][j];
            }
        }
        double subdet = submat[0][0]*(submat[1][1]*submat[2][2] - submat[1][2]*submat[2][1])
                      - submat[0][1]*(submat[1][0]*submat[2][2] - submat[1][2]*submat[2][0])
                      + submat[0][2]*(submat[1][0]*submat[2][1] - submat[1][1]*submat[2][0]);
        det += m[0][p] * pow(-1, p) * subdet;
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

    fout << "4x4 Matrix Determinant Analysis (Scalars 1–46)\n";
    fout << "============================================================\n\n";

    string line;
    vector<vector<double>> matrix;
    int matrixCount = 0;

    while (getline(fin, line)) {
        if (line.find("Matrix #") != string::npos) {
            if (!matrix.empty()) {
                matrixCount++;
                fout << "Matrix #" << matrixCount << " (4x4)\n";
                fout << "------------------------------------------------------------\n";

                double detOriginal = determinant4x4(matrix);
                vector<double> dets;

                // Determinant scaling: det(kA) = k^4 * det(A)
                for (int s = 1; s <= 46; s++) {
                    double det = pow(s, 4) * detOriginal;
                    dets.push_back(det);
                    fout << "Scalar " << setw(2) << s << " => Determinant = " << det << "\n";
                }

                // First Differences
                vector<double> firstDiff;
                fout << "\nFirst Differences:\n";
                for (size_t i = 1; i < dets.size(); i++) {
                    double diff = dets[i] - dets[i - 1];
                    firstDiff.push_back(diff);
                    fout << "Δ(" << i + 1 << "," << i << ") = " << diff << "\n";
                }

                // Second Differences
                vector<double> secondDiff;
                fout << "\nSecond Differences:\n";
                for (size_t i = 1; i < firstDiff.size(); i++) {
                    double diff2 = firstDiff[i] - firstDiff[i - 1];
                    secondDiff.push_back(diff2);
                    fout << "Δ²(" << i + 2 << "," << i + 1 << "," << i << ") = " << diff2 << "\n";
                }

                // Third Differences
                vector<double> thirdDiff;
                fout << "\nThird Differences:\n";
                for (size_t i = 1; i < secondDiff.size(); i++) {
                    double diff3 = secondDiff[i] - secondDiff[i - 1];
                    thirdDiff.push_back(diff3);
                    fout << "Δ³(" << i + 3 << "," << i + 2 << "," << i + 1 << "," << i << ") = " << diff3 << "\n";
                }

                // Fourth Differences
                fout << "\nFourth Differences:\n";
                for (size_t i = 1; i < thirdDiff.size(); i++) {
                    double diff4 = thirdDiff[i] - thirdDiff[i - 1];
                    fout << "Δ⁴(" << i + 4 << "," << i + 3 << "," << i + 2 << "," << i + 1 << "," << i << ") = " << diff4 << "\n";
                }

                fout << "\n------------------------------------------------------------\n\n";
                matrix.clear();
            }
        } else {
            stringstream ss(line);
            vector<double> row;
            double num;
            while (ss >> num) row.push_back(num);
            if (!row.empty()) matrix.push_back(row);
        }
    }

    // Process last matrix if file doesn't end with "Matrix #"
    if (!matrix.empty()) {
        matrixCount++;
        fout << "Matrix #" << matrixCount << " (4x4)\n";
        fout << "------------------------------------------------------------\n";

        double detOriginal = determinant4x4(matrix);
        vector<double> dets;

        for (int s = 1; s <= 46; s++) {
            double det = pow(s, 4) * detOriginal;
            dets.push_back(det);
            fout << "Scalar " << setw(2) << s << " => Determinant = " << det << "\n";
        }

        vector<double> firstDiff, secondDiff, thirdDiff;

        fout << "\nFirst Differences:\n";
        for (size_t i = 1; i < dets.size(); i++) {
            double diff = dets[i] - dets[i - 1];
            firstDiff.push_back(diff);
            fout << "Δ(" << i + 1 << "," << i << ") = " << diff << "\n";
        }

        fout << "\nSecond Differences:\n";
        for (size_t i = 1; i < firstDiff.size(); i++) {
            double diff2 = firstDiff[i] - firstDiff[i - 1];
            secondDiff.push_back(diff2);
            fout << "Δ²(" << i + 2 << "," << i + 1 << "," << i << ") = " << diff2 << "\n";
        }

        fout << "\nThird Differences:\n";
        for (size_t i = 1; i < secondDiff.size(); i++) {
            double diff3 = secondDiff[i] - secondDiff[i - 1];
            thirdDiff.push_back(diff3);
            fout << "Δ³(" << i + 3 << "," << i + 2 << "," << i + 1 << "," << i << ") = " << diff3 << "\n";
        }

        fout << "\nFourth Differences:\n";
        for (size_t i = 1; i < thirdDiff.size(); i++) {
            double diff4 = thirdDiff[i] - thirdDiff[i - 1];
            fout << "Δ⁴(" << i + 4 << "," << i + 3 << "," << i + 2 << "," << i + 1 << "," << i << ") = " << diff4 << "\n";
        }

        fout << "\n------------------------------------------------------------\n\n";
    }

    fout << "Processed " << matrixCount << " matrices successfully.\n";
    fin.close();
    fout.close();

    cout << "✅ Done! Results saved to output.txt (" << matrixCount << " matrices processed)\n";
    return 0;
}

