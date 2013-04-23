/**
 * 
 * RBTree
 * 
 * An implementation of a Red Black Tree with
 * non-negative, distinct integer values
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
   * returns i if the tree contains i
   *  otherwise, the closest value to i (in terms of absolute difference)
   */
  public int search(int i)
  {
	return 0;  // to be replaced by student code
  }

  /**
   * public void insert(int i)
   * 
   * inserts the integer i into the binary tree; the tree
   * must remain valid (keep its invariants).
   * the function returns the number of rotations, or 0 if i was already in the tree
   * or no reotations were needed
   */
   public int insert(int i) {
	  return 0;	// to be replaced by student code
   }
  
  /**
   * public void delete(int i)
   * 
   * deletes the integer i from the binary tree, if it is there;
   * the tree must remain valid (keep its invariants).
   * the function returns the number of rotations, or 0 if i was not in the tree
   * or no reotations were needed
   */
   public int delete(int i)
   {
	   return 0;	// to be replaced by student code 
   }
   
   /**
    * public int min()
    * 
    * Returns the smallest key in the tree, or -1 if the tree is empty
    * is empty, returns -1;
    * 
    */
   public int min()
   {
	   return -1; // to be replaced by student code
   }
   
   /**
    * public int max()
    * 
    * Returns the largest key in the tree, or -1 if the tree is empty
    */
   public int max()
   {
	   return -1; // to be replaced by student code
   }
   
  /**
   * public void arrayToTree(int[] )
   * 
   * inserts the array of integers to the tree.
   * if the tree contained elements before, they should be discarded
   * the array contains integers in ascending order.
   * 
   */
  public void arrayToTree(int[] array)
  {
	 return; //	 to be replaced by student code
  }

   /**
    * public int size()
    * 
    * Returns the number of nodes in the tree.
    * 
    * precondition: none
    * postcondition: none
    */
   public int size()
   {
	   return 0; // to be replaced by student code
   }

  /**
   * public class RBNode
   * 
   * If you wish to implement classes other than RBTree
   * (for example RBNode), do it in this file, not in 
   * another file 
   *  
   */
  public class RBNode{
	
  }
  
  /**
 * @original author Shai Vardi
 * Modified for semester 2013 b
 */

}
  

