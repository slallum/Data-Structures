package test;

import static org.junit.Assert.assertEquals;

import org.junit.Before;
import org.junit.Test;

import system.RBTree;
import system.RBTree.RBNode;

public class TestNode {

	private RBTree tree = new RBTree();
	private RBNode root = createNode(6);
	private RBNode rotatedLeft = createNode(-1);
	private String[] rotatedLeftIn = new String[2];
	private String[] rotatedLeftPre = new String[2];
	private String[] rotatedLeftPost = new String[2];
	private RBNode rotatedRight = createNode(-1);
	private String[] rotatedRightIn = new String[2];
	private String[] rotatedRightPre = new String[2];
	private String[] rotatedRightPost = new String[2];

	@Before
	public void setUp() {
		rotatedLeft.setKey(4);
		RBNode left = createNode(2);
		RBNode right = createNode(5);
		left.setRight(createNode(3));
		left.setLeft(createNode(1));
		rotatedLeft.setRight(right);
		rotatedLeft.setLeft(left);

		root.setLeft(rotatedLeft);
		rotatedLeftIn[0] = order(root, "in");
		rotatedLeftPre[0] = order(root, "pre");
		rotatedLeftPost[0] = order(root, "post");

		root.setLeft(null);
		root.setRight(rotatedLeft);
		rotatedLeftIn[1] = order(root, "in");
		rotatedLeftPre[1] = order(root, "pre");
		rotatedLeftPost[1] = order(root, "post");

		rotatedRight.setKey(2);
		left = createNode(1);
		right = createNode(4);
		right.setRight(createNode(5));
		right.setLeft(createNode(3));
		rotatedRight.setLeft(left);
		rotatedRight.setRight(right);

		root.setRight(rotatedRight);
		rotatedRightIn[1] = order(root, "in");
		rotatedRightPre[1] = order(root, "pre");
		rotatedRightPost[1] = order(root, "post");

		root.setRight(null);
		root.setLeft(rotatedRight);
		rotatedRightIn[0] = order(root, "in");
		rotatedRightPre[0] = order(root, "pre");
		rotatedRightPost[0] = order(root, "post");
	}

	@Test
	public void testRotate() {

		root.setLeft(rotatedRight);
		root.setRight(null);
		rotatedRight.rotateLeft();
		assertEquals("Rotate left - in", rotatedLeftIn[0], order(root, "in"));
		assertEquals("Rotate left - pre", rotatedLeftPre[0], order(root, "pre"));
		assertEquals("Rotate left - post", rotatedLeftPost[0],
				order(root, "post"));

		rotatedRight = rotatedRight.getParent();
		rotatedRight.rotateRight();
		assertEquals("Rotate right - in", rotatedRightIn[0], order(root, "in"));
		assertEquals("Rotate right - pre", rotatedRightPre[0],
				order(root, "pre"));
		assertEquals("Rotate right - post", rotatedRightPost[0],
				order(root, "post"));

		rotatedRight = rotatedRight.getParent();
		root.setLeft(null);
		root.setRight(rotatedRight);
		rotatedRight.rotateLeft();
		assertEquals("Rotate left - in", rotatedLeftIn[1], order(root, "in"));
		assertEquals("Rotate left - pre", rotatedLeftPre[1], order(root, "pre"));
		assertEquals("Rotate left - post", rotatedLeftPost[1],
				order(root, "post"));

		rotatedRight = rotatedRight.getParent();
		rotatedRight.rotateRight();
		assertEquals("Rotate right - in", rotatedRightIn[1], order(root, "in"));
		assertEquals("Rotate right - pre", rotatedRightPre[1],
				order(root, "pre"));
		assertEquals("Rotate right - post", rotatedRightPost[1],
				order(root, "post"));

	}

	@Test
	public void testGetPosition() {
		// After previous test, rotated right is supposed to be a reference to
		// node number 2
		assertEquals(rotatedRight, root.getPosition(2));

		// After building it, rotated left should be have the key 4
		root.setLeft(rotatedLeft);
		root.setRight(null);
		assertEquals(rotatedLeft, root.getPosition(4));

		// Checking rest of left tree
		assertEquals(rotatedLeft.getLeft(), root.getPosition(2));
		assertEquals(rotatedLeft.getLeft().getLeft(), root.getPosition(1));
		assertEquals(rotatedLeft.getLeft().getRight(), root.getPosition(3));
		assertEquals(rotatedLeft.getRight(), root.getPosition(5));
	}

	/**
	 * 
	 * @param type
	 *            "pre" for pre-order values "post" for post-order values "in"
	 *            or "" for in-order values
	 * @return String of all node's keys in "type" order
	 */
	public String order(RBNode node, String type) {
		String right = (node.getRight() != null) ? order(node.getRight(), type)
				.toString() : "";
		String left = (node.getLeft() != null) ? order(node.getLeft(), type)
				.toString() : "";
		switch (type) {
		case "pre":
			return node.getKey() + left + right;
		case "post":
			return left + right + node.getKey();
		default:
			return left + node.getKey() + right;
		}
	}

	/**
	 * @return All keys of tree, in order
	 */
	public String treeToStr(RBTree tree) {
		return order(tree.getRoot(), "in");
	}

	private RBNode createNode(int key) {
		return tree.new RBNode(null, null, null, key, true);
	}
}
