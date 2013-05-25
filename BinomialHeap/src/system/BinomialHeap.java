package system;

import java.util.LinkedList;
import java.util.List;

/**
 * BinomialHeap
 *
 * An implementation of lazy binomial heap over non-negative integers.
 */
public class BinomialHeap
{

   /**
    * public boolean empty()
    *
    * precondition: none
    *
    * The method returns true if and only if the heap
    * is empty.
    *
    */
    public boolean empty()
    {
    	return false; // should be replaced by student code
    }

   /**
    * public void insert(int value)
    *
    * Insert value into the heap
    *
    */
    public void insert(int value)
    {
    	return; // should be replaced by student code
    }

   /**
    * public void deleteMin()
    *
    * Delete the minimum value.
    * Return the number of linking actions that occured in the process.
    *
    */
    public int deleteMin()
    {
     	return 42; // should be replaced by student code
    }

   /**
    * public int findMin()
    *
    * Return the minimum value
    *
    */
    public int findMin()
    {
    	return 42;// should be replaced by student code
    }

   /**
    * public void meld (BinomialHeap heap2)
    *
    * Meld the heap with heap2
    *
    */
    public void meld (BinomialHeap heap2)
    {
    	  return; // should be replaced by student code
    }

   /**
    * public int size()
    *
    * Return the number of elements in the heap
    *
    */
    public int size()
    {
    	return 42; // should be replaced by student code
    }


   /**
    * public static int sortArray(int[] array)
    *
    * Sort an array by using insert and deleteMin actions on a new heap.
    * Return the number of linking actions that occured in the process.
    *
    */
    public static int sortArray(int[] array)
    {
        return 42; //	 to be replaced by student code
    }

   /**
    * public int[] treesRanks()
    *
    * Return an array containing the ranks of the trees that represent the heap
    * in ascending order.
    *
    */
    public int[] treesRanks()
    {
        int[] arr = new int[42]; //
        return arr; //	 to be replaced by student code
    }

   /**
    * public class BinomialHeapTree
    *
    * If you wish to implement classes other than BinomialHeap
    * (for example BinomialHeapTree), do it in this file, not in
    * another file
    *
    */
    public class BinomialHeapTree {

    }
    
    /**
     * Basic building stone of the tree, represents one link in the tree
     * 
     * @author Shir
     */
    public class BHTNode {
    	
    	/** The nodes parent.  Null if there isn't */
    	private BHTNode parent;
    	
    	/** Node's children - first element is most left child */
    	private LinkedList<BHTNode> children;
    	
    	/** Node's element - non-negative non-unique integers */
    	private int key;

    	/**
    	 * Constructor
    	 */
    	public BHTNode(BHTNode parent) {
			this.parent = parent;
    		this.children = new LinkedList<>();
    	}
    	
		/**
		 * @return the parent
		 */
		public BHTNode getParent() {
			return parent;
		}

		/**
		 * @param parent the parent to set
		 */
		public void setParent(BHTNode parent) {
			this.parent = parent;
		}

		/**
		 * @return the children
		 */
		public LinkedList<BHTNode> getChildren() {
			return children;
		}

		/**
		 * @param children the children to set
		 */
		public void setChildren(LinkedList<BHTNode> children) {
			this.children = children;
		}

		/**
		 * @return the key
		 */
		public int getKey() {
			return key;
		}

		/**
		 * @param key the key to set
		 */
		public void setKey(int key) {
			this.key = key;
		}
		
		/**
		 * @return	Most left child of tree
		 */
		public BHTNode getLeftChild() {
			if (this.children.size() == 0) {
				return null;
			}
			return this.children.getFirst();
		}
		
		/**
		 * Hangs the given node as most left son of current
		 * 
		 * @param leftChild	Node to hang onto current node
		 */
		public void addLeftChild(BHTNode leftChild) {
			this.children.addFirst(leftChild);
		}
    }

}
