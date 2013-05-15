package system;

/**
 * 
 * RBTree
 * 
 * An implementation of a Red Black Tree with non-negative, distinct integer
 * values
 * 
 */

public class RBTree {

	private static final int DUMMY_VALUE = -1;

	/** Starts the tree */
	private RBNode root;
	
	/** Counts how many nodes in data structure */
	private int size = 0;
	
	private boolean isBlack;

	/**
	 * @param root
	 */
	public RBTree(RBNode root) {
		this.root = root;
	}

	/**
	 * 
	 */
	public RBTree() {

	}

	/**
	 * public boolean empty()
	 * 
	 * returns true if and only if the tree is empty
	 * 
	 */
	public boolean empty() {
		if (this.root == null) {
			return true;
		}
		return false;
	}

	/**
	 * public boolean search(int i)
	 * 
	 * returns i if the tree contains i otherwise, the closest value to i (in
	 * terms of absolute difference)
	 */
	public int search(int i) {
		if (this.empty()) {
			return -1;
		}
		
		int minVal = min();
		int maxVal = max();
		RBNode current = this.root;
		while (current != null) {
			// Found it!
			if (current.getKey() == i) {
				return i;
			}
			if (current.getKey() > i) {
				// Need to go left in tree
				if (current.getKey() < maxVal) {
					maxVal = current.getKey();
				}
				current = current.getLeft();
			} else {
				// Need to go right in tree
				if (current.getKey() < minVal) {
					minVal = current.getKey();
				}
				current = current.getRight();
			}
		}
		// Return value closest to i
		if (i - minVal > maxVal - i) {
			return maxVal;
		}
		// If same distance, return smaller value
		return minVal;
	}

	/**
	 * public void insert(int i)
	 * 
	 * inserts the integer i into the binary tree; the tree must remain valid
	 * (keep its invariants). the function returns the number of rotations, or 0
	 * if i was already in the tree or no reotations were needed
	 */
	public int insert(int i) {
		if (this.empty()) {
			this.root = new RBNode(null, null, null, i, true);
			this.size++;
			return 0;
		}

		RBNode position = this.root.getPosition(i);
		if (position.key == i) {
			return 0;
		}

		RBNode newNode = new RBNode(position, null, null, i, false);
		if (position.key > i) {
			position.setLeft(newNode);
		} else {
			position.setRight(newNode);
		}
		this.size++;
		return fixInsert(newNode);
	}

	/**
	 * public void delete(int i)
	 * 
	 * deletes the integer i from the binary tree, if it is there; the tree must
	 * remain valid (keep its invariants). the function returns the number of
	 * rotations, or 0 if i was not in the tree or no rotations were needed
	 */
	public int delete(int i) {
		RBNode position = this.root.getPosition(i);
		if (position.getKey() != i) {
			return 0;
		}
		this.size--;
		isBlack = position.isBlack();
		RBNode nodeToFix;
		if ((position.getRight() == null) && (position.getLeft() == null)) {
			nodeToFix = new RBNode(null, null, null, DUMMY_VALUE, true);
			this.transplant(position, nodeToFix);
		} else if (position.getRight() == null) {
			nodeToFix = position.getLeft();
			nodeToFix.moveUp();
			
		} else if (position.getLeft() == null) {
			nodeToFix = position.getRight();
			nodeToFix.moveUp();
		} else {
			nodeToFix = removeSuccessor(position);
		}
		if (nodeToFix.getParent() == null) {
			this.root = nodeToFix;
		}
		int rotations = isBlack ? fixDelete(nodeToFix) : 0;
		// If we added a dummy node for means of fixing
		if (isDummyNode(nodeToFix)) {
			if (nodeToFix.getParent() == null) {
				this.root = null;
			} else {
				nodeToFix.removeBelow();
			}
		}
		return rotations;
	}

	/**
	 * public int min()
	 * 
	 * Returns the smallest key in the tree, or -1 if the tree is empty is
	 * empty, returns -1;
	 * 
	 */
	public int min() {
		if (empty()) {
			return DUMMY_VALUE;
		}
		RBNode current = this.root;
		while (current.left != null) {
			current = current.left;
		}
		return current.key;
	}

	/**
	 * public int max()
	 * 
	 * Returns the largest key in the tree, or -1 if the tree is empty
	 */
	public int max() {
		if (empty()) {
			return DUMMY_VALUE;
		}
		RBNode current = this.root;
		while (current.right != null) {
			current = current.right;
		}
		return current.key;
	}

	/**
	 * public void arrayToTree(int[] )
	 * 
	 * inserts the array of integers to the tree. if the tree contained elements
	 * before, they should be discarded the array contains integers in ascending
	 * order.
	 * 
	 */
	public void arrayToTree(int[] array) {
		this.root = new RBNode(null, null, null, array[0], true);
		RBNode current = this.root;
		for (int i = 1; i < array.length; i++) {
			RBNode newNode = new RBNode(current, null, null, array[i], false);
			// Adding to the right because we assume array is in ASC order
			current.setRight(newNode);
			fixInsert(newNode);
			current = newNode;
		}
	}

	/**
	 * public int size()
	 * 
	 * Returns the number of nodes in the tree.
	 * 
	 * precondition: none postcondition: none
	 */
	public int size() {
		return this.size;
	}

	// *** Private Methods ***//

	/**
	 * @param oldNode
	 *            The node to replace
	 * @param newNode
	 *            The node to place instead
	 */
	private void transplant(RBNode oldNode, RBNode newNode) {
		newNode.setParent(oldNode.getParent());
		newNode.setLeft(oldNode.getLeft());
		newNode.setRight(oldNode.getRight());
		if (oldNode.getParent() == null) {
			this.root = newNode;
		} else if (oldNode.isRightSon()) {
			oldNode.getParent().setRight(newNode);
		} else {
			oldNode.getParent().setLeft(newNode);
		}
	}

	/**
	 * @param newNode
	 * @return the number of rotations done for the fix
	 */
	private int fixInsert(RBNode nodeToCheck) {
		int rotationsCount = 0;
		while ((nodeToCheck.getParent() != null)
				&& !nodeToCheck.getParent().isBlack()) {
			RBNode uncle = nodeToCheck.getUncle();
			boolean isRightUncle = !nodeToCheck.getParent().isRightSon();
			// case 1
			if ((uncle != null) && (!uncle.isBlack())) {
				uncle.setBlack();
				nodeToCheck.getParent().setBlack();
				nodeToCheck = nodeToCheck.getParent().getParent();
				nodeToCheck.setRed();
			} else {
				// case 2
				if ((isRightUncle) && (nodeToCheck.isRightSon())) {
					nodeToCheck = nodeToCheck.getParent();
					nodeToCheck.rotateLeft();
					rotationsCount++;
				} else if ((!isRightUncle) && (!nodeToCheck.isRightSon())) {
					nodeToCheck = nodeToCheck.getParent();
					nodeToCheck.rotateRight();
					rotationsCount++;
				}
				fixCase3(nodeToCheck, isRightUncle);
				rotationsCount++;
			}
		}
		this.root.setBlack();
		return rotationsCount;
	}

	/**
	 * @param nodeToFix
	 * @param isRightUncle
	 */
	private void fixCase3(RBNode nodeToFix, boolean isRightUncle) {
		nodeToFix.getParent().setBlack();
		nodeToFix.getParent().getParent().setRed();
		if (isRightUncle) {
			nodeToFix.getParent().getParent().rotateRight();
		} else {
			nodeToFix.getParent().getParent().rotateLeft();
		}
		fixRoot();
	}

	/**
	 * If root has changed, i.e. current root has a parent, go up until no
	 * parents - that should be the root
	 */
	private void fixRoot() {
		while (this.root.getParent() != null) {
			this.root = this.root.getParent();
		}
	}

	/**
	 * @param position
	 *            The node to replace
	 * @return The node that was put in instead, should be it's successor
	 */
	private RBNode removeSuccessor(RBNode position) {
		RBNode nextPosition = position.successor();
		isBlack = nextPosition.isBlack();
		// Need to fix where removed
		RBNode nodeToFix = nextPosition.getRight();
		// No node to fix - need to put a dummy instead
		if (nodeToFix == null) {
			nodeToFix = new RBNode(null, null, null, DUMMY_VALUE, true);
			this.transplant(nextPosition, nodeToFix);
		}
		// Successor is immediate right son
		if (nextPosition.getParent() == position) {
			position.setRight(nodeToFix);
		} else {
			// Successor is most left of right son
			nextPosition.getParent().setLeft(nodeToFix);
		}
		this.transplant(position, nextPosition);
		setSameColor(position, nextPosition);
		return nodeToFix;
	}

	/**
	 * Make nextPosition have same color of position
	 * 
	 * @param position
	 * @param nextPosition
	 */
	private void setSameColor(RBNode position, RBNode nextPosition) {
		if (position.isBlack) {
			nextPosition.setBlack();
		} else {
			nextPosition.setRed();
		}
	}

	/**
	 * Need to fix the extra blackness in the tree of nodeToFix, 
	 * by the removal of it's parent
	 * 
	 * @param nodeToFix
	 * @return
	 */
	private int fixDelete(RBNode nodeToFix) {
		int rotations = 0;
		while ((nodeToFix != this.root) && nodeToFix.isBlack()) {
			RBNode sibling = nodeToFix.getSibling();
			if (!nodeToFix.isRightSon()) {
				if (isDeleteCase1(sibling)) {
					sibling = fixDeleteCase1Left(nodeToFix, sibling);
					rotations++;
					this.fixRoot();
				}
				if (isDeleteCase2(sibling)) {
					nodeToFix = fixDeleteCase2(nodeToFix, sibling);
					// dummySibling can only happen in case2
					if (isDummyNode(sibling)) {
						sibling.removeBelow();
					}
				} else {
					if (isDeleteCase3Left(sibling)) {
						sibling = fixDeleteCase3Left(nodeToFix, sibling);
						rotations++;
					}
					// Case 3 fix causes case 4
					fixDeleteCase4(nodeToFix, sibling);
					nodeToFix = fixDeleteCase4Left(nodeToFix, sibling);
					rotations++;
				}
			} else {
				// Now dealing with right son
				if (isDeleteCase1(sibling)) {
					sibling = fixDeleteCase1Right(nodeToFix, sibling);
					rotations++;
					this.fixRoot();
				}
				if (isDeleteCase2(sibling)) {
					nodeToFix = fixDeleteCase2(nodeToFix, sibling);
					// dummySibling can only happen in case2
					if (isDummyNode(sibling)) {
						sibling.removeBelow();
					}
				} else {
					if (isDeleteCase3Right(sibling)) {
						sibling = fixDeleteCase3Right(nodeToFix, sibling);
					}
					// Anyway fixing case 4
					fixDeleteCase4(nodeToFix, sibling);
					nodeToFix = fixDeleteCase4Right(nodeToFix, sibling);
					rotations++;
				}
			}
			this.fixRoot();
		}
		nodeToFix.setBlack();
		return rotations;
	}

	/**
	 * Sibling is red
	 * 
	 * @param sibling
	 * @return Whether setting fits with case 2 of delete
	 */
	private boolean isDeleteCase1(RBNode sibling) {
		return (sibling != null) && !sibling.isBlack();
	}

	/**
	 * Sibling of right child is red - need to colour parent red and rotate left
	 * 
	 * @param nodeToFix
	 * @param sibling
	 * @return
	 */
	private RBNode fixDeleteCase1Right(RBNode nodeToFix, RBNode sibling) {
		sibling.setBlack();
		nodeToFix.getParent().setRed();
		nodeToFix.getParent().rotateRight();
		sibling = nodeToFix.getParent().getLeft();
		if (sibling == null) {
			sibling = new RBNode(null, null, null, DUMMY_VALUE, true);
			nodeToFix.getParent().setLeft(sibling);
		}
		return sibling;
	}

	/**
	 * Sibling of left child is red - need to colour parent red and rotate right
	 * 
	 * @param nodeToFix
	 * @param sibling
	 * @return
	 */
	private RBNode fixDeleteCase1Left(RBNode nodeToFix, RBNode sibling) {
		sibling.setBlack();
		nodeToFix.getParent().setRed();
		nodeToFix.getParent().rotateLeft();
		sibling = nodeToFix.getParent().getRight();
		if (sibling == null) { 
			sibling = new RBNode(null, null, null, DUMMY_VALUE, true);
			nodeToFix.getParent().setRight(sibling);
		}
		return sibling;
	}

	/**
	 * Both sons of sibling are black
	 * 
	 * @param sibling
	 *            Sibling of node to fix
	 * @return Whether setting fits with case 2 of delete
	 */
	private boolean isDeleteCase2(RBNode sibling) {
		if (sibling.getLeft() == null && sibling.getRight() == null) {
			return true;
		}
		if (sibling.getLeft() == null) {
			return sibling.getRight().isBlack();
		}
		if (sibling.getLeft().isBlack()) {
			if (sibling.getRight() == null) {
				return true;
			}
			return sibling.getRight().isBlack();
		}
		return false;
	}

	/**
	 * Making the sibling red is enough for now but moving up as 'extra
	 * blackness' went up
	 * 
	 * @param nodeToFix
	 * @param sibling
	 * @return The node after fix
	 */
	private RBNode fixDeleteCase2(RBNode nodeToFix, RBNode sibling) {
		sibling.setRed();
		return nodeToFix.getParent();
	}

	/**
	 * Siblings
	 * 
	 * @param sibling
	 * @return Whether setting fits case 3 of delete, when removing a left child
	 */
	private boolean isDeleteCase3Right(RBNode sibling) {
		return (sibling.getLeft() == null) || sibling.getLeft().isBlack();
	}

	/**
	 * @param sibling
	 * @return Whether setting fits case 3 of delete, when removing a left child
	 */
	private boolean isDeleteCase3Left(RBNode sibling) {
		return (sibling.getRight() == null) || sibling.getRight().isBlack();
	}

	/**
	 * Siblings children are red and black, from right to left
	 * 
	 * @param nodeToFix
	 * @param sibling
	 * @return
	 */
	private RBNode fixDeleteCase3Left(RBNode nodeToFix, RBNode sibling) {
		if (sibling.getLeft() != null) {
			sibling.getLeft().setBlack();
		}
		sibling.setRed();
		sibling.rotateRight();
		sibling = nodeToFix.getParent().getRight();
		return sibling;
	}

	/**
	 * Siblings children are red and black, from left to right
	 * 
	 * @param nodeToFix
	 * @param sibling
	 * @return
	 */
	private RBNode fixDeleteCase3Right(RBNode nodeToFix, RBNode sibling) {
		if (sibling.getLeft() != null) {
			sibling.getLeft().setBlack();
		}
		sibling.setRed();
		sibling.rotateLeft();
		sibling = nodeToFix.getParent().getLeft();
		return sibling;
	}

	/**
	 * 
	 * 
	 * @param nodeToFix
	 * @param sibling
	 * @return
	 */
	private RBNode fixDeleteCase4Left(RBNode nodeToFix, RBNode sibling) {
		if (sibling.getRight() != null) {
			sibling.getRight().setBlack();
		}
		nodeToFix.getParent().rotateLeft();
		fixRoot();
		nodeToFix = this.root;
		return nodeToFix;
	}

	/**
	 * @param nodeToFix
	 * @param sibling
	 * @return
	 */
	private RBNode fixDeleteCase4Right(RBNode nodeToFix, RBNode sibling) {
		if (sibling.getLeft() != null) {
			sibling.getLeft().setBlack();
		}
		nodeToFix.getParent().rotateRight();
		fixRoot();
		nodeToFix = this.root;
		return nodeToFix;
	}

	/**
	 * @param nodeToFix
	 * @param sibling
	 */
	private void fixDeleteCase4(RBNode nodeToFix, RBNode sibling) {
		setSameColor(nodeToFix.getParent(), sibling);
		if (nodeToFix.getParent() != null) {
			nodeToFix.getParent().setBlack();
		}
	}

	/**
	 * @param nodeToCheck
	 *            Check if was dummy
	 * @return Is a dummy node we created ourselves
	 */
	private boolean isDummyNode(RBNode nodeToCheck) {
		return nodeToCheck.getKey() == DUMMY_VALUE;
	}

	/**
	 * public class RBNode
	 * 
	 * If you wish to implement classes other than RBTree (for example RBNode),
	 * do it in this file, not in another file
	 * 
	 */
	public class RBNode {
		/** Parent holding this node */
		private RBNode parent;

		/** Left son */
		private RBNode left;

		/** Right son */
		private RBNode right;

		/** Ordered key */
		private int key;

		/** Whether this node is black or red otherwise */
		private boolean isBlack;

		public RBNode(RBNode parent, RBNode left, RBNode right, int key,
				boolean isBlack) {
			this.parent = parent;
			this.left = left;
			this.right = right;
			this.key = key;
			this.isBlack = isBlack;
		}

		/**
		 * Takes the right sided son, according to position of current node
		 * 
		 * @return The son of the same parent
		 */
		public RBNode getSibling() {
			if (this.isRightSon()) {
				return this.getParent().getLeft();
			} else {
				return this.getParent().getRight();
			}
		}

		/**
		 * @return If parent has a sibling, return it
		 */
		public RBNode getUncle() {
			if (this.getParent().getParent() != null) {
				if (this.getParent().getParent().getLeft() == this.getParent()) {
					return this.getParent().getParent().getRight();
				} else if (this.getParent().getParent().getRight() == this
						.getParent()) {
					return this.getParent().getParent().getLeft();
				}
			}
			return null;
		}

		/**
		 * @return the parent
		 */
		public RBNode getParent() {
			return parent;
		}

		/**
		 * @param parent
		 *            the parent to set
		 */
		public void setParent(RBNode parent) {
			this.parent = parent;
		}

		/**
		 * @return the left
		 */
		public RBNode getLeft() {
			return left;
		}

		/**
		 * @param left
		 *            the left to set
		 */
		public void setLeft(RBNode left) {
			this.left = left;
			if (this.left != null) {
				this.left.setParent(this);
			}
		}

		/**
		 * @return the right
		 */
		public RBNode getRight() {
			return right;
		}

		/**
		 * @param right
		 *            the right to set
		 */
		public void setRight(RBNode right) {
			this.right = right;
			if (this.right != null) {
				this.right.setParent(this);
			}
		}

		/**
		 * @return the key
		 */
		public int getKey() {
			return key;
		}

		/**
		 * @param key
		 *            the key to set
		 */
		public void setKey(int key) {
			this.key = key;
		}

		/**
		 * @return the isBlack
		 */
		public boolean isBlack() {
			return isBlack;
		}

		/**
		 * Make the node black
		 */
		public void setBlack() {
			this.isBlack = true;
		}

		/**
		 * Make the node red
		 */
		public void setRed() {
			this.isBlack = false;
		}

		/**
		 * replaces the current node with its father if this.parent.parent is
		 * Null - returns false
		 * 
		 * @throws InvalidOperationException
		 *             If no parent to replace
		 */
		private void moveUp() {
			if ((this.parent == null) || (this.parent.getParent() == null)) {
				if ((this.parent.getParent() == null)) {
					this.parent = null;
				}
				return;
			}

			if (this.parent.isRightSon()) {
				this.parent.getParent().setRight(this);
			} else {
				this.parent.getParent().setLeft(this);
			}
		}

		/**
		 * Takes current Node's left son, moves it up, it's right son to be it's
		 * parent's left son and the parent to be it's right son
		 */
		public void rotateRight() {
			RBNode y = this.left;
			if (y == null) {
				return;
			}
			y.moveUp();
			this.setLeft(y.getRight());
			y.setRight(this);
		}

		/**
		 * Takes current Node's right son, moves it up, it's left son to be it's
		 * parent's right son and the parent to be it's left son
		 */
		public void rotateLeft() {

			RBNode right = this.right;
			if (right == null) {
				return;
			}
			right.moveUp();
			this.setRight(right.getLeft());
			right.setLeft(this);
		}

		/**
		 * @param key
		 *            Value to look for in keys
		 * @return The node containing the value or the position to insert it
		 */
		public RBNode getPosition(int key) {
			if (this.key == key) {
				return this;
			}
			RBNode next;
			if (this.key > key) {
				next = this.left;
			} else {
				next = this.right;
			}

			if (next == null) {
				return this;
			}
			return next.getPosition(key);
		}

		/**
		 * @return Node with smallest key which is larger than current
		 */
		public RBNode successor() {
			RBNode current;
			// this node has a right child
			if (this.right != null) {
				current = this.right;
				while (current.getLeft() != null) {
					current = current.getLeft();
				}
				return current;
			}

			current = this;
			// get the first right ancestor:
			// go up until you are a left child or you can't go up anymore
			// (which will mean that this node is the max node).
			while ((current.getParent() != null)
					&& (current.getParent().getRight() == current)) {
				current = current.getParent();
			}

			// this will return null of current is the maximum node (the most
			// right node)

			// or it will return the first right ancestor
			return current.getParent();
		}

		/**
		 * Remove everything under this node inclusive
		 */
		public void removeBelow() {
			if (this.isRightSon()) {
				this.getParent().setRight(null);
			} else {
				this.getParent().setLeft(null);
			}
		}

		/**
		 * @return Whether current node is a right son of given node
		 */
		public boolean isRightSon() {
			return this == this.getParent().getRight();
		}

	}

	public RBNode getRoot() {
		return this.root;
	}

	/**
	 * @original author Shai Vardi Modified for semester 2013 b
	 */

}
