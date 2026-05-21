#include <bits/stdc++.h>
using namespace std;

// Function to calculate determinant of a 4x4 matrix using expansion by minors
double determinant4x4(vector<vector<double>> &m) {
    double det = 0;
    for (int i = 0; i < 4; i++) {
        vector<vector<double>> sub(3, vector<double>(3));
        for (int j = 1; j < 4; j++) {
            int colIndex = 0;
            for (int k = 0; k < 4; k++) {
                if (k == i) continue;
                sub[j - 1][colIndex++] = m[j][k];
            }
        }
        double subDet =
            sub[0][0] * (sub[1][1] * sub[2][2] - sub[1][2] * sub[2][1]) -
            sub[0][1] * (sub[1][0] * sub[2][2] - sub[1][2] * sub[2][0]) +
            sub[0][2] * (sub[1][0] * sub[2][1] - sub[1][1] * sub[2][0]);
        det += (i % 2 == 0 ? 1 : -1) * m[0][i] * subDet;
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

    fout << "4x4 Matrix Determinant Analysis (Scalars 1–40)\n";
    fout << "================================================\n\n";

    string line;
    vector<vector<double>> matrix;
    int matrixCount = 0;

    while (getline(fin, line)) {
        if (line.find("Matrix #") != string::npos) {
            if (!matrix.empty()) {
                matrixCount++;
                fout << "Matrix #" << matrixCount << " (4x4)\n";
                fout << "----------------------------------------------\n";

                double detOriginal = determinant4x4(matrix);
                vector<double> dets;

                // Determinant scaling property det(kA) = k^4 * det(A)
                for (int s = 1; s <= 40; s++) {
                    double det = pow(s, 4) * detOriginal;
                    dets.push_back(det);
                    fout << "Scalar " << setw(2) << s << " => Determinant = " << det << "\n";
                }

                // First difference
                vector<double> firstDiff;
                fout << "\nFirst Differences:\n";
                for (size_t i = 1; i < dets.size(); i++) {
                    double diff = dets[i] - dets[i - 1];
                    firstDiff.push_back(diff);
                    fout << "Δ(" << i+1 << "," << i << ") = " << diff << "\n";
                }

                // Second difference
                vector<double> secondDiff;
                fout << "\nSecond Differences:\n";
                for (size_t i = 1; i < firstDiff.size(); i++) {
                    double diff2 = firstDiff[i] - firstDiff[i - 1];
                    secondDiff.push_back(diff2);
                    fout << "Δ²(" << i+2 << "," << i+1 << "," << i << ") = " << diff2 << "\n";
                }

                // Third difference
                vector<double> thirdDiff;
                fout << "\nThird Differences:\n";
                for (size_t i = 1; i < secondDiff.size(); i++) {
                    double diff3 = secondDiff[i] - secondDiff[i - 1];
                    thirdDiff.push_back(diff3);
                    fout << "Δ³(" << i+3 << "," << i+2 << "," << i+1 << "," << i << ") = " << diff3 << "\n";
                }

                // Fourth difference
                fout << "\nFourth Differences:\n";
                for (size_t i = 1; i < thirdDiff.size(); i++) {
                    double diff4 = thirdDiff[i] - thirdDiff[i - 1];
                    fout << "Δ⁴(" << i+4 << "," << i+3 << "," << i+2 << "," << i+1 << "," << i << ") = " << diff4 << "\n";
                }

                fout << "\n----------------------------------------------\n\n";
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

    // Process the last matrix
    if (!matrix.empty()) {
        matrixCount++;
        fout << "Matrix #" << matrixCount << " (4x4)\n";
        fout << "----------------------------------------------\n";

        double detOriginal = determinant4x4(matrix);
        vector<double> dets;

        for (int s = 1; s <= 40; s++) {
            double det = pow(s, 4) * detOriginal;
            dets.push_back(det);
            fout << "Scalar " << setw(2) << s << " => Determinant = " << det << "\n";
        }

        vector<double> firstDiff;
        fout << "\nFirst Differences:\n";
        for (size_t i = 1; i < dets.size(); i++) {
            double diff = dets[i] - dets[i - 1];
            firstDiff.push_back(diff);
            fout << "Δ(" << i+1 << "," << i << ") = " << diff << "\n";
        }

        vector<double> secondDiff;
        fout << "\nSecond Differences:\n";
        for (size_t i = 1; i < firstDiff.size(); i++) {
            double diff2 = firstDiff[i] - firstDiff[i - 1];
            secondDiff.push_back(diff2);
            fout << "Δ²(" << i+2 << "," << i+1 << "," << i << ") = " << diff2 << "\n";
        }

        vector<double> thirdDiff;
        fout << "\nThird Differences:\n";
        for (size_t i = 1; i < secondDiff.size(); i++) {
            double diff3 = secondDiff[i] - secondDiff[i - 1];
            thirdDiff.push_back(diff3);
            fout << "Δ³(" << i+3 << "," << i+2 << "," << i+1 << "," << i << ") = " << diff3 << "\n";
        }

        fout << "\nFourth Differences:\n";
        for (size_t i = 1; i < thirdDiff.size(); i++) {
            double diff4 = thirdDiff[i] - thirdDiff[i - 1];
            fout << "Δ⁴(" << i+4 << "," << i+3 << "," << i+2 << "," << i+1 << "," << i << ") = " << diff4 << "\n";
        }

        fout << "\n----------------------------------------------\n\n";
    }

    fout << "Processed " << matrixCount << " matrices successfully.\n";
    fin.close();
    fout.close();

    cout << "✅ Done! Results saved to output.txt (" << matrixCount << " matrices processed)\n";
    return 0;
}

