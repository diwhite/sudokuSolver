// hello.cpp
#include <iostream>
#include <fstream>
#include <set>
#include <list>
#include <ctime>
using namespace std;

class gameboard {

public:	
	int lines[9][9]; // holds the puzzle's current solution
	int canBes[9][9][9]; // holds possible entries for the spots in the puzzle
	set<int> s; // used to check completeness

	/*
	 * Constructor.
	 *
	 */
	gameboard() {}

	/*
	 * Destructor.
	 *
	 */
	~gameboard() {}

	/*
	 *  Read in the puzzle at the provided index (1-50) from p096_sudoku.txt.
	 *
	 */
	void readFromFile(int num) {
		if (num < 1 || num > 50) {
			cerr << "Error: Invalid game number, please pick a game between 1 and 50." << endl;
			return;
		}
		string line;
		string grid("Grid ");
		if (num < 10) {
			grid.push_back('0');
		}
		grid.append(to_string(num));

		ifstream sfile("p096_sudoku.txt");
		if (sfile.is_open()) {
			//cout << "file is open! looking for " << grid << endl;
			while(getline(sfile, line)) {

				if (line == grid) {
					//cout << "found! " << line << " " << grid << endl;
					for (int i=0; i < 9; ++i) {
						getline(sfile, line);
						//cout << line << endl;
						for (int j=0; j < 9; ++j) {
							lines[i][j] = (int)(line[j] - '0');
						}
					}

				}
			}
			sfile.close();
		}
	}

	/*
	 *  Is provided column complete and correct?
	 *
	 */
	bool columnComplete(int column) {
		if (column < 0 || column > 9) {
			cerr << "Error: columnComplete called on an invalid column " << column << endl;
			return false;
		}

		s.clear();
		for (int i=0; i < 9; ++i) {
			if (lines[i][column] != 0) {
				s.insert(lines[i][column]);
			}
		}
		return s.size() == 9;
	}

	/*
	 *  Is provided row complete and correct?
	 *
	 */
	bool rowComplete(int row) {
		if (row < 0 || row > 9) {
			cerr << "Error: rowComplete called on an invalid row " << row << endl;
			return false;
		}

		s.clear();
		for (int i=0; i < 9; ++i) {
			if (lines[row][i] != 0) {
				s.insert(lines[row][i]);
			}
		}
		return s.size() == 9;
	}

	/*
	 *  Is provided area complete and correct?
	 *
	 */
	bool areaComplete(int area) {
		if (area < 0 || area > 9) {
			cerr << "Error: areaComplete called on an invalid area " << area << endl;
			return false;
		}
		
		int i=0, j=0;

		switch(area) {
			case 1: i=3; break;
			case 2: i=6; break;
			case 3: j=3; break;
			case 4: j=3; i=3; break;
			case 5: j=3; i=6; break;
			case 6: j=6; break;
			case 7: j=6; i=3; break;
			case 8: j=6; i=6; break;
		}

		s.clear();
		for (int m=0; m < 3; ++m) {
			for (int n=0; n < 3; ++n) {
				if (lines[j+m][i+n] != 0) {
					s.insert(lines[j+m][i+n]);
				}	
			}
		}

		return s.size() == 9;
	}

	/*
	 *  Does the current solution solve the puzzle?
	 *
	 */
	bool isSolved() {
		for (int i=0; i < 9; ++i) {
			if (!columnComplete(i)) {
				return false;
			}
			if (!rowComplete(i)) {
				return false;
			}
			if (!areaComplete(i)) {
				return false;
			}
		}
		return true;
	}

	/*
	 *  Does the provided column already contain the given number?
	 *
	 */
	bool columnContains(int column, int num) {
		if (column < 0 || column > 9) {
			cerr << "Error: columnContains called on an invalid column " << column << endl;
			return false;
		}

		for (int i=0; i < 9; ++i) {
			if (lines[i][column] == num) {
				return true;
			}
		}
		return false;
	}

	/*
	 *  Does the provided row already contain the given number?
	 *
	 */
	bool rowContains(int row, int num) {
		if (row < 0 || row > 9) {
			cerr << "Error: rowContains called on an invalid row " << row << endl;
			return false;
		}

		for (int i=0; i < 9; ++i) {
			if (lines[row][i] == num) {
				return true;
			}
		}
		return false;
	}

	/*
	 *  Does the provided area already contain the given number?
	 *
	 */
	bool areaContains(int area, int num) {
		if (area < 0 || area > 9) {
			cerr << "Error: areaContains called on an invalid area " << area << endl;
			return false;
		}
		
		int i=0, j=0;

		switch(area) {
			case 1: i=3; break;
			case 2: i=6; break;
			case 3: j=3; break;
			case 4: j=3; i=3; break;
			case 5: j=3; i=6; break;
			case 6: j=6; break;
			case 7: j=6; i=3; break;
			case 8: j=6; i=6; break;
		}

		s.clear();
		for (int m=0; m < 3; ++m) {
			for (int n=0; n < 3; ++n) {
				if (lines[j+m][i+n] == num) {
					return true;
				}	
			}
		}
		return false;
	}

	/*
	 *  Does the provided area have only one spot for the given number?
	 *  If so, it returns the row and column in the puzzle for that spot.
	 *
	 */
	bool hasOneSpot(int area, int num, int& row, int& column) {
	
		if (area < 0 || area > 9) {
			cerr << "Error: hasOneSpot called on an invalid area " << area << endl;
			return false;
		}
		
		int i=0, j=0;

		switch(area) {
			case 1: i=3; break;
			case 2: i=6; break;
			case 3: j=3; break;
			case 4: j=3; i=3; break;
			case 5: j=3; i=6; break;
			case 6: j=6; break;
			case 7: j=6; i=3; break;
			case 8: j=6; i=6; break;
		}

		list<pair<int, int> > l;
		for (int m=0; m < 3; ++m) {
			for (int n=0; n < 3; ++n) {
				if (lines[j+m][i+n] == 0 && !rowContains(j+m, num) && !columnContains(i+n, num)) {
					l.insert(l.begin(), make_pair(j+m,i+n));
				}
			}
		}

		if(l.size() == 1) {
			row = l.begin()->first;
			column = l.begin()->second;
			return true;
		}

		return false;
	}

	/*
	 *  Returns the area index for the spot at (i,j).
	 *
	 */
	int whichArea(int i, int j) {
		if (i < 0 || i > 9) return -1;
		if (j < 0 || j > 9) return -1;
	
		if (i >= 0 && i < 3) {
			if (j >= 0 && j < 3) {
				return 0;
			} else if (j >=3 && j < 6) {
				return 1;
			} else {
				return 2;
			}
		} else if (i >= 3 && i < 6) {
			if (j >= 0 && j < 3) {
				return 3;
			} else if (j >=3 && j < 6) {
				return 4;
			} else {
				return 5;
			}
		} else {
			if (j >= 0 && j < 3) {
				return 6;
			} else if (j >=3 && j < 6) {
				return 7;
			} else {
				return 8;
			}
		}
		return -1;
	}

	/*
	 *  Does the provided row have only one spot for the given number?
	 *  If so, it returns the row and column in the puzzle for that spot.
	 *
	 */
	bool hasOneSpotRow(int row, int num, int& outRow, int& outColumn) {
	
		if (row < 0 || row > 9) {
			cerr << "Error: hasOneSpotRows called on an invalid row " << row << endl;
			return false;
		}

		list<pair<int, int> > l;
		for (int j=0; j < 9; ++j) {
		
			int area = whichArea(row, j);
			if (lines[row][j] == 0 && !columnContains(j, num) && !areaContains(area, num)) {
					l.insert(l.begin(), make_pair(row, j));
			}

		}

		if(l.size() == 1) {
			outRow = l.begin()->first;
			outColumn = l.begin()->second;
			return true;
		}

		return false;
	}

	/*
	 *  Does the provided column have only one spot for the given number?
	 *  If so, it returns the row and column in the puzzle for that spot.
	 *
	 */
	bool hasOneSpotColumn(int column, int num, int& outRow, int& outColumn) {
	
		if (column < 0 || column > 9) {
			cerr << "Error: hasOneSpotColumns called on an invalid column " << column << endl;
			return false;
		}
		
		list<pair<int, int> > l;
		for (int i=0; i < 9; ++i) {
		
			int area = whichArea(i, column);
			if (lines[i][column] == 0 && !rowContains(i, num) && !areaContains(area, num)) {
					l.insert(l.begin(), make_pair(i, column));
			}

		}

		if(l.size() == 1) {
			outRow = l.begin()->first;
			outColumn = l.begin()->second;
			return true;
		}

		return false;
	}

	/*
	 *  Update the possible candidates for (i,j).
	 *
	 */
	void updateCanBes(int i, int j) {

		for (int k=1; k <= 9; ++k) {
			canBes[i][j][k] = 0;

			if (!rowContains(i, k) && !columnContains(j, k) && !areaContains(whichArea(i,j), k)) {
				canBes[i][j][k-1] = 1;
			}
		}		
	}

	/*
	 *  Print the puzzle.
	 *
	 *  Useful for debugging.
	 */
	void print() {
		cout << "------------------" << endl;
		for (int i = 0; i < 9; ++i) {
				cout << lines[i][0] << " " << lines[i][1] << " " << lines[i][2] << "|";
				cout << lines[i][3] << " " << lines[i][4] << " " << lines[i][5] << "|";
				cout << lines[i][6] << " " << lines[i][7] << " " << lines[i][8] << "|" << endl;
		cout << "------------------" << endl;
		}
	}

	/*
	 *  Print the possible values for (i,j).
	 *
	 *  Useful for debugging.
	 */
	void printCanBes(int i, int j) {
		cout << "canBes for (" << i << "," << j << ") ";
		for (int k=0; k < 9; ++k) {
			if (canBes[i][j][k] == 1) {
				cout << k+1 << ", ";
			}
		}
		cout << endl;
	}

	/*
	 *  Iterate over the unfilled spots, try each possibly entry for each spot and see
	 *  if the puzzle is solvable with that entry filled in.
	 *
	 *  The intent is for this to be called if solve() returns false.
	 */
	bool makeAGuess() {
	
		gameboard* temp = new gameboard();

		for (int i=0; i<9; ++i) {
			for (int j=0; j<9; ++j) {

				// for each unfilled spot
				if (lines[i][j] == 0) {

					// copy the whole gameboard to the temp gameboard
					for (int x=0; x<9; ++x) {
						for (int y=0; y<9; ++y) {
							temp->lines[x][y] = lines[x][y];
						}
					}

					// can the puzzle be solved if we fill in any of the possible entries?
					temp->updateCanBes(i,j);
					for (int k=0; k<9; ++k) {
						if (temp->canBes[i][j][k] == 1) {
							temp->lines[i][j] = k+1;
							if (temp->solve()) {
								lines[i][j] = k+1;
								delete temp;
								return true;
							}
						}
					}
				}
			}
		}
		
		delete temp;
	
		return false;
	}


	/*
	 *  Attempt to solve the puzzle. Return whether it was solved or not.
	 *
	 */
	bool solve() {

		bool changed = true; // exit the while loop if nothing was changed during a run

		while (changed && !isSolved()) {

			changed = false;

			for (int a=0; a < 9; ++a) {
				for (int n=1; n < 10; ++n) {
				
					// for each area, see if there is exactly one spot where n could go
					if (!areaContains(a, n)) {
						int r, c;
						if (hasOneSpot(a, n, r, c)) {
							lines[r][c] = n;
							changed = true;
						}
					}

					// for each row, see if there is exactly one spot where n could go
					if (!rowContains(a, n)) {
						int r, c;
						if (hasOneSpotRow(a, n, r, c)) {
							lines[r][c] = n;
							changed = true;
						}
					}

					// for each column, see if there is exactly one spot where n could go
					if (!columnContains(a, n)) {
						int r, c;
						if (hasOneSpotColumn(a, n, r, c)) {
							lines[r][c] = n;
							changed = true;
						}
					}
				}
				
			}

			// check if there are any unfilled spots where there is only one possible number that fits
			for (int i=0; i < 9; ++i) {
				for (int j=0; j < 9; ++j) {

					if (lines[i][j] != 0) continue;

					updateCanBes(i,j);
					int count = 0;
					int newValue = -1;
					for (int k=0; k < 9; ++k) {
						if (canBes[i][j][k] == 1) {
							++count;
							newValue = k+1;
						}
					}

					if (count == 1) {
						lines[i][j] = newValue;
						changed = true;
					}
				}
			}
		}

		return isSolved();

	}
 
};


int main(int argc, char* argv[]) {

	if (argc < 2) {
		cerr << "Error: please supply the game number as an arg." << endl;
		return -1;
	}

	gameboard* gb = new gameboard();

	gb->readFromFile(atoi(argv[1]));

	cout << endl << "Before:" << endl;	

   	gb->print();

	clock_t begin = clock();

	while (!gb->solve()) {
		gb->makeAGuess();
		gb->solve();
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << endl <<endl << "After:" << endl;	

   	gb->print();

	
	if (gb->isSolved()) {
		cout << "I solved it in " << elapsed_secs << " seconds!" << endl;
	} else {
		// this should never happen, it would likely get stuck in the while loop above first
		cout << "I was unable to solve it, sorry!" << endl;
	}

	delete gb;

	return 0;
}
