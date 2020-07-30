#include "utils.h"

class Node{
public:
	vector<vector<char> > boardState;
	int player;
	int Q;
	int num_visits;
	vector<Node*> unvisited_children;
	vector<Node*> visited_children;
	Node* parent;

	Node(vector<vector<char> > boardState, int player);
	
	bool isTerminal();

	int finalBestChild();

	int bestChild();

	float getUCB();

	bool isFullyExpanded();

	pair<Node*, int> pickUnvisitedChildren();

	void updateScore(int result);
	
	bool isNoChildren();

};
