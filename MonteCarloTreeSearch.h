#include "Node.h"

class MCTS{
public:
	Node* rootNode;
	int numRollouts;

	MCTS(vector<vector<char> > boardState, int player);

	vector<vector<char> > predictNextState();
	
	Node* traverse(Node* node);

	void expandNode(Node* node);

	int rollout(Node* node);

	void backpropagate(Node* node, int playoutResult);

	bool isRoot(Node* node);

};