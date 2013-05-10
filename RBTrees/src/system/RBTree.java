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
		boolean isBlack = position.isBlack();
		RBNode nodeToFix;
		if ((position.getRight() == null) && (position.getLeft() == null)) {
			nodeToFix = new RBNode(null, null, null, DUMMY_VALUE, true);
			this.transplant(position, nodeToFix);
		} else if (position.getRight() == null) {
			this.transplant(position, position.getLeft());
			nodeToFix = position.getLeft();
		} else if (position.getLeft() == null) {
			this.transplant(position, position.getRight());
			nodeToFix = position.getRight();
		} else {
			nodeToFix = removeSuccessor(position);
			isBlack = nodeToFix.isBlack();
		}
		int rotations = isBlack ? fixDelete(nodeToFix) : 0;
		// If we added a dummy node for means of fixing
		if (isDummyNode(nodeToFix)) {
			nodeToFix.removeBelow();
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
	 * @return All keys of tree, in order
	 */
	public String treeToStr() {
		return this.root.order("in");
	}

	/**
	 * public int size()
	 * 
	 * Returns the number of nodes in the tree.
	 * 
	 * precondition: none postcondition: none
	 */
	public int size() {
		return this.root.size();
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
		if (oldNode.isBlack()) {
			newNode.setBlack();
		} else {
			newNode.setRed();
		}
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
		return nodeToFix;
	}

	/**
	 * @param nodeToFix
	 * @return
	 */
	private int fixDelete(RBNode nodeToFix) {
		int rotations = 0;
		while ((nodeToFix != this.root) && nodeToFix.isBlack()) {
			RBNode sibling = nodeToFix.getSibling();
			if (!nodeToFix.isRightSon()) {
				if (isDeleteCase1(sibling)) {
					sibling.setBlack();
					nodeToFix.getParent().setRed();
					nodeToFix.getParent().rotateLeft();
					sibling = nodeToFix.getParent().getRight();
					rotations++;
				}
				if (isDeleteCase2(sibling)) {
					nodeToFix = fixDeleteCase2(nodeToFix, sibling);
				} else {
					if (isDeleteCase3Left(sibling)) {
						sibling.getLeft().setBlack();
						sibling.setRed();
						sibling.rotateRight();
						rotations++;
						sibling = nodeToFix.getParent().getRight();
					}
					// Anyway fixing case 4
					if (nodeToFix.getParent().isBlack()) {
						sibling.setBlack();
					} else {
						sibling.setRed();
					}
					if (nodeToFix.getParent() != null) {
						nodeToFix.getParent().setBlack();
					}
					if (sibling.getRight() != null) {
						sibling.getRight().setBlack();
					}
					nodeToFix.getParent().rotateLeft();
					rotations++;
					fixRoot();
					nodeToFix = this.root;
				}
			} else {
				// Now dealing with left son
				if (isDeleteCase1(sibling)) {
					sibling.setBlack();
					nodeToFix.getParent().setRed();
					nodeToFix.getParent().rotateRight();
					rotations++;
					sibling = nodeToFix.getParent().getLeft();
				}
				if (isDeleteCase2(sibling)) {
					nodeToFix = fixDeleteCase2(nodeToFix, sibling);
				}
			}
			fixRoot();
		}
		nodeToFix.setBlack();
		return rotations;
	}

	/**
	 * @param sibling
	 * @return Whether setting fits case 3 of delete, when removing a left child
	 */
	private boolean isDeleteCase3Right(RBNode sibling) {
		return (sibling.getLeft() != null) && sibling.getLeft().isBlack();
	}

	/**
	 * @param sibling
	 * @return Whether setting fits case 3 of delete, when removing a left child
	 */
	private boolean isDeleteCase3Left(RBNode sibling) {
		return (sibling.getRight() != null) && sibling.getRight().isBlack();
	}

	/**
	 * @param sibling
	 * @return Whether setting fits with case 2 of delete
	 */
	private boolean isDeleteCase1(RBNode sibling) {
		return (sibling != null) && !sibling.isBlack();
	}

	/**
	 * @param nodeToFix
	 * @param sibling
	 * @return The node after fix
	 */
	private RBNode fixDeleteCase2(RBNode nodeToFix, RBNode sibling) {
		sibling.setRed();
		return nodeToFix.getParent();
	}

	/**
	 * @param sibling
	 *            Sibling of node to fix
	 * @return Whether setting fits with case 2 of delete
	 */
	private boolean isDeleteCase2(RBNode sibling) {
		return (sibling.getLeft() == null && sibling.getRight() == null)
				|| (sibling.getLeft().isBlack() && sibling.getRight().isBlack());
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
		 * 
		 * @param type
		 *            "pre" for pre-order values "post" for post-order values
		 *            "in" or "" for in-order values
		 * @return String of all node's keys in "type" order
		 */
		public String order(String type) {
			String right = (this.right != null) ? this.right.order(type)
					.toString() : "";
			String left = (this.left != null) ? this.left.order(type)
					.toString() : "";
			switch (type) {
			case "pre":
				return this.key + left + right;
			case "post":
				return left + right + this.key;
			default:
				return left + this.key + right;
			}
		}

		/**
		 * Calls recursively and sums sizes of children's nodes
		 * 
		 * @return The amount of nodes under current node inclusive
		 */
		public int size() {
			int sum = 1;
			if (this.right != null) {
				sum += this.right.size();
			}
			if (this.left != null) {
				sum += this.left.size();
			}
			return sum;
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
