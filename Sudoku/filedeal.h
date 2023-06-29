#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include "sudoku.h"
using namespace std;


// �Ѷȵȼ���ո���Ŀ�ļ�ֵ��
map<int, int> diff_map = {
        {1, 20},
        {2, 40},
        {3, 55}
};
// �������ļ��õ��Ľ��·��
string output_path = "sudoku.txt";


// ��Ӧc����������sudo�վ��ļ�
void create_sudoku(int num){
    // �Ƚ��������ɵ��������
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

// ��Ӧs�������������ļ�
void solve_sudoku(string filepath) {
    // ��ȡ�ļ�
    ofstream fout("sudoku.txt", ios_base::out);

    ifstream fin;
    fin.open(filepath, ios::in);
    string s;
    int index = 0;  // ���index�����indexΪ9��������
    vector<vector<char>>temp_vec;

    cout << "Begin to solve the sudoku game ..." << endl;
    // ���ж�ȡ���ݲ�����s�У�ֱ������ȫ����ȡ
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
        // �ŵ�����vector֮��
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

// ��Ӧn����������game������Ϸ
void create_game(int num, int m = 1){
    // �Ƚ��������ɵ��������
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

// ��Ӧr����������game������Ϸ
void create_game_range(int num, int r) {
    // �Ƚ��������ɵ��������
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

// ��Ӧu����������Ψһ��ĺ�����Ĭ������20����
void create_game_unique(int num) {
    // �Ƚ��������ɵ��������
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
