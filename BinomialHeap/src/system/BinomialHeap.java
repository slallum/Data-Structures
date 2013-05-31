package system;


/**
 * BinomialHeap
 * 
 * An implementation of lazy binomial heap over non-negative integers.
 */
public class BinomialHeap {

	private BinomialTree rightMostTree;

	/** Root with minimum value in the heap */
	private BinomialTree minTree;

	/** How many roots saved in the heap */
	private int rootsCount = 0;

	/**
	 * Creates an empty binomial heap
	 */
	public BinomialHeap() {

	}

	/**
	 * Constructor with roots list
	 * 
	 * @param rightMostTree
	 */
	public BinomialHeap(BinomialTree rightMostTree) {
		this.rightMostTree = rightMostTree;
		this.rootsCount = 1;
		this.minTree = rightMostTree;
	}

	/**
	 * public boolean empty()
	 * 
	 * precondition: none
	 * 
	 * The method returns true if and only if the heap is empty.
	 * 
	 */
	public boolean empty() {
		return this.rightMostTree == null;
	}

	/**
	 * public void insert(int value)
	 * 
	 * Insert value into the heap
	 * 
	 */
	public void insert(int value) {
		BinomialTree newTree = new BinomialTree(value);

		if (this.size() == 0) {
			this.minTree = newTree;
			this.rightMostTree = newTree;
			this.rootsCount++;
			return;
		}

		newTree.setLeftSibling(this.rightMostTree);
		this.rightMostTree = newTree;

		if (value < minTree.getKey()) {
			this.minTree = newTree;
		}

		this.rootsCount++;
	}

	/**
	 * public void deleteMin()
	 * 
	 * Delete the minimum value. Return the number of linking actions that
	 * occured in the process.
	 * 
	 */
	public int deleteMin() {
		removeMinRoot();
		int linksCount = successiveLinking();
		findNewMin();
		return linksCount;
	}

	/**
	 * public int findMin()
	 * 
	 * Return the minimum value
	 * 
	 */
	public int findMin() {
		return minTree.getKey();
	}

	/**
	 * public void meld (BinomialHeap heap2)
	 * 
	 * Meld the heap with heap2
	 * 
	 */
	public void meld(BinomialHeap heap2) {

		BinomialTree current = this.rightMostTree;
		if (current == null) {
			this.rightMostTree = heap2.getRightMostTree();
			return;
		}
		while (current.getLeftSibling() != null) {
			current = current.getLeftSibling();
		}
		current.setLeftSibling(heap2.getRightMostTree());
	}

	/**
	 * public int size()
	 * 
	 * Return the number of elements in the heap
	 * 
	 */
	public int size() {
		int sum = 0;
		BinomialTree current = this.rightMostTree;
		while (current != null) {
			sum += current.size();
			current = current.getLeftSibling();
		}
		return sum;
	}

	/**
	 * public static int sortArray(int[] array)
	 * 
	 * Sort an array by using insert and deleteMin actions on a new heap. Return
	 * the number of linking actions that occured in the process.
	 * 
	 */
	public static int sortArray(int[] array) {
		BinomialHeap sortingHeap = new BinomialHeap();
		for (int i = 0; i < array.length; i++) {
			sortingHeap.insert(array[i]);
		}
		int linksCount = 0;
		for (int i = 0; i < array.length; i++) {
			array[i] = sortingHeap.getMinVal();
			linksCount += sortingHeap.deleteMin();
		}
		return linksCount;
	}

	/**
	 * public int[] treesRanks()
	 * 
	 * Return an array containing the ranks of the trees that represent the heap
	 * in ascending order.
	 * 
	 */
	public int[] treesRanks() {
		int[] ranksInOrder = new int[rootsCount];
		int ranksInd = 0;
		BinomialTree currentTree = this.rightMostTree;
		while (currentTree != null) {
			ranksInOrder[ranksInd] = currentTree.getRank();
			currentTree = currentTree.getLeftSibling();
		}
		return ranksInOrder;
	}
	
	/**
	 * @return	The minimal value currently in the heap
	 */
	public int getMinVal() {
		return this.minTree.getKey();
	}

	/* --- Private Methods --- */

	/**
	 * @return The number of links performed
	 */
	private int successiveLinking() {
		int linksCounter = 0;
		BinomialTree[] linkedTrees = new BinomialTree[rootsCount];
		BinomialTree current = this.rightMostTree;
		while (current != null) {
			BinomialTree next = current.getLeftSibling();
			BinomialTree treeToHang = linkedTrees[current.getRank()];
			if (treeToHang != null) {
				// Making sure that treeToHang is the maximum value between the
				// two
				if (current.getKey() > treeToHang.getKey()) {
					BinomialTree temp = treeToHang;
					treeToHang = current;
					current = temp;
				}
				// Removing the hanged one from the array and from the list of trees
				linkedTrees[treeToHang.getRank()] = null;
				this.removeTree(treeToHang);
				// Moving the linked tree up in array
				current.hangTree(treeToHang);
				linksCounter++;
			} else {
				linkedTrees[current.getRank()] = current;
				current = next;
			}
		}
		return linksCounter;
	}

	/**
	 * Removes the root from list of roots and melds it's list of sons with the
	 * roots of the tree
	 */
	private void removeMinRoot() {
		removeTree(this.minTree);
		this.meld(new BinomialHeap(this.minTree.getRightMostChild()));
	}

	private void removeTree(BinomialTree tree) {
		if (this.getRightMostTree() == tree) {
			this.rightMostTree = tree.getLeftSibling();
		}
		BinomialTree left = tree.getLeftSibling();
		BinomialTree right = tree.getRightSibling();
		if (left != null) {
			left.setRightSibling(right);			
		}
		if (right != null) {
			right.setLeftSibling(left);			
		}
		this.rootsCount--;
	}

	/**
	 * Find the minimal root between binomial heap's roots
	 */
	private void findNewMin() {
		BinomialTree current = this.rightMostTree;
		this.minTree = current;
		while (current != null) {
			if (current.getKey() < this.minTree.getKey()) {
				this.minTree = current;
			}
			current = current.getLeftSibling();
		}
	}

	/**
	 * @return The first root in roots' list of the heap
	 */
	private BinomialTree getRightMostTree() {
		return this.rightMostTree;
	}

	/**
	 * A binomial tree
	 * 
	 * @author Shir
	 */
	public class BinomialTree {

		/** The nodes parent. Null if there isn't */
		private BinomialTree parent = null;

		/** Sibling of tree to it's left */
		private BinomialTree leftSibling = null;

		/** Sibling of tree to it's right */
		private BinomialTree rightSibling = null;

		/** Most left child of tree */
		private BinomialTree mostLeftChild = null;

		/** Rank of tree as defined for binomial tree */
		private int rank;

		/** Node's element - non-negative non-unique integers */
		private int key;

		/**
		 * Constructor
		 */
		public BinomialTree(int key) {
			this.key = key;
			this.rank = 0;
		}

		/**
		 * @return the parent
		 */
		public BinomialTree getParent() {
			return parent;
		}

		/**
		 * @param parent
		 *            the parent to set
		 */
		public void setParent(BinomialTree parent) {
			this.parent = parent;
		}

		/**
		 * @return the leftSibling
		 */
		public BinomialTree getLeftSibling() {
			return leftSibling;
		}

		/**
		 * @param leftSibling
		 *            the leftSibling to set
		 */
		public void setLeftSibling(BinomialTree leftSibling) {
			this.leftSibling = leftSibling;
			if (leftSibling == null) {
				return;
			}

			this.leftSibling.rightSibling = this;

			if (this.getParent() == null) {
				return;
			}

			// update the leftmost child
			if (this.getParent().getMostLeftChild() == leftSibling
					.getRightSibling()) {
				this.parent.setMostLeftChild(this);
			}
		}

		/**
		 * @return the rightSibling
		 */
		public BinomialTree getRightSibling() {
			return rightSibling;
		}

		/**
		 * @param rightSibling
		 *            the rightSibling to set
		 */
		public void setRightSibling(BinomialTree rightSibling) {
			this.rightSibling = rightSibling;
			if (rightSibling == null) {
				return;
			}
			this.rightSibling.leftSibling = this;
		}

		/**
		 * @return the mostLeftChild
		 */
		public BinomialTree getMostLeftChild() {
			return mostLeftChild;
		}

		/**
		 * @param mostLeftChild
		 *            the mostLeftChild to set
		 */
		public void setMostLeftChild(BinomialTree mostLeftChild) {
			this.mostLeftChild = mostLeftChild;
			this.mostLeftChild.setParent(this);
		}

		/**
		 * @return the value
		 */
		public int getKey() {
			return key;
		}

		/**
		 * @param key
		 *            the value to set
		 */
		public void setKey(int key) {
			this.key = key;
		}

		/**
		 * @return the rank
		 */
		public int getRank() {
			return rank;
		}

		/**
		 * @param rank
		 *            the rank to set
		 */
		public void setRank(int rank) {
			this.rank = rank;
		}

		/**
		 * @return The size of the tree - amount of nodes
		 */
		public int size() {
			return (int) Math.pow(2, this.rank);
		}

		/**
		 * @param treeToHang
		 *            Tree to hang on current tree
		 */
		public void hangTree(BinomialTree treeToHang) {
			if (this.mostLeftChild == null) {
				this.setMostLeftChild(treeToHang);
				treeToHang.setRightSibling(null);
				treeToHang.setLeftSibling(null);
				this.rank++;
				return;
			}
			
			treeToHang.setRightSibling(this.mostLeftChild);
			treeToHang.setLeftSibling(null);
			this.mostLeftChild.setLeftSibling(treeToHang);
			this.rank++;
			this.mostLeftChild = treeToHang;
		}

		/**
		 * @return The most right son of the tree
		 */
		private BinomialTree getRightMostChild() {
			BinomialTree rightMost = this.getMostLeftChild();
			if (rightMost == null) {
				return null;
			}
			while (rightMost.getRightSibling() != null) {
				rightMost = rightMost.getRightSibling();
			}
			return rightMost;
		}

	}
}
