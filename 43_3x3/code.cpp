#include <bits/stdc++.h>
using namespace std;

// Function to calculate determinant of a 3x3 matrix
double determinant3x3(vector<vector<double>> &m) {
    return m[0][0] * (m[1][1]*m[2][2] - m[1][2]*m[2][1])
         - m[0][1] * (m[1][0]*m[2][2] - m[1][2]*m[2][0])
         + m[0][2] * (m[1][0]*m[2][1] - m[1][1]*m[2][0]);
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

    fout << "3x3 Matrix Determinant Analysis (Scalars 1–42)\n";
    fout << "=================================================\n\n";

    string line;
    vector<vector<double>> matrix;
    int matrixCount = 0;

    while (getline(fin, line)) {
        if (line.find("Matrix #") != string::npos) {
            if (!matrix.empty()) {
                matrixCount++;
                fout << "Matrix #" << matrixCount << " (3x3)\n";
                fout << "----------------------------------------------\n";

                double detOriginal = determinant3x3(matrix);
                vector<double> dets;

                // Determinant scaling: det(kA) = k^3 * det(A)
                for (int s = 1; s <= 42; s++) {
                    double det = pow(s, 3) * detOriginal;
                    dets.push_back(det);
                    fout << "Scalar " << setw(2) << s << " => Determinant = " << det << "\n";
                }

                // First differences
                vector<double> firstDiff;
                fout << "\nFirst Differences:\n";
                for (size_t i = 1; i < dets.size(); i++) {
                    double diff = dets[i] - dets[i - 1];
                    firstDiff.push_back(diff);
                    fout << "Δ(" << i+1 << "," << i << ") = " << diff << "\n";
                }

                // Second differences
                vector<double> secondDiff;
                fout << "\nSecond Differences:\n";
                for (size_t i = 1; i < firstDiff.size(); i++) {
                    double diff2 = firstDiff[i] - firstDiff[i - 1];
                    secondDiff.push_back(diff2);
                    fout << "Δ²(" << i+2 << "," << i+1 << "," << i << ") = " << diff2 << "\n";
                }

                // Third differences
                fout << "\nThird Differences:\n";
                for (size_t i = 1; i < secondDiff.size(); i++) {
                    double diff3 = secondDiff[i] - secondDiff[i - 1];
                    fout << "Δ³(" << i+3 << "," << i+2 << "," << i+1 << "," << i << ") = " << diff3 << "\n";
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

    // Process the last matrix if file doesn't end with "Matrix #"
    if (!matrix.empty()) {
        matrixCount++;
        fout << "Matrix #" << matrixCount << " (3x3)\n";
        fout << "----------------------------------------------\n";

        double detOriginal = determinant3x3(matrix);
        vector<double> dets;

        for (int s = 1; s <= 42; s++) {
            double det = pow(s, 3) * detOriginal;
            dets.push_back(det);
            fout << "Scalar " << setw(2) << s << " => Determinant = " << det << "\n";
        }

        vector<double> firstDiff, secondDiff;
        fout << "\nFirst Differences:\n";
        for (size_t i = 1; i < dets.size(); i++) {
            double diff = dets[i] - dets[i - 1];
            firstDiff.push_back(diff);
            fout << "Δ(" << i+1 << "," << i << ") = " << diff << "\n";
        }

        fout << "\nSecond Differences:\n";
        for (size_t i = 1; i < firstDiff.size(); i++) {
            double diff2 = firstDiff[i] - firstDiff[i - 1];
            secondDiff.push_back(diff2);
            fout << "Δ²(" << i+2 << "," << i+1 << "," << i << ") = " << diff2 << "\n";
        }

        fout << "\nThird Differences:\n";
        for (size_t i = 1; i < secondDiff.size(); i++) {
            double diff3 = secondDiff[i] - secondDiff[i - 1];
            fout << "Δ³(" << i+3 << "," << i+2 << "," << i+1 << "," << i << ") = " << diff3 << "\n";
        }

        fout << "\n----------------------------------------------\n\n";
    }

    fout << "Processed " << matrixCount << " matrices successfully.\n";
    fin.close();
    fout.close();

    cout << "✅ Done! Results saved to output.txt (" << matrixCount << " matrices processed)\n";
    return 0;
}

