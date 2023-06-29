#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include "sudoku.h"
using namespace std;


// 难度等级与空格数目的键值对
map<int, int> diff_map = {
        {1, 20},
        {2, 40},
        {3, 55}
};
// 解数独文件得到的结果路径
string output_path = "sudoku.txt";


// 对应c参数，生成sudo终局文件
void create_sudoku(int num){
    // 先将曾经生成的内容清空
    ofstream f("board.txt", ios_base::out);

    cout << "Begin to create the sudoku board ..." << endl;
    vector<vector<vector<char>>> Grids;
    sudoku temp;
    temp.generateSudokuGrids(Grids, num);
    for (auto grid : Grids) {
        temp.outputBoard(grid, f);
    }
    cout << "Finish to create the sudoku board !!!" << endl;
    f.close();
}

// 对应s参数，解数独文件
void solve_sudoku(string filepath) {
    // 读取文件
    ofstream fout("sudoku.txt", ios_base::out);

    ifstream fin;
    fin.open(filepath, ios::in);
    string s;
    int index = 0;  // 标记index，如果index为9则进行求解
    vector<vector<char>>temp_vec;

    cout << "Begin to solve the sudoku game ..." << endl;
    // 逐行读取数据并存于s中，直至数据全部读取
    while(getline(fin, s)){
        // cout << s.c_str() << endl;
        vector<char> extractedChars;
        for (char c : s) {
            if (c >= '1' && c <= '9' || c == '$') {
                extractedChars.push_back(c);
            }
        }
        if (!extractedChars.empty()) {
            index++;
            temp_vec.push_back(extractedChars);
        }
        // 放到外层的vector之中
        if (index == 9) {
            sudoku solution(temp_vec);
            solution.dfs(temp_vec, 0);
            solution.outputBoard(temp_vec, fout);
            
            temp_vec.clear();
            index = 0;
            temp_vec.clear();
        }
    }

    cout << "Finish to solve the sudoku game !!!" << endl;
    fin.close();
    fout.close();
}

// 对应n参数，生成game数独游戏
void create_game(int num, int m = 1){
    // 先将曾经生成的内容清空
    ofstream f("game.txt", ios_base::out);

    cout << "Begin to create the game board ..." << endl;
    for (int i = 0; i < num; i++){
        vector<vector<char>>blank(9, vector<char>(9, '$'));
        sudoku temp(blank);
        temp.create(diff_map[m], blank);
        temp.outputBoard(blank, f);
    }
    cout << "Finish to create the game board !!!" << endl;
    f.close();
}

// 对应r参数，生成game数独游戏
void create_game_range(int num, int r) {
    // 先将曾经生成的内容清空
    ofstream f("game.txt", ios_base::out);

    cout << "Begin to create the game board ..." << endl;
    for (int i = 0; i < num; i++) {
        vector<vector<char>>blank(9, vector<char>(9, '$'));
        sudoku temp(blank);
        temp.create(r, blank);
        temp.outputBoard(blank, f);
    }
    cout << "Finish to create the game board !!!" << endl;
    f.close();
}

// 对应u参数，生成唯一解的函数，默认生成20个空
void create_game_unique(int num) {
    // 先将曾经生成的内容清空
    ofstream f("unique_game.txt", ios_base::out);

    cout << "Begin to create the game board having the unique answer ..." << endl;
    /*
    for (int i = 0; i < num; i++) {
        vector<vector<char>>blank(9, vector<char>(9, '$'));
        sudoku temp(blank);
        temp.create(20, blank);
        temp.outputBoard(blank, f);
    }
    */
    int index = 0;
    while (index < num) {
        vector<vector<char>>blank(9, vector<char>(9, '$'));
        sudoku temp(blank);
        temp.create(50, blank);
        int n = temp.countSudokuSolutions(blank);
        if (n == 1) {
            index++;
            temp.outputBoard(blank, f);
            cout << "The Gen sudoku solution number: " << n << "    (Accepted)" << endl;
        }
        else {
            cout << "The Gen sudoku solution number: " << n << "    (Rejected)" << endl;
        }
    }
    cout << "Finish to create the game board having the unique answer !!!" << endl;
    f.close();
}
