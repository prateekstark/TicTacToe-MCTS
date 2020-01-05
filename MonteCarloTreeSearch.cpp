#include<iostream>
#include<vector>
#include<math.h>
#include "utils.cpp"
#include<ctime>
#include<cstdlib>

using namespace std;

class Node{
public:
	vector<vector<char> > boardState;
	int player;
	int Q;
	int num_visits;
	vector<Node*> unvisited_children;
	vector<Node*> visited_children;
	Node* parent;

	Node(vector<vector<char> > boardState, int player){
		this->boardState = boardState;
		this->Q = 0;
		this->num_visits = 0;
		this->player = player;
		this->parent = NULL;
	}

	bool isTerminal(){
		if(getWinner(this->boardState) == 3){
			return false;
		}
		return true;
	}

	int finalBestChild(){
		int maxVisit = 0;
		int index = 0;
		int childVisit;
		for(int i=0;i<this->visited_children.size();i++){
			childVisit = this->visited_children[i]->num_visits;
			if(childVisit >= maxVisit){
				maxVisit = childVisit;
				index = i;
			}
		}
		return index;
	}

	int bestChild(){
		int maxUCB = -10;
		int index = 0;
		float childUCB;
		for(int i=0;i<this->visited_children.size();i++){
			childUCB = this->visited_children[i]->getUCB();
			if(childUCB >= maxUCB){
				maxUCB = childUCB;
				index = i;
			}
		}
		return index;
	}

	float getUCB(){
		float c = 1.41;
		if(this->num_visits == 0){
			return -10.0;
		}
		float average_Q = ((float)this->Q)/((float)this->num_visits);
		float UCB = average_Q + c*sqrt((log10(this->parent->num_visits))/(this->num_visits));
		return UCB;
	}

	bool isFullyExpanded(){
		if(this->unvisited_children.size() == 0 && this->visited_children.size() != 0){
			return true;
		}
		return false;
	}

	pair<Node*, int> pickUnvisitedChildren(){
		int index = rand() % (this->unvisited_children.size());
		return make_pair(this->unvisited_children[index], index);
	}

	void updateScore(int result){
		this->Q += result;
	}
	
	bool isNoChildren(){
		if(this->unvisited_children.size() == 0 && this->visited_children.size() == 0){
			return true;
		}
		return false;
	}
};

class MCTS{
public:
	Node* rootNode;
	int numRollouts;

	MCTS(vector<vector<char> > boardState, int player){
		rootNode = new Node(boardState, player);
		numRollouts = 0;
	}

	vector<vector<char> > predictNextState(){
		time_t startTime = time(NULL);
		Node* tempRoot = this->rootNode;
		Node* nodeToExplore;
		int playoutResult;
		int result = 0;
		while(time(NULL) - startTime < 1){
			nodeToExplore = this->traverse(tempRoot);
			playoutResult = this->rollout(nodeToExplore);
			/*cout << playoutResult << endl;
			if(playoutResult == this->rootNode->player){
				result = 1;
			}
			if((3 - playoutResult) == this->rootNode->player){
				result = -1;
			}
			printBoard(nodeToExplore->boardState);
			*/
			this->backpropagate(nodeToExplore, playoutResult);
		}

		/*
		cout << "The num_visits of root are: " << tempRoot->num_visits << endl;

		for(int i=0;i<tempRoot->visited_children.size();i++){
			cout << "The num_visits are: " << tempRoot->visited_children[i]->num_visits << endl;
			cout << "The UCB Value are: " << tempRoot->visited_children[i]->getUCB() << endl;
		}
		*/
		int index = tempRoot->finalBestChild();
		// cout << this->numRollouts << endl;
		return tempRoot->visited_children[index]->boardState;
	}

	Node* traverse(Node* node){
		int index;
		while(node->isFullyExpanded()){
			index = node->bestChild();
			node = node->visited_children[index];
		}

		if(node->isTerminal()){
			return node;
		}

		if(node->isNoChildren()){
			this->expandNode(node);
		}
		
		pair<Node*, int> nodeInfo = node->pickUnvisitedChildren();
		Node* childNode = nodeInfo.first;
		index = nodeInfo.second;
		node->visited_children.push_back(childNode);
		node->unvisited_children.erase(node->unvisited_children.begin() + index);
		return childNode;
	}

	void expandNode(Node* node){
		vector<pair<int, int> > childrenMoveList = generateChildren(node->boardState);
		vector<vector<char> > tempNodeState;
		Node* tempNode;
		vector<Node*> childrenList;
		for(int i=0; i<childrenMoveList.size(); i++){
			tempNodeState = playMove(node->boardState, childrenMoveList[i].first, childrenMoveList[i].second, node->player);
			tempNode = new Node(tempNodeState, (3 - node->player));
			tempNode->parent = node;
			childrenList.push_back(tempNode);
		}
		node->unvisited_children = childrenList;
	}

	int rollout(Node* node){
		this->numRollouts += 1;
		vector<vector<char> > boardState = node->boardState;
		int index, player = node->player;
	    while(getWinner(boardState) == 3){
	    	vector<pair<int, int> > children = generateChildren(boardState);
	    	if(children.size() == 0){
	    		return 0;
	    	}
	    	index = rand() % (children.size());
	    	boardState = playMove(boardState, children[index].first, children[index].second, player);
	        player = 3 - player;
	    }
	    return getWinner(boardState);
	}


	// void backpropagate(Node* node, int result){
	// 	node->num_visits += 1;
	// 	if(this->isRoot(node)){
	// 		return;
	// 	}
	// 	node->updateScore(result);
	// 	this->backpropagate(node->parent, result);
	// }

	void backpropagate(Node* node, int playoutResult){
		node->num_visits += 1;
		if(this->isRoot(node)){
			return;
		}
		if(node->player == (3 - playoutResult)){
			node->updateScore(1);	
		}
		else if(node->player == (playoutResult)){
			node->updateScore(-1);
		}
		
		this->backpropagate(node->parent, playoutResult);
	}

	bool isRoot(Node* node){
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(node->boardState[i][j] != this->rootNode->boardState[i][j]){
					return false;
				}
			}
		}
		return true;
	}

};