#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<math.h>

using namespace std;

void printBoard(vector<vector<char> > board);
vector<vector<char> > playMove(vector<vector<char> > board, int x, int y, int player);
vector<pair<int, int> > generateChildren(vector<vector<char> > board);
int getWinner(vector<vector<char> > board);