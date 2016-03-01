M-ary Tree:	
===========
Implement generic M-ary Tree. 


Operation:
==========


Maintenance history:
====================
	Version 1.2 | 1 March 2016
	--------------------------
		Details: 1) Modified constructors and AddChildren method to work with "_name" variable.
				 2) Added methods show and ShowHelper for printing trees. 
				 3) Added few example statements in main function.

	Version 1.1	| 1 March 2016
	--------------------------
		Details: 1) Added methods FindByID and FindByIdHelper for finding[1] any unique[2] node.
				 2) Added method returnID which returns an unique[2] ID of a node.

	Version 1.0 | Initial commit -- 29 February 2016.
	-------------------------------------------------
		Details: Created template class MNode and added it's member variables and methods.



References:
===========
	[1] Uses Preorder traversal operation.
	[2]	No two nodes must have the same IDs. IDs are std::string type.
