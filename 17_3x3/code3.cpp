#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <tuple>
#include <iomanip>

using namespace std;

struct MinorInfo {
    int r1, r2, c1, c2;
    int det;
    bool exactZero;
    bool modZero;
};

struct RowCandidate {
    int a, b, c;
    int mask;
};

int mod17(int x) {
    int r = x % 17;
    if (r < 0) r += 17;
    return r;
}

int det2x2(int a, int b, int c, int d) {
    return a * d - b * c;
}

void printMatrix(ofstream& fout, const vector<vector<int>>& M) {
    for (const auto& row : M) {
        for (int x : row) {
            fout << setw(3) << x << " ";
        }
        fout << "\n";
    }
}

bool inRange1To16(const vector<vector<int>>& M) {
    for (const auto& row : M) {
        for (int x : row) {
            if (x < 1 || x > 16) return false;
        }
    }
    return true;
}

bool uniqueEntries(const vector<vector<int>>& M) {
    set<int> s;
    for (const auto& row : M) {
        for (int x : row) {
            if (s.count(x)) return false;
            s.insert(x);
        }
    }
    return true;
}

vector<int> rowSums(const vector<vector<int>>& M) {
    vector<int> sums;
    for (const auto& row : M) {
        int sum = 0;
        for (int x : row) sum += x;
        sums.push_back(sum);
    }
    return sums;
}

bool rowSumsEqual(const vector<vector<int>>& M, int target) {
    vector<int> sums = rowSums(M);
    for (int s : sums) {
        if (s != target) return false;
    }
    return true;
}

vector<MinorInfo> getAllMinors(const vector<vector<int>>& M) {
    vector<MinorInfo> minors;
    for (int r1 = 0; r1 < 3; r1++) {
        for (int r2 = r1 + 1; r2 < 3; r2++) {
            for (int c1 = 0; c1 < 3; c1++) {
                for (int c2 = c1 + 1; c2 < 3; c2++) {
                    int d = det2x2(M[r1][c1], M[r1][c2], M[r2][c1], M[r2][c2]);
                    MinorInfo info;
                    info.r1 = r1; info.r2 = r2;
                    info.c1 = c1; info.c2 = c2;
                    info.det = d;
                    info.exactZero = (d == 0);
                    info.modZero = (mod17(d) == 0);
                    minors.push_back(info);
                }
            }
        }
    }
    return minors;
}

bool samePositionZeroMod17(const vector<vector<int>>& M, const MinorInfo& pos) {
    int d = det2x2(M[pos.r1][pos.c1], M[pos.r1][pos.c2],
                   M[pos.r2][pos.c1], M[pos.r2][pos.c2]);
    return mod17(d) == 0;
}

bool findAnyZeroMinorMod17(const vector<vector<int>>& M, MinorInfo& found) {
    vector<MinorInfo> minors = getAllMinors(M);
    for (const auto& m : minors) {
        if (m.modZero) {
            found = m;
            return true;
        }
    }
    return false;
}

vector<vector<int>> applyProcess(const vector<vector<int>>& A) {
    // 7 * 6 * 16 * 15 ≡ 16 ≡ -1 (mod 17)
    // do it directly as in your process result
    vector<vector<int>> B(3, vector<int>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            B[i][j] = mod17(16 * A[i][j]);
        }
    }
    return B;
}

vector<vector<int>> addAndMod(const vector<vector<int>>& B, const vector<vector<int>>& C) {
    vector<vector<int>> D(3, vector<int>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            D[i][j] = mod17(B[i][j] + C[i][j]);
        }
    }
    return D;
}

vector<vector<vector<int>>> readMatrices(const string& filename) {
    ifstream fin(filename);
    vector<vector<vector<int>>> matrices;

    if (!fin.is_open()) {
        cerr << "Cannot open file: " << filename << "\n";
        return matrices;
    }

    string line;
    while (getline(fin, line)) {
        if (line.find("Matrix #") != string::npos) {
            vector<vector<int>> M(3, vector<int>(3));
            for (int i = 0; i < 3; i++) {
                if (!getline(fin, line)) break;
                istringstream iss(line);
                iss >> M[i][0] >> M[i][1] >> M[i][2];
            }
            matrices.push_back(M);
        }
    }

    fin.close();
    return matrices;
}

vector<RowCandidate> generateRowCandidates() {
    vector<RowCandidate> rows;
    for (int a = 1; a <= 16; a++) {
        for (int b = 1; b <= 16; b++) {
            for (int c = 1; c <= 16; c++) {
                if (a == b || b == c || a == c) continue;
                if (a + b + c != 32) continue;
                int mask = (1 << (a - 1)) | (1 << (b - 1)) | (1 << (c - 1));
                rows.push_back({a, b, c, mask});
            }
        }
    }
    return rows;
}

int main() {
    string inputFile = "NewMatrices.txt";
    string outputFile = "output4.txt";

    vector<vector<vector<int>>> matrices = readMatrices(inputFile);
    ofstream fout(outputFile);

    if (!fout.is_open()) {
        cerr << "Cannot create output file: " << outputFile << "\n";
        return 1;
    }

    vector<RowCandidate> rowCandidates = generateRowCandidates();

    int successCount = 0;
    int failCount = 0;

    fout << "PROCESSING MATRICES\n";
    fout << "===================\n\n";

    for (size_t idx = 0; idx < matrices.size(); idx++) {
        const auto& A = matrices[idx];

        fout << "Matrix #" << (idx + 1) << "\n";
        fout << "Original matrix A:\n";
        printMatrix(fout, A);

        // Step 1: check original minors
        vector<MinorInfo> minors = getAllMinors(A);
        vector<MinorInfo> originalZeroPositions;

        for (const auto& m : minors) {
            if (m.exactZero || m.modZero) {
                originalZeroPositions.push_back(m);
            }
        }

        bool originalHasZeroMinor = !originalZeroPositions.empty();

        fout << "\nOriginal zero-minor analysis:\n";
        if (!originalHasZeroMinor) {
            fout << "  No zero minor found in original matrix, even modulo 17.\n";
        } else {
            for (const auto& m : originalZeroPositions) {
                fout << "  Position rows (" << (m.r1 + 1) << "," << (m.r2 + 1)
                     << "), cols (" << (m.c1 + 1) << "," << (m.c2 + 1) << ")"
                     << " | det = " << m.det
                     << " | exact zero: " << (m.exactZero ? "YES" : "NO")
                     << " | mod17 zero: " << (m.modZero ? "YES" : "NO") << "\n";
            }
        }

        // Step 2: multiplication process
        vector<vector<int>> B = applyProcess(A);
        fout << "\nAfter multiplication process and mod 17 (matrix B):\n";
        printMatrix(fout, B);

        // Step 3: search for C
        bool found = false;
        vector<vector<int>> bestC(3, vector<int>(3));
        vector<vector<int>> bestD(3, vector<int>(3));
        MinorInfo finalMinor{};
        bool preserved = false;
        bool created = false;
        MinorInfo preservedPos{};

        for (const auto& r1 : rowCandidates) {
            for (const auto& r2 : rowCandidates) {
                if (r1.mask & r2.mask) continue;

                for (const auto& r3 : rowCandidates) {
                    if (r1.mask & r3.mask) continue;
                    if (r2.mask & r3.mask) continue;

                    vector<vector<int>> C = {
                        {r1.a, r1.b, r1.c},
                        {r2.a, r2.b, r2.c},
                        {r3.a, r3.b, r3.c}
                    };

                    if (!rowSumsEqual(C, 32)) continue;
                    if (!inRange1To16(C)) continue;
                    if (!uniqueEntries(C)) continue;

                    vector<vector<int>> D = addAndMod(B, C);

                    if (!rowSumsEqual(D, 16)) continue;
                    if (!inRange1To16(D)) continue;
                    if (!uniqueEntries(D)) continue;

                    if (originalHasZeroMinor) {
                        bool ok = false;
                        MinorInfo chosen{};
                        for (const auto& pos : originalZeroPositions) {
                            if (samePositionZeroMod17(D, pos)) {
                                ok = true;
                                chosen = pos;
                                break;
                            }
                        }
                        if (!ok) continue;

                        bestC = C;
                        bestD = D;
                        preserved = true;
                        created = false;
                        preservedPos = chosen;
                        found = true;
                        break;
                    } else {
                        MinorInfo anyMinor{};
                        if (!findAnyZeroMinorMod17(D, anyMinor)) continue;

                        bestC = C;
                        bestD = D;
                        finalMinor = anyMinor;
                        preserved = false;
                        created = true;
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            if (found) break;
        }

        fout << "\nSearch result:\n";
        if (!found) {
            fout << "  No valid C found under all conditions.\n";
            failCount++;
        } else {
            fout << "  Valid C found.\n\n";
            fout << "Matrix C:\n";
            printMatrix(fout, bestC);

            fout << "\nFinal matrix D = (B + C) mod 17:\n";
            printMatrix(fout, bestD);

            fout << "\nFinal row sums: ";
            vector<int> sums = rowSums(bestD);
            for (int s : sums) fout << s << " ";
            fout << "\n";

            if (preserved) {
                fout << "Result: ZERO MINOR POSITION PRESERVED\n";
                fout << "Preserved at rows (" << (preservedPos.r1 + 1) << "," << (preservedPos.r2 + 1)
                     << "), cols (" << (preservedPos.c1 + 1) << "," << (preservedPos.c2 + 1) << ")\n";

                int d = det2x2(bestD[preservedPos.r1][preservedPos.c1],
                               bestD[preservedPos.r1][preservedPos.c2],
                               bestD[preservedPos.r2][preservedPos.c1],
                               bestD[preservedPos.r2][preservedPos.c2]);

                fout << "Final determinant at same position = " << d
                     << " | mod17 = " << mod17(d) << "\n";
            } else if (created) {
                fout << "Result: ZERO MINOR CREATED\n";
                fout << "Created at rows (" << (finalMinor.r1 + 1) << "," << (finalMinor.r2 + 1)
                     << "), cols (" << (finalMinor.c1 + 1) << "," << (finalMinor.c2 + 1) << ")\n";

                int d = det2x2(bestD[finalMinor.r1][finalMinor.c1],
                               bestD[finalMinor.r1][finalMinor.c2],
                               bestD[finalMinor.r2][finalMinor.c1],
                               bestD[finalMinor.r2][finalMinor.c2]);

                fout << "Final determinant at created position = " << d
                     << " | mod17 = " << mod17(d) << "\n";
            }

            successCount++;
        }

        fout << "\n---------------------------------------------\n\n";
    }

    fout << "SUMMARY\n";
    fout << "=======\n";
    fout << "Total matrices processed: " << matrices.size() << "\n";
    fout << "Successful cases: " << successCount << "\n";
    fout << "Failed cases: " << failCount << "\n";

    fout.close();

    cout << "Done. Output written to " << outputFile << "\n";
    return 0;
}
