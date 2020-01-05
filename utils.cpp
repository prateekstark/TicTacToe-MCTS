#include<iostream>
#include<vector>
using namespace std;

void printBoard(vector<vector<char> > board){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

vector<vector<char> > playMove(vector<vector<char> > board, int x, int y, int player){
	if(player == 1){
		board[x][y] = 'X';
	}
	else{
		board[x][y] = '0';
	}
	return board;
}

vector<pair<int, int> > generateChildren(vector<vector<char> > board){
	vector<pair<int, int> > children;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j] == '-'){
				children.push_back(make_pair(i, j));
			}
		}
	}
	return children;
}

int getWinner(vector<vector<char> > board){
	char winner = 'X';
	if(board[0][0] == winner && board[0][1] == winner && board[0][2] == winner){
		return 1;
	}
	if(board[1][0] == winner && board[1][1] == winner && board[1][2] == winner){
		return 1;
	}
	if(board[2][0] == winner && board[2][1] == winner && board[2][2] == winner){
		return 1;
	}
	if(board[0][0] == winner && board[1][0] == winner && board[2][0] == winner){
		return 1;
	}
	if(board[0][1] == winner && board[1][1] == winner && board[2][1] == winner){
		return 1;
	}
	if(board[0][2] == winner && board[1][2] == winner && board[2][2] == winner){
		return 1;
	}
	if(board[0][0] == winner && board[1][1] == winner && board[2][2] == winner){
		return 1;
	}
	if(board[2][0] == winner && board[1][1] == winner && board[0][2] == winner){
		return 1;
	}

	winner = '0';
	
	if(board[0][0] == winner && board[0][1] == winner && board[0][2] == winner){
		return 2;
	}
	if(board[1][0] == winner && board[1][1] == winner && board[1][2] == winner){
		return 2;
	}
	if(board[2][0] == winner && board[2][1] == winner && board[2][2] == winner){
		return 2;
	}
	if(board[0][0] == winner && board[1][0] == winner && board[2][0] == winner){
		return 2;
	}
	if(board[0][1] == winner && board[1][1] == winner && board[2][1] == winner){
		return 2;
	}
	if(board[0][2] == winner && board[1][2] == winner && board[2][2] == winner){
		return 2;
	}
	if(board[0][0] == winner && board[1][1] == winner && board[2][2] == winner){
		return 2;
	}
	if(board[2][0] == winner && board[1][1] == winner && board[0][2] == winner){
		return 2;
	}

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j] == '-'){
				return 3;
			}
		}
	}

	return 0;
}
