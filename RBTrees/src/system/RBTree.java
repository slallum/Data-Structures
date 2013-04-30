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

	/** Starts the tree */
	private RBNode root;

	public RBTree(RBNode root) {
		this.root = root;
	}

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
	 * @param newNode
	 * @return the number of rotations done for the fix
	 */
	private int fixInsert(RBNode nodeToCheck) {
		int rotationsCount = 0;
		while (!nodeToCheck.getParent().isBlack()) {
			RBNode uncle = nodeToCheck.getUncle();
			boolean isRightUncle = !nodeToCheck.getParent().isRightSon();
			// case 1
			if ((uncle != null) && (!uncle.isBlack())) {
				uncle.setBlack();
				nodeToCheck.getParent().setBlack();
				nodeToCheck = nodeToCheck.getParent().getParent();
			}
			else {
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
	}

	
	/**
	 * public void delete(int i)
	 * 
	 * deletes the integer i from the binary tree, if it is there; the tree must
	 * remain valid (keep its invariants). the function returns the number of
	 * rotations, or 0 if i was not in the tree or no rotations were needed
	 */
	public int delete(int i) {
		return 0; // to be replaced by student code
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
			return -1;
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
			return -1;
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
		for (int i = 1; i < array.length; i++) {
			this.insert(array[i]);
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

		public RBNode getUncle() {
			// TODO Auto-generated method stub
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
				return;
			}

			if (this.parent == this.parent.getParent().getLeft()) {
				this.parent.getParent().setLeft(this);
			} else {
				this.parent.getParent().setRight(this);
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
				current = this.right.getLeft();
				while (current != null) {
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
			// righ node)
			// or it will return the first right ancestor
			return current.getParent();
		}

		/**
		 * @return	Whether current node is a right son of given node
		 */
		private boolean isRightSon() {
			return this == this.getParent().getRight();
		}
	}
	


	/**
	 * @original author Shai Vardi Modified for semester 2013 b
	 */

}
