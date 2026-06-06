#include <bits/stdc++.h>
using namespace std;

// Function to calculate determinant of a 2x2 matrix
double determinant2x2(vector<vector<double>> &m) {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
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

    fout << "2x2 Matrix Determinant Analysis (Scalars 1–46)\n";
    fout << "=================================================\n\n";

    string line;
    vector<vector<double>> matrix;
    int matrixCount = 0;

    while (getline(fin, line)) {
        if (line.find("Matrix #") != string::npos) {
            // Process previous matrix if exists
            if (!matrix.empty()) {
                matrixCount++;
                fout << "Matrix #" << matrixCount << " (2x2)\n";
                fout << "----------------------------------------------\n";

                double detOriginal = determinant2x2(matrix);
                vector<double> dets;

                // Determinant scaling rule: det(kA) = k^2 * det(A)
                for (int s = 1; s <= 46; s++) {
                    double det = pow(s, 2) * detOriginal;
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
                fout << "\nSecond Differences:\n";
                for (size_t i = 1; i < firstDiff.size(); i++) {
                    double diff2 = firstDiff[i] - firstDiff[i - 1];
                    fout << "Δ²(" << i + 2 << "," << i + 1 << "," << i << ") = " << diff2 << "\n";
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
        fout << "Matrix #" << matrixCount << " (2x2)\n";
        fout << "----------------------------------------------\n";

        double detOriginal = determinant2x2(matrix);
        vector<double> dets;

        for (int s = 1; s <= 46; s++) {
            double det = pow(s, 2) * detOriginal;
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
        fout << "\nSecond Differences:\n";
        for (size_t i = 1; i < firstDiff.size(); i++) {
            double diff2 = firstDiff[i] - firstDiff[i - 1];
            fout << "Δ²(" << i + 2 << "," << i + 1 << "," << i << ") = " << diff2 << "\n";
        }

        fout << "\n----------------------------------------------\n\n";
    }

    fout << "Processed " << matrixCount << " matrices successfully.\n";
    fin.close();
    fout.close();

    cout << "✅ Done! Results saved to output.txt (" << matrixCount << " matrices processed)\n";
    return 0;
}

