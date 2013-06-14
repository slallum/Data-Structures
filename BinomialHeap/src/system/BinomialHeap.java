package system;

/**
 * BinomialHeap
 * 
 * An implementation of lazy binomial heap over non-negative integers.
 */
public class BinomialHeap {

	/** First link in list of tree roots contained */
	private BinomialTree rightMostTree = null;

	/** Last link in list of tree roots */
	private BinomialTree leftMostTree = null;

	/** Root with minimum value in the heap */
	private BinomialTree minTree = null;

	/** How many roots saved in the heap */
	private int rootsCount = 0;

	/** Amount of elements in the heap */
	private int size = 0;

	/**
	 * Creates an empty binomial heap
	 */
	public BinomialHeap() {
		// Nothing to do
	}

	/**
	 * Constructor with roots list
	 * 
	 * @param rightMostTree
	 */
	public BinomialHeap(BinomialTree rightMostTree) {
		this.rightMostTree = rightMostTree;
		this.leftMostTree = rightMostTree;
		this.rootsCount = 0;
		if (this.rightMostTree != null) {
			BinomialTree current = this.rightMostTree;
			this.rootsCount++;
			this.size += current.size();
			while (current.getLeftSibling() != null) {
				current = current.getLeftSibling();
				this.rootsCount++;
				this.size += current.size();
			}
			this.leftMostTree = current;
		}
		this.findNewMin();
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
			this.leftMostTree = newTree;
		} else {
			newTree.setLeftSibling(this.rightMostTree);
			this.rightMostTree = newTree;

			if (value < minTree.getKey()) {
				this.minTree = newTree;
			}
		}
		this.size++;
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
		if (this.minTree != null) {
			removeMinRoot();
			if (this.size() == 0) {
				return 0;
			}
			int linksCount = successiveLinking();
			findNewMin();
			return linksCount;
		}
		return 0;
	}

	/**
	 * public int findMin()
	 * 
	 * Return the minimum value
	 * 
	 */
	public int findMin() {
		if (minTree == null) {
			return -1;
		}
		return minTree.getKey();
	}

	/**
	 * public void meld (BinomialHeap heap2)
	 * 
	 * Meld the heap with heap2
	 * 
	 */
	public void meld(BinomialHeap heap2) {
		// If heap2 is empty, stays as is
		if ((heap2 == null) || (heap2.getRightMostTree() == null)) {
			return;
		}
		// If ours is empty, just put heap2
		if (this.rightMostTree == null) {
			this.rightMostTree = heap2.getRightMostTree();
			this.leftMostTree = heap2.getLeftMostTree();
			this.rootsCount += heap2.getRootsCount();
			this.size += heap2.size();
			this.minTree = heap2.getMinTree();
			return;
		}
		// Need to combine both
		heap2.getLeftMostTree().setLeftSibling(this.getRightMostTree());
		this.rightMostTree = heap2.getRightMostTree();
		this.rootsCount += heap2.getRootsCount();
		this.size += heap2.size();
		if (heap2.findMin() < this.findMin()) {
			this.minTree = heap2.getMinTree();
		}
	}

	/**
	 * public int size()
	 * 
	 * Return the number of elements in the heap
	 * 
	 */
	public int size() {
		return this.size;
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
			array[i] = sortingHeap.findMin();
			linksCount += sortingHeap.deleteMin();
		}
		return linksCount;
	}

	/**
	 * public int[] treesRanks()
	 * 
	 * Return an array containing the ranks of the trees that represent the heap
	 * in ascending order. Just goes over in the order of the list, as we
	 * already made sure they are sorted, during the successive linking process
	 */
	public int[] treesRanks() {
		int[] ranks = new int[this.rootsCount];
		int maxRank = 0;
		int index = 0;
		BinomialTree currentTree = this.rightMostTree;
		while (currentTree != null) {
			if (currentTree.getRank() > maxRank) {
				maxRank = currentTree.getRank();
			}
			ranks[index] = currentTree.getRank();
			index++;
			currentTree = currentTree.getLeftSibling();
		}
		return this.countSort(ranks, maxRank);	
	}

	/* --- Private Methods --- */

	/**
	 * Goes over linked list of the nodes and inserts them into an array that
	 * keeps only one tree of each rank.
	 * 
	 * @return The number of links performed
	 */
	private int successiveLinking() {
		int linksCounter = 0;
		BinomialTree[] linkedTrees = new BinomialTree[BinomialHeap.log(this.size(), 2) + 1];
		BinomialTree current = this.rightMostTree;
		while (current != null) {
			BinomialTree next = current.getLeftSibling();
			removeTree(current);
			linksCounter += insertTree(current, linkedTrees);
			current = next;
		}
		recreateHeap(linkedTrees);
		return linksCounter;
	}

	/**
	 * Recursive function for inserting into an array of nodes, while each one
	 * is in the cell matching it's rank. If two are matching the same cell,
	 * must link them.
	 * 
	 * @param currentTree
	 * @param linkedTrees
	 */
	private int insertTree(BinomialTree currentTree, BinomialTree[] linkedTrees) {
		if (linkedTrees[currentTree.getRank()] == null) {
			linkedTrees[currentTree.getRank()] = currentTree;
			return 0;
		}
		BinomialTree previousTree = linkedTrees[currentTree.getRank()];
		linkedTrees[currentTree.getRank()] = null;
		// Swap in order to maintain heap-order
		if (previousTree.getKey() < currentTree.getKey()) {
			BinomialTree temp = currentTree;
			currentTree = previousTree;
			previousTree = temp;
		}
		currentTree.hangTree(previousTree);
		return 1 + insertTree(currentTree, linkedTrees);
	}

	/**
	 * Build heap from array containing nodes in un-consistent cells.
	 * 
	 * @param linkedTrees
	 */
	private void recreateHeap(BinomialTree[] linkedTrees) {
		BinomialTree current;

		// find the first node
		int i = 0;
		while ((i < linkedTrees.length) && (linkedTrees[i] == null)) {
			i++;
		}
		if (i < linkedTrees.length) {
			this.rightMostTree = linkedTrees[i];
			this.rootsCount = 1;
			this.size = this.rightMostTree.size();

			// add the next nodes
			current = this.rightMostTree;
			i++;
			while (i < linkedTrees.length) {
				if (linkedTrees[i] != null) {
					current.setLeftSibling(linkedTrees[i]);
					current = current.getLeftSibling();
					this.size += current.size();
					this.rootsCount++;
				}
				i++;
			}
			this.leftMostTree = current;
		}
	}

	/**
	 * Removes the root from list of roots and melds it's list of sons with the
	 * roots of the tree
	 */
	private void removeMinRoot() {
		if (this.minTree != null) {
			removeTree(this.minTree);
			this.meld(new BinomialHeap(this.minTree.getRightMostChild()));
			this.minTree = null;
		}
	}

	/**
	 * @param tree
	 */
	private void removeTree(BinomialTree tree) {
		if (tree != null) {
			if (this.getRightMostTree() == tree) {
				this.rightMostTree = tree.getLeftSibling();
			}
			if (this.getLeftMostTree() == tree) {
				this.leftMostTree = tree.getRightSibling();
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
			this.size -= tree.size();
			tree.setRightSibling(null);
			tree.setLeftSibling(null);
		}
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
	 * Uses a count-sort algorithm, as we know  the range of values we will have in the
	 * array (maxRank) and we also know that because of the data structure,
	 * the maximal rank will not be more than logn (n number of elements stored in the heap)
	 * So the work done by the method will be at most O(n)
	 * 
	 * @param ranks		All ranks as is in roots list 
	 * @param maxRank	Maximal rank between the ranks
	 * @return			ranks ordered
	 */
	private int[] countSort(int[] ranks, int maxRank) {
		int[] ranksCount = new int[maxRank + 1];
		for (int i = 0; i < ranks.length; i++) {
			ranksCount[ranks[i]]++;
		}
		int[] sortedRanks = new int[ranks.length];
		int countInd = 0;
		for (int i = 0; i < ranks.length; i++) {
			while (ranksCount[countInd] == 0) {
				countInd++;
			}
			sortedRanks[i] = countInd;
			ranksCount[countInd]--;
		}
		return sortedRanks;
	}

	/**
	 * @return The first root in roots' list of the heap
	 */
	private BinomialTree getRightMostTree() {
		return this.rightMostTree;
	}

	/**
	 * @return The first root in roots' list of the heap
	 */
	private BinomialTree getLeftMostTree() {
		return this.leftMostTree;
	}

	/**
	 * @return
	 */
	private int getRootsCount() {
		return this.rootsCount;
	}

	/**
	 * @return
	 */
	private BinomialTree getMinTree() {
		return this.minTree;
	}
	
	static int log(int x, int base)
	{
	    return (int) (Math.log(x) / Math.log(base));
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
			if (this.leftSibling != null) {
				this.leftSibling.rightSibling = this;
				if (this.getParent() != null) {
					// update the leftmost child
					if (this.getParent().getMostLeftChild() == leftSibling
							.getRightSibling()) {
						this.parent.setMostLeftChild(this);
					}
				}
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
			} else {
				treeToHang.setRightSibling(this.mostLeftChild);
				treeToHang.setLeftSibling(null);
				this.mostLeftChild.setLeftSibling(treeToHang);
				this.rank++;
				this.mostLeftChild = treeToHang;
			}
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
