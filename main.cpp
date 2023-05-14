#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
 
using Board = vector<vector<int>>;

void writefile(Board board, string filename){

    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Unable to open file " << filename << endl;
        exit(1);
    }

    for (int i = 0; i < (int)board.size(); i++) {
        for (int j = 0; j < (int)board[i].size(); j++) {
            //cell == 1 ? "*" : "_"
            char cell= board[i][j] == 1 ? '*' : '_';
            outfile << cell;
        }
        outfile << endl;
    }

    outfile.close();
}
void printBoard(const Board& board) {
    for (const auto& row : board) {
        for (int cell : row) {
            cout << (cell == 1 ? "*" : "_");
        }
        cout << endl;
    }
    cout << endl;
}

void fillboard (string fileinput , Board& board){
    //Board board;
    std::ifstream file(fileinput);
    if (!file) {
        throw invalid_argument("Error: could not open file "+fileinput);
        //cerr << "Error: could not open file " << fileinput << endl;
    }
    string line;
    while (getline(file, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c == '*' ? 1 : 0);
        }
        board.push_back(row);
    }
    file.close();
}

void updateBoard(Board& board){
    int nbrows = board.size();
    int nbcols = board[0].size();
    int nbvoisin = 0;
    //Board newboard(nbrows, vector<int>(nbcols));
    cout << nbrows << " " << nbcols << endl;
    //Board newboard = board;
    Board newboard(nbrows + 2, std::vector<int>(nbcols + 2, 0));
    
    for(int row = -1; row<=nbrows; row++){
        for(int col = -1; col<=nbcols; col++){
            nbvoisin = 0;
            
            //ligne du dessus 
            if(max(row-1,0) != row && row >=0){
                for(int i = max(col-1,0); i<=min(col+1,nbcols-1); i++){ 
                    nbvoisin+=board[row-1][i];
                }
            }
            //ligne en dessous
            if(min(row+1,nbrows) != nbrows){
                for(int i = max(col-1,0); i<=min(col+1,nbcols-1); i++){
                    //cout << row+1<< " " << i << " "<<board[row+1][i] << endl;
                    nbvoisin+=board[row+1][i];
                }
            }
            //ligne du millieu
            if(row != -1 && row != nbrows){

                for(int i = max(col-1,0); i<=min(col+1,nbcols-1); i=i+1){
                    if(i == col)continue;
                    nbvoisin+=board[row][i];
                }
                //nbvoisin-=board[row][0];
            }

            //cas particulier pour une grid infinie 
            if(row == -1 || col == -1 || row == nbrows || col == nbcols ){
                if(nbvoisin ==3 )
                {
                    newboard[row+1][col+1]=1;
                }
                else{
                    newboard[row+1][col+1]=0;

                }
                continue;
            }
            
            //cout << row+1 << " " << col+1 << " " << nbvoisin << endl; 
            if(nbvoisin >=2 && nbvoisin <=3 && board[row][col] == 1 )
            {
                newboard[row+1][col+1]=1;
            }
            else if(nbvoisin ==3 && board[row][col] == 0 )
            {
                newboard[row+1][col+1]=1;
            }
            else{
                newboard[row+1][col+1]=0;
            }
        }
    }
    board = newboard;
}

int main(int argc, char* argv[])
{
    int numIterations = 1;
    string inputFilePath;
    bool printAll = false;
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "--input") {
            i++;
            if (i < argc) {
                inputFilePath = argv[i];
            } else {
                throw invalid_argument("--input requires a file path argument");
            }
        } else if (arg == "--iterations") {
            i++;
            if (i < argc) {
                numIterations = stoi(argv[i]);
                if (numIterations < 1) {
                    throw invalid_argument("--iterations requires a positive integer argument");
                }
            } else {
                throw invalid_argument("--iterations requires an integer argument");
            }
        } else if (arg == "--all") {
            printAll = true;
        }
    }

    if (inputFilePath.empty()) {
        throw invalid_argument("--input is a mandatory argument");
    }
    Board board;
    size_t dot_pos = inputFilePath.rfind(".");
    string newstring = inputFilePath.substr(0, dot_pos);
    string stextension = inputFilePath.substr(dot_pos,inputFilePath.size());

    fillboard(inputFilePath, board);
    printBoard(board);
    for (int i = 0; i<numIterations;i++){
        updateBoard(board);
        if(printAll){
            printBoard(board);
            writefile(board,newstring+"_"+to_string(i)+stextension);
        }
    }
    if(printAll == false ){
        printBoard(board);
        writefile(board,newstring+"_"+to_string(numIterations-1)+stextension);
    }
 
    return 0;
}

