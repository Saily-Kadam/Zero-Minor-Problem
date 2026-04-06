#include <bits/stdc++.h>
using namespace std;

// Determinant of 2x2 matrix
double det2x2(const vector<vector<double>>& A) {
    return A[0][0]*A[1][1] - A[0][1]*A[1][0];
}

int main() {
    ifstream fin("matrices.txt");   // correct file
    ofstream fout("output1.txt");

    if (!fin.is_open()) {
        cout << "Error opening matrices.txt\n";
        return 1;
    }

    if (!fout.is_open()) {
        cout << "Error creating output1.txt\n";
        return 1;
    }

    // 10 GP sequences (5 terms each)
    vector<vector<double>> gps = {
        {2,4,8,16,32},
        {3,9,27,81,243},
        {4,16,64,256,1024},
        {5,25,125,625,3125},
        {6,36,216,1296,7776},
        {7,49,343,2401,16807},
        {8,64,512,4096,32768},
        {9,81,729,6561,59049},
        {10,100,1000,10000,100000},
        {11,121,1331,14641,161051}
    };

    vector<vector<double>> A;
    string line;
    int matrixCount = 0;

    while (getline(fin, line)) {
        stringstream ss(line);
        vector<double> row;
        double x;

        while (ss >> x) row.push_back(x);

        if (!row.empty())
            A.push_back(row);

        if (A.size() == 2) {
            matrixCount++;
            double detA = det2x2(A);

            fout << "Matrix #" << matrixCount << "\n";
            fout << "Original Determinant = " << detA << "\n";

            for (int g = 0; g < gps.size(); g++) {
                fout << "GP " << g+1 << "\n";

                vector<double> dets;
                for (double k : gps[g])
                    dets.push_back(k*k*detA);   // det(kA)=k²det(A)

                fout << "Determinants: ";
                for (double d : dets) fout << d << " ";
                fout << "\nRatios: ";

                for (int i = 1; i < dets.size(); i++)
                    fout << dets[i]/dets[i-1] << " ";

                fout << "\n\n";
            }

            fout << "---------------------------------\n\n";
            A.clear();
        }
    }

    fin.close();
    fout.close();

    cout << "✅ Results successfully written to output1.txt (" 
         << matrixCount << " matrices)\n";

    return 0;
}

