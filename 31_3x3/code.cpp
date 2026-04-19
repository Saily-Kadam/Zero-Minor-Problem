#include <bits/stdc++.h>
using namespace std;

// Function to compute determinant of a 3x3 matrix
double determinant3x3(const vector<vector<double>> &mat) {
    return mat[0][0] * (mat[1][1]*mat[2][2] - mat[1][2]*mat[2][1])
         - mat[0][1] * (mat[1][0]*mat[2][2] - mat[1][2]*mat[2][0])
         + mat[0][2] * (mat[1][0]*mat[2][1] - mat[1][1]*mat[2][0]);
}

int main() {
    ifstream fin("matrices.txt");
    ofstream fout("output.txt");

    if (!fin.is_open()) {
        cerr << "❌ Error: Could not open matrices.txt\n";
        return 1;
    }
    if (!fout.is_open()) {
        cerr << "❌ Error: Could not create output.txt\n";
        return 1;
    }

    fout << "3x3 Matrix Determinant Analysis Report (Scalars 1–30)\n";
    fout << "=====================================================\n\n";

    string line;
    vector<vector<double>> matrix;
    int matrixCount = 0;

    while (getline(fin, line)) {
        if (line.find("Matrix #") != string::npos) {
            // Process previous matrix if present
            if (!matrix.empty()) {
                matrixCount++;
                fout << "Matrix #" << matrixCount << " (3x3)\n";
                fout << "----------------------------------\n";

                double baseDet = determinant3x3(matrix);
                fout << "Original Determinant = " << baseDet << "\n\n";

                // Step 1: Determinants for scalars 1–30
                vector<double> dets;
                for (int s = 1; s <= 30; s++) {
                    double det = pow(s, 3) * baseDet;  // k³ * det(A)
                    dets.push_back(det);
                    fout << "Scalar " << s << " => Determinant = " << det << "\n";
                }

                // Step 2: First differences
                vector<double> firstDiff;
                fout << "\nFirst Differences:\n";
                for (size_t i = 1; i < dets.size(); i++) {
                    double diff = dets[i] - dets[i - 1];
                    firstDiff.push_back(diff);
                    fout << "Δ(" << i << ") = " << diff << "\n";
                }

                // Step 3: Second differences
                vector<double> secondDiff;
                fout << "\nSecond Differences:\n";
                for (size_t i = 1; i < firstDiff.size(); i++) {
                    double diff2 = firstDiff[i] - firstDiff[i - 1];
                    secondDiff.push_back(diff2);
                    fout << "Δ²(" << i << ") = " << diff2 << "\n";
                }

                // Step 4: Third differences
                fout << "\nThird Differences:\n";
                for (size_t i = 1; i < secondDiff.size(); i++) {
                    double diff3 = secondDiff[i] - secondDiff[i - 1];
                    fout << "Δ³(" << i << ") = " << diff3 << "\n";
                }

                fout << "\n----------------------------------\n\n";
                matrix.clear();
            }
        } else {
            // Parse numeric lines (matrix rows)
            stringstream ss(line);
            vector<double> row;
            double num;
            while (ss >> num) row.push_back(num);
            if (!row.empty()) matrix.push_back(row);
        }
    }

    // Process the last matrix (if file doesn’t end with "Matrix #")
    if (!matrix.empty()) {
        matrixCount++;
        fout << "Matrix #" << matrixCount << " (3x3)\n";
        fout << "----------------------------------\n";

        double baseDet = determinant3x3(matrix);
        fout << "Original Determinant = " << baseDet << "\n\n";

        vector<double> dets;
        for (int s = 1; s <= 30; s++) {
            double det = pow(s, 3) * baseDet;  // scaling rule
            dets.push_back(det);
            fout << "Scalar " << s << " => Determinant = " << det << "\n";
        }

        vector<double> firstDiff;
        fout << "\nFirst Differences:\n";
        for (size_t i = 1; i < dets.size(); i++) {
            double diff = dets[i] - dets[i - 1];
            firstDiff.push_back(diff);
            fout << "Δ(" << i << ") = " << diff << "\n";
        }

        vector<double> secondDiff;
        fout << "\nSecond Differences:\n";
        for (size_t i = 1; i < firstDiff.size(); i++) {
            double diff2 = firstDiff[i] - firstDiff[i - 1];
            secondDiff.push_back(diff2);
            fout << "Δ²(" << i << ") = " << diff2 << "\n";
        }

        fout << "\nThird Differences:\n";
        for (size_t i = 1; i < secondDiff.size(); i++) {
            double diff3 = secondDiff[i] - secondDiff[i - 1];
            fout << "Δ³(" << i << ") = " << diff3 << "\n";
        }

        fout << "\n----------------------------------\n\n";
    }

    fout << "Processed " << matrixCount << " matrices successfully.\n";
    fin.close();
    fout.close();

    cout << "✅ Done! Results saved to output.txt (" << matrixCount << " matrices)\n";
    return 0;
}

