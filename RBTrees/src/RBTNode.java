
/**
 * @author slallum
 *
 */
public class RBTNode {
	/** Parent holding this node */
	private RBTNode parent;
	
	/** Left son */
	private RBTNode left;
	
	/** Right son */
	private RBTNode right;
	
	/** Ordered key */
	private int key;
	
	/** Whether this node is black or red otherwise */
	private boolean isBlack;

	public RBTNode(RBTNode parent, RBTNode left, RBTNode right, int key, boolean isBlack) {
		this.parent = parent;
		this.left = left;
		this.right = right;
		this.key = key;
		this.isBlack = isBlack;
	}
	
	/**
	 * @return the parent
	 */
	public RBTNode getParent() {
		return parent;
	}

	/**
	 * @param parent the parent to set
	 */
	public void setParent(RBTNode parent) {
		this.parent = parent;
	}

	/**
	 * @return the left
	 */
	public RBTNode getLeft() {
		return left;
	}

	/**
	 * @param left the left to set
	 */
	public void setLeft(RBTNode left) {
		this.left = left;
		this.left.setParent(this);
	}

	/**
	 * @return the right
	 */
	public RBTNode getRight() {
		return right;
	}

	/**
	 * @param right the right to set
	 */
	public void setRight(RBTNode right) {
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
	 * @param key the key to set
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
	 * @param isBlack the isBlack to set
	 */
	public void setBlack(boolean isBlack) {
		this.isBlack = isBlack;
	}
	
	
	/**
	 * replaces the current node with its father
	 * if this.parent.parent is Null - returns false
	 * 
	 * @throws InvalidOperationException If no parent to replace
	 */
	public boolean moveUp() throws InvalidOperationException {
		if (this.parent == null) {
			throw new InvalidOperationException();
		}
		if (this.parent.getParent() == null) {
			return false;
		}
		
		if (this.parent == this.parent.getParent().getLeft()) {
			this.parent.getParent().setLeft(this);
		} else {
			this.parent.getParent().setRight(this);
		}
		return true;
	}
}
