

/*****************前序遍历*****************/

//前序遍历节点
static void TraversalNodeDLR(const TreeNode* _node, void* _function(TreeNode*), TreeNode* _crition)
{
	if (_node && _node != _crition)
	{
		ProcessNode(_node, _function);
		TraversalNodeDLR(_node->LeftChild, _function, _crition);
		TraversalNodeDLR(_node->RightChild, _function, _crition);
	}
}

//前序遍历树
static void TraversalDLR(const Tree* _tree, void* _function(TreeNode*), TreeNode* _crition)
{
	if (_tree && _tree->Root && _tree->Root != _crition)
	{
		TraversalNodeDLR(_tree->Root, _function, _crition);
	}
}

/*****************前序遍历*****************/

/*****************中序遍历*****************/
//中序遍历节点
static void TraversalNodeLDR(const TreeNode* _node, void* _function(TreeNode*), TreeNode* _crition)
{
	if (_node && _node != _crition)
	{
		TraversalNodeLDR(_node->LeftChild, _function, _crition);
		ProcessNode(_node, _function);
		TraversalNodeLDR(_node->RightChild, _function, _crition);
	}
}

//中序遍历树
static void TraversalLDR(const Tree* _tree, void* _function(TreeNode*), TreeNode* _crition)
{
	if (_tree && _tree->Root && _tree->Root != _crition)
	{
		TraversalNodeLDR(_tree->Root, _function, _crition);
	}
}

/*****************中序遍历*****************/

/*****************后序遍历*****************/
//后序遍历节点
static void TraversalNodeLRD(const TreeNode* _node, void* _function(TreeNode*), TreeNode* _crition)
{
	if (_node && _node != _crition)
	{
		TraversalNodeLRD(_node->LeftChild, _function, _crition);
		TraversalNodeLRD(_node->RightChild, _function, _crition);
		ProcessNode(_node, _function);
	}
}

//后序遍历树
static void TraversalLRD(const Tree* _tree, void* _function(TreeNode*), TreeNode* _crition)
{
	if (_tree && _tree->Root && _tree->Root != _crition)
	{
		TraversalNodeLRD(_tree->Root, _function, _crition);
	}
}

/*****************后序遍历*****************/

//遍历树
int TraversalTree(const Tree* _tree, TreeNode* _crition, TraversalMode _mode, void* _function(TreeNode*))
{
	switch (_mode)
	{
	case DLR:
		TraversalDLR(_tree, _function, _crition);
		return 1;
	case LDR:
		TraversalLDR(_tree, _function, _crition);
		return 1;
	case LRD:
		TraversalLRD(_tree, _function, _crition);
		return 1;
	default:
		return 0;
	}
	SwitchLine();
}

