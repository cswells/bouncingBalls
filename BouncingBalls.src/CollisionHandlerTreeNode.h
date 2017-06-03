#pragma once
#include "ball.h"
#include "QuadRectangle.h"
#include <iostream>
#include <new>
using namespace std;
class ball;


class CollisionHandlerTreeNode
{
public:
	//Data beind held by this OctalTree
	ball *list[100];
	int list_size;
	QuadRectangle *rect;

	//Nodes
	CollisionHandlerTreeNode *top_front_left;
	CollisionHandlerTreeNode *top_back_left;
	CollisionHandlerTreeNode *top_front_right;
	CollisionHandlerTreeNode *top_back_right;
	CollisionHandlerTreeNode *bottom_front_left;
	CollisionHandlerTreeNode *bottom_back_left;
	CollisionHandlerTreeNode *bottom_front_right;
	CollisionHandlerTreeNode *bottom_back_right;

	CollisionHandlerTreeNode(void);
	void clearAllLowerNodes(CollisionHandlerTreeNode *node);

	~CollisionHandlerTreeNode(void);
	
	
	void addBall(ball *b);
private:
	void clearAllLowerNodesHelper(CollisionHandlerTreeNode *node);
	CollisionHandlerTreeNode* buildTFLnode();
	CollisionHandlerTreeNode* buildTBLnode();
	CollisionHandlerTreeNode* buildBFLnode();
	CollisionHandlerTreeNode* buildBBLnode();
	CollisionHandlerTreeNode* buildTFRnode();
	CollisionHandlerTreeNode* buildTBRnode();
	CollisionHandlerTreeNode* buildBFRnode();
	CollisionHandlerTreeNode* buildBBRnode();
	
};

