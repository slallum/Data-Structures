/**
 * 
 * RBTree
 * 
 * An implementation of a Red Black Tree with non-negative, distinct integer
 * values
 * 
 */

public class RBTree {

	/**
	 * public boolean empty()
	 * 
	 * returns true if and only if the tree is empty
	 * 
	 */
	public boolean empty() {
		return false; // to be replaced by student code
	}

	/**
	 * public boolean search(int i)
	 * 
	 * returns i if the tree contains i otherwise, the closest value to i (in
	 * terms of absolute difference)
	 */
	public int search(int i) {
		return 0; // to be replaced by student code
	}

	/**
	 * public void insert(int i)
	 * 
	 * inserts the integer i into the binary tree; the tree must remain valid
	 * (keep its invariants). the function returns the number of rotations, or 0
	 * if i was already in the tree or no reotations were needed
	 */
	public int insert(int i) {
		return 0; // to be replaced by student code
	}

	/**
	 * public void delete(int i)
	 * 
	 * deletes the integer i from the binary tree, if it is there; the tree must
	 * remain valid (keep its invariants). the function returns the number of
	 * rotations, or 0 if i was not in the tree or no reotations were needed
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
		return; // to be replaced by student code
	}

	/**
	 * public int size()
	 * 
	 * Returns the number of nodes in the tree.
	 * 
	 * precondition: none postcondition: none
	 */
	public int size() {
		return 0; // to be replaced by student code
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
			this.left.setParent(this);
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
			this.right.setParent(this);
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
		 * @param isBlack
		 *            the isBlack to set
		 */
		public void setBlack(boolean isBlack) {
			this.isBlack = isBlack;
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

	}

	/**
	 * @original author Shai Vardi Modified for semester 2013 b
	 */

}
