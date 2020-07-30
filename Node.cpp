#include "Node.h"

Node::Node(vector<vector<char> > boardState, int player){
	this->boardState = boardState;
	this->Q = 0;
	this->num_visits = 0;
	this->player = player;
	this->parent = NULL;
}

bool Node::isTerminal(){
	if(getWinner(this->boardState) == 3){
		return false;
	}
	return true;
}

int Node::finalBestChild(){
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

int Node::bestChild(){
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

float Node::getUCB(){
	float c = 1.41;
	if(this->num_visits == 0){
		return -10.0;
	}
	float average_Q = ((float)this->Q)/((float)this->num_visits);
	float UCB = average_Q + c*sqrt((log10(this->parent->num_visits))/(this->num_visits));
	return UCB;
}

bool Node::isFullyExpanded(){
	if(this->unvisited_children.size() == 0 && this->visited_children.size() != 0){
		return true;
	}
	return false;
}

pair<Node*, int> Node::pickUnvisitedChildren(){
	int index = rand() % (this->unvisited_children.size());
	return make_pair(this->unvisited_children[index], index);
}

void Node::updateScore(int result){
	this->Q += result;
}

bool Node::isNoChildren(){
	if(this->unvisited_children.size() == 0 && this->visited_children.size() == 0){
		return true;
	}
	return false;
}
