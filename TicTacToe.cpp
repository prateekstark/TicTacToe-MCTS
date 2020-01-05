#include<iostream>
#include<vector>
#include "MonteCarloTreeSearch.cpp"
using namespace std;

int main(){
	vector<vector<char> > board;
	
	for(int i=0;i<3;i++){
		vector<char> tempVector;
		for(int j=0;j<3;j++){
			tempVector.push_back('-');
		}
		board.push_back(tempVector);
	}
	
	cout << "Do you want to play first?(y/n)" << endl;
	string userAnswer1;
	cin >> userAnswer1;
	
	int inputX;
	int inputY;
	if(userAnswer1.compare("Y") == 0 || userAnswer1.compare("y") == 0){
		cout << "Okay! You play first." << endl;
		while(1){
			cin >> inputX;
			cin >> inputY;
			board = playMove(board, inputX, inputY, 1);
			printBoard(board);
			if(getWinner(board) == 1){
				cout << "Player 1, the human, won the match!" << endl;
				return 0;
			}
			if(getWinner(board) == 0){
				cout << "The match is tied!" << endl;
				return 0;
			}
			MCTS* mcts = new MCTS(board, 2);
			board = mcts->predictNextState();
			printBoard(board);
			if(getWinner(board) == 2){
				cout << "Player 2, the computer, won the match!" << endl;
				return 0;
			}
		}
	}

	else{
		cout << "Okay! You play second." << endl;
		while(1){
			MCTS* mcts = new MCTS(board, 2);
			board = mcts->predictNextState();
			printBoard(board);
			if(getWinner(board) == 2){
				cout << "Player 1, the computer, won the match!" << endl;
				return 0;
			}
			if(getWinner(board) == 0){
				cout << "The match is tied!" << endl;
				return 0;
			}
			cin >> inputX;
			cin >> inputY;
			board = playMove(board, inputX, inputY, 1);
			printBoard(board);
			if(getWinner(board) == 1){
				cout << "Player 2, the human, won the match!" << endl;
				return 0;
			}
		}
	}
	
	
	return 0;
}