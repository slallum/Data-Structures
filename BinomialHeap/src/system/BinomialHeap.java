package system;

import java.util.ArrayList;
import java.util.LinkedList;

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
		BinomialTree newTree = new BinomialTree(null, null, null, null, value);
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
		return 42; // should be replaced by student code
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
		return; // should be replaced by student code
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
		return 42; // to be replaced by student code
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
		while (currentTree.getLeftSibling() != null) {
			ranksInOrder[ranksInd] = currentTree.getRank();
		}
		return ranksInOrder;
	}

	/* --- Private Methods --- */

	private int successiveLinking() {
		int linksCounter = 0;

		return linksCounter;
	}

	/**
	 * A binomial tree
	 * 
	 * @author Shir
	 */
	public class BinomialTree {

		/** The nodes parent. Null if there isn't */
		private BinomialTree parent;

		/** Sibling of tree to it's left */
		private BinomialTree leftSibling;

		/** Sibling of tree to it's right */
		private BinomialTree rightSibling;

		/** Most left child of tree */
		private BinomialTree mostLeftChild;

		/** Rank of tree as defined for binomial tree */
		private int rank;

		/** Node's element - non-negative non-unique integers */
		private int key;

		/**
		 * Constructor
		 */
		public BinomialTree(BinomialTree parent, BinomialTree leftSibling,
			BinomialTree rightSibling, BinomialTree mostLeftChild, int key) {
			this.setParent(parent);
			this.setLeftSibling(leftSibling);
			this.setRightSibling(rightSibling);
			this.setMostLeftChild(mostLeftChild);
			this.key = key;
			this.setRank(mostLeftChild.getRank() + 1);
		}

		/**
		 * @return the parent
		 */
		public BinomialTree getParent() {
			return parent;
		}

		/**
		 * @param parent the parent to set
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
		 * @param leftSibling the leftSibling to set
		 */
		public void setLeftSibling(BinomialTree leftSibling) {
			this.leftSibling = leftSibling;
			this.leftSibling.setRightSibling(this);
		}

		/**
		 * @return the rightSibling
		 */
		public BinomialTree getRightSibling() {
			return rightSibling;
		}

		/**
		 * @param rightSibling the rightSibling to set
		 */
		public void setRightSibling(BinomialTree rightSibling) {
			this.rightSibling = rightSibling;
			this.rightSibling.setLeftSibling(this);
		}

		/**
		 * @return the mostLeftChild
		 */
		public BinomialTree getMostLeftChild() {
			return mostLeftChild;
		}

		/**
		 * @param mostLeftChild the mostLeftChild to set
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
		 * @param key the value to set
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
		 * @param rank the rank to set
		 */
		public void setRank(int rank) {
			this.rank = rank;
		}
		
		public int size() {
			return (int) Math.pow(2, this.rank);
		}
		
	}
}
