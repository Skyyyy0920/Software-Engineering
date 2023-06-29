#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <Windows.h>
using namespace std;


const int N = 9;


int randEx(){
    LARGE_INTEGER seed;
    QueryPerformanceFrequency(&seed);
    QueryPerformanceCounter(&seed);
    srand(unsigned int(seed.QuadPart));

    return rand();
}


class sudoku{
public:
    bool active = false;

    sudoku() {
        active = false;
    }

    sudoku(vector<vector<char>>& board){
        // printBoard(board);
        active = dfs(board, 0);
    }

    void printBoard(vector<vector<char>>& board){
        cout << " |---|---|---|---|---|---|---|---|---| " << endl;
        for (int i = 0; i < int(board.size()); i++){
            for (int j = 0; j < int(board.size()); j++){
                cout << " | " << board[i][j];
            }
            cout << " | " << endl;
            cout << " |---|---|---|---|---|---|---|---|---| " << endl;
        }
    }

    void outputBoard(vector<vector<char>>& board, ofstream& f){
        f << " |---|---|---|---|---|---|---|---|---| " << endl;
        for (int i = 0; i < int(board.size()); i++) {
            for (int j = 0; j < int(board.size()); j++) {
                f << " | " << board[i][j];
            }
            f << " | " << endl;
            f << " |---|---|---|---|---|---|---|---|---| " << endl;
        }
        f << endl;
    }

    bool isValid(int row, int col, int num, vector<vector<char>>& board){
        // 检查行有没有重复的，如果有返回false
        for (int i = 0; i < int(board.size()); i++){
            if (num == board[row][i] - '0'){
                return false;
            }
        }
        // 检查列有没有重复的，如果有返回false
        for (int i = 0; i < int(board.size()); i++)
        {
            if (num == board[i][col] - '0')
                return false;
        }
        // 检查数字所在的方块有没有重复的，如果有返回false
        int startrow = row / 3 * 3;
        int startcol = col / 3 * 3;
        int endrow = startrow + 3;
        int endcol = startcol + 3;
        for (int i = startrow; i < endrow; i++){
            for (int j = startcol; j < endcol; j++){
                if (num == board[i][j] - '0')
                    return false;
            }
        }
        return true;

    }

    // 用于生成不用终局的求解函数，需要shuffle
    bool solveSudoku_Gen(std::vector<std::vector<char>>& board) {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                if (board[row][col] == '$') {
                    std::vector<int> candidates = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
                    std::random_device rd;
                    std::mt19937 g(rd());
                    std::shuffle(candidates.begin(), candidates.end(), g);
                    for (char num : candidates) {
                        if (isValid(row, col, num, board)) {
                            board[row][col] = num + '0';
                            if (solveSudoku_Gen(board)) {
                                return true;
                            }
                            board[row][col] = '$';  // 回溯
                        }
                    }
                    return false;
                }
            }
        }

        return true;  // 数独已经填满
    }

    // 这里用于生成互不相同的数独终局
    void generateSudokuGrids(vector<vector<vector<char>>>& grids, int count) {
        random_device rd;
        mt19937 g(rd());

        while (int(grids.size()) < count) {
            vector<vector<char>> temp_sudoku(N, vector<char>(N, '$'));
            solveSudoku_Gen(temp_sudoku);

            // 检查生成的数独表是否已经存在于 grids 中
            if (std::find(grids.begin(), grids.end(), temp_sudoku) == grids.end()) {
                grids.push_back(temp_sudoku);
            }
        }
    }

    void swapCol(int m, int n, vector<vector<char>>& board){
        vector<char>temp(board.size(), ' ');
        for (int i = 0; i < int(board.size()); i++){
            temp[i] = board[i][m];
            board[i][m] = board[i][n];
            board[i][n] = temp[i];
        }
    }

    void selectBlank(int nums, vector<vector<char>>& board){
        // srand(time(NULL));
        while (nums){
            int row = randEx() % 9;
            int col = randEx() % 9;
            if (board[row][col] != '$'){
                board[row][col] = '$';
                nums--;
            }
        }
    }

    void create(int blank, vector<vector<char>>& board){
        // 小九宫格中的行和列交换，有以下９种交换方式
        int choice[9][2] = { {0,1},{0,2},{1,2},{3,4},{3,5},{4,5},{6,7},{6,8},{7,8} };
        // srand(time(NULL));

        for (int j = 0; j < 10; j++){
            int i = randEx() % 9;
            board[choice[i][0]].swap(board[choice[i][1]]);   // 随机交换两行
            swapCol(choice[i][0], choice[i][1], board);      // 随机交换两列
        }
        selectBlank(blank, board);    // 根据难度可以选择不同数量的空格
    }

    // 从０开始依次遍历81个格子，计算此数独
    bool dfs(vector<vector<char>>& board, int start){
        // 81全部遍历成功说明已经成功解出数独
        if (start == 81){
            return true;
        }
        else{
            bool nextvalid = false;
            int row = start / 9;
            int col = start % 9;
            if (board[row][col] == '$'){
                for (int i = 1; i <= 9; i++){
                    // 从１－９依次放入空格，并判断是否合法
                    if (isValid(row, col, i, board)){
                        board[row][col] = i + '0';
                        // 判断此方格的下一个方格是否成功写入
                        nextvalid = dfs(board, start + 1);
                        if (!nextvalid){
                            board[row][col] = '$';  // 回溯
                        }
                    }
                }
            }
            else{
                nextvalid = dfs(board, start + 1);
            }
            return nextvalid;
        }
    }

    // 这里用于来检查是否有唯一解，回溯法
    int solveSudoku(vector<vector<char>>& board) {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                if (board[row][col] == '$') {
                    int count = 0;
                    for (int i = 1; i <= 9; i++) {
                        if (isValid(row, col, i, board)) {
                            board[row][col] = i + '0';
                            count += solveSudoku(board);
                            board[row][col] = '$';  // 回溯
                        }
                    }
                    return count;
                }
            }
        }

        return 1;  // 数独已经填满，返回 1
    }

    // 需要创建一个数独的副本，返回数独的解数量
    int countSudokuSolutions(vector<vector<char>>& board) {
        vector<vector<char>> copy = board;  
        return solveSudoku(copy);
    }
};
