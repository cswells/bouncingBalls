#include "CollisionHandlerTreeNode.h"


CollisionHandlerTreeNode::CollisionHandlerTreeNode(void)
{
	list_size = 0;
}

void CollisionHandlerTreeNode::addBall(ball *b)
{
	
}

void CollisionHandlerTreeNode::clearAllLowerNodes(CollisionHandlerTreeNode *node)
{
	if(node != NULL)
	{
		clearAllLowerNodesHelper(node->top_front_left);
		clearAllLowerNodesHelper(node->top_back_left);
		clearAllLowerNodesHelper(node->top_front_right);
		clearAllLowerNodesHelper(node->top_back_right);

		clearAllLowerNodesHelper(node->bottom_front_left);
		clearAllLowerNodesHelper(node->bottom_back_left);
		clearAllLowerNodesHelper(node->bottom_front_right);
		clearAllLowerNodesHelper(node->bottom_back_right);
	}
}

void CollisionHandlerTreeNode::clearAllLowerNodesHelper(CollisionHandlerTreeNode *node)
{
	if(node != NULL)
	{
		clearAllLowerNodesHelper(node->top_front_left);
		clearAllLowerNodesHelper(node->top_back_left);
		clearAllLowerNodesHelper(node->top_front_right);
		clearAllLowerNodesHelper(node->top_back_right);

		clearAllLowerNodesHelper(node->bottom_front_left);
		clearAllLowerNodesHelper(node->bottom_back_left);
		clearAllLowerNodesHelper(node->bottom_front_right);
		clearAllLowerNodesHelper(node->bottom_back_right);

		delete node;
	}
}

CollisionHandlerTreeNode::~CollisionHandlerTreeNode(void)
{

}
