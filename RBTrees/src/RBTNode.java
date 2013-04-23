
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
	 * Takes current Node's left son, moves it up,
	 * it's right son to be it's parent's left son
	 * and the parent to be it's right son
	 */
	public void rotateRight() {
		RBTNode y = this.left;
		if (y == null) {
			return;
		}
		y.moveUp();
		this.setLeft(y.getRight());
		y.setRight(this);
	}
	
	/**
	 * Takes current Node's right son, moves it up,
	 * it's left son to be it's parent's right son
	 * and the parent to be it's left son
	 */
	public void rotateLeft() {
		
		RBTNode right = this.right;
		if (right == null) {
			return;
		}
		right.moveUp();
		this.setRight(right.getLeft());
		right.setLeft(this);
	}
	
}
