package system;

import java.util.ArrayList;
import java.util.LinkedList;

/**
 * BinomialHeap
 * 
 * An implementation of lazy binomial heap over non-negative integers.
 */
public class BinomialHeap {

	/** Lists of heaps roots, tidied in array according to their degree */
	private ArrayList<LinkedList<BinomialTree>> rootsList;

	/** Root with minimum value in the heap */
	private BinomialTree minValRoot;

	/** How many roots saved in the heap */
	private int rootsCount = 0;

	/**
	 * Creates an empty binomial heap
	 */
	public BinomialHeap() {
		this.rootsList = new ArrayList<LinkedList<BinomialTree>>();
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
		if (getRootsList().size() == 0) {
			return true;
		}
		return false;
	}

	/**
	 * public void insert(int value)
	 * 
	 * Insert value into the heap
	 * 
	 */
	public void insert(int value) {
		BinomialTree newNode = new BinomialTree(null, value);
		this.getRootsList().get(0).add(new BinomialTree(null, value));
		if (value < minValRoot.getKey()) {
			minValRoot = newNode;
		}
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
		return minValRoot.getKey();
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
		return 42; // should be replaced by student code
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
		int arrInd = 0;
		int rankInd = 0;
		for (LinkedList<BinomialTree> roots : rootsList) {
			for (int i = 0; i < roots.size(); i++) {
				ranksInOrder[arrInd] = rankInd;
				arrInd++;
			}
			rankInd++;
		}
		return ranksInOrder;
	}

	/**
	 * @return the rootsList
	 */
	public ArrayList<LinkedList<BinomialTree>> getRootsList() {
		return rootsList;
	}


	/* --- Private Methods --- */

	private int successiveLinking() {
		int linksCounter = 0;

		return linksCounter;
	}

	/**
	 * Basic building stone of the tree, represents one link in the tree
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

		/** Value held in the node */
		private int value;

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
		}

		/**
		 * @return the value
		 */
		public int getValue() {
			return value;
		}

		/**
		 * @param value the value to set
		 */
		public void setValue(int value) {
			this.value = value;
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
		
	}
}
