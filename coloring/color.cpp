#include <iostream>
#include <fstream>
#include "avlbst.h"

using namespace std;


typedef AVLTree<char, int> ANSWER_MAP_T;
void printSolution(ANSWER_MAP_T& answer, std::ostream& ostr);

bool isValid(char **mat, ANSWER_MAP_T &map, int &row, int &col){
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            //test right
            if(j != col - 1){
                if(mat[i][j] != mat[i][j+1]){
                    int temp1 = 0;
                    int temp2 = 0;
                    int gotBoth = 0;
                    for(ANSWER_MAP_T::iterator treeIter = map.begin(); treeIter != map.end(); ++treeIter)
                    {
                        if(gotBoth == 2){
                            break;
                        }
                        if(treeIter->first == mat[i][j]){
                            temp1 = treeIter->second;
                            gotBoth++;
                        }else if(treeIter->first == mat[i][j + 1]){
                            temp2 = treeIter->second;
                            gotBoth++;
                        }
                    }
                    if(temp1 == 0 || temp2 == 0){
                        continue;
                    }
                    if(temp1 == temp2){
                        return false;
                    }
                }
            }
            //test down
            if(i != row - 1){
                if(mat[i][j] != mat[i+1][j]){
                    int temp1 = 0;
                    int temp2 = 0;
                    int gotBoth = 0;
                    for(ANSWER_MAP_T::iterator treeIter = map.begin(); treeIter != map.end(); ++treeIter)
                    {
                        if(gotBoth == 2){
                            break;
                        }
                        if(treeIter->first == mat[i][j]){
                            temp1 = treeIter->second;
                            gotBoth++;
                        }else if(treeIter->first == mat[i+1][j]){
                            temp2 = treeIter->second;
                            gotBoth++;
                        }
                    }
                    if(temp1 == 0 || temp2 == 0){
                        continue;
                    }
                    if(temp1 == temp2){
                        return false;
                    }
                }
            }
            //test left
            if(j != 0){
                if(mat[i][j] != mat[i][j - 1]){
                    int temp1 = 0;
                    int temp2 = 0;
                    int gotBoth = 0;
                    for(ANSWER_MAP_T::iterator treeIter = map.begin(); treeIter != map.end(); ++treeIter)
                    {
                        if(gotBoth == 2){
                            break;
                        }
                        if(treeIter->first == mat[i][j]){
                            temp1 = treeIter->second;
                            gotBoth++;
                        }else if(treeIter->first == mat[i][j - 1]){
                            temp2 = treeIter->second;
                            gotBoth++;
                        }
                    }
                    if(temp1 == 0 || temp2 == 0){
                        continue;
                    }
                    if(temp1 == temp2){
                        return false;
                    }
                }
            }
            //test up
            if(i != 0){
                if(mat[i][j] != mat[i - 1][j]){
                    int temp1 = 0;
                    int temp2 = 0;
                    int gotBoth = 0;
                    for(ANSWER_MAP_T::iterator treeIter = map.begin(); treeIter != map.end(); ++treeIter)
                    {
                        if(gotBoth == 2){
                            break;
                        }
                        if(treeIter->first == mat[i][j]){
                            temp1 = treeIter->second;
                            gotBoth++;
                        }else if(treeIter->first == mat[i - 1][j]){
                            temp2 = treeIter->second;
                            gotBoth++;
                        }
                    }
                    if(temp1 == 0 || temp2 == 0){
                        continue;
                    }
                    if(temp1 == temp2){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
bool allAssigned(ANSWER_MAP_T &input, char &key, int &countries){
    int num = 0;
    for(ANSWER_MAP_T::iterator treeIter = input.begin(); treeIter != input.end(); ++treeIter){
        if(treeIter->second != 0){
            ++num;
        }
    }
    key = 'A' + num;
    if(num == countries){
        return true;
    }else{
        return false;
    }
}

bool solveHelper(ANSWER_MAP_T &input, char** mat, int &row, int &col, int countries){
    char key;
    if (allAssigned(input, key, countries)){
        return true;
    }
    for (int color = 1; color <= 4; ++color)
    {
        input.insert(make_pair(key, color));

        if (isValid(mat, input, row, col))
        {
            if (solveHelper(input, mat, row, col, countries)){
                return true;
            }else{
                input.insert(make_pair(key, 0));
            }
        }else{
            input.insert(make_pair(key, 0));
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    if(argc < 3) {
        cout << "Please supply a map input file and output filename" << endl;
        return 1;
    }
    ifstream in_file(argv[1]);
    ofstream out_file(argv[2]);
    ANSWER_MAP_T output;
    int numCountries, numRows, numCols;
    in_file >> numCountries >> numRows >> numCols;
    char **input = new char*[numRows];
    
    for(int i = 0; i < numRows; ++i){
        input[i] = new char[numCols];
        string temp;
        in_file >> temp;
        for(int j = 0; j < numCols; ++j){
            input[i][j] = temp.at(j);
        }
    }
    
    solveHelper(output, input, numRows, numCols, numCountries);

    // Call printSolution to output the answers to the output file
    printSolution(output, out_file);
    
    // deallocate memory
    for(int i = 0; i < numRows; ++i){
        delete [] input[i];
    }
    delete [] input;
    return 0;
}


void printSolution(ANSWER_MAP_T& answer, std::ostream& os)
{
    for(ANSWER_MAP_T::iterator it = answer.begin();
            it!= answer.end();
            ++it) {
        os << it->first << " " << it->second << endl;
    }
}

