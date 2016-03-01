# M-ary-Tree
Implementation of general purpose M-ary tree.

Operation:
==========


Maintenance history:
====================
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