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
		rotatedLeftIn[0] = root.order("in");
		rotatedLeftPre[0] = root.order("pre");
		rotatedLeftPost[0] = root.order("post");
		
		root.setLeft(null);
		root.setRight(rotatedLeft);
		rotatedLeftIn[1] = root.order("in");
		rotatedLeftPre[1] = root.order("pre");
		rotatedLeftPost[1] = root.order("post");
		
		rotatedRight.setKey(2);
		left = createNode(1);
		right = createNode(4);
		right.setRight(createNode(5));
		right.setLeft(createNode(3));
		rotatedRight.setLeft(left);
		rotatedRight.setRight(right);
		
		root.setRight(rotatedRight);
		rotatedRightIn[1] = root.order("in");
		rotatedRightPre[1] = root.order("pre");
		rotatedRightPost[1] = root.order("post");
		
		root.setRight(null);
		root.setLeft(rotatedRight);
		rotatedRightIn[0] = root.order("in");
		rotatedRightPre[0] = root.order("pre");
		rotatedRightPost[0] = root.order("post");
	}
	
	@Test
	public void testRotateLeft() {
		
		root.setLeft(rotatedRight);
		root.setRight(null);
		rotatedRight.rotateLeft();
		assertEquals("Rotate left - in", rotatedLeftIn[0], root.order("in"));
		assertEquals("Rotate left - pre", rotatedLeftPre[0], root.order("pre"));
		assertEquals("Rotate left - post", rotatedLeftPost[0], root.order("post"));
		
		rotatedRight = rotatedRight.getParent();
		rotatedRight.rotateRight();
		assertEquals("Rotate right - in", rotatedRightIn[0], root.order("in"));
		assertEquals("Rotate right - pre", rotatedRightPre[0], root.order("pre"));
		assertEquals("Rotate right - post", rotatedRightPost[0], root.order("post"));
		
		rotatedRight = rotatedRight.getParent();
		root.setLeft(null);
		root.setRight(rotatedRight);
		rotatedRight.rotateLeft();
		assertEquals("Rotate left - in", rotatedLeftIn[1], root.order("in"));
		assertEquals("Rotate left - pre", rotatedLeftPre[1], root.order("pre"));
		assertEquals("Rotate left - post", rotatedLeftPost[1], root.order("post"));
		
		rotatedRight = rotatedRight.getParent();
		rotatedRight.rotateRight();
		assertEquals("Rotate right - in", rotatedRightIn[1], root.order("in"));
		assertEquals("Rotate right - pre", rotatedRightPre[1], root.order("pre"));
		assertEquals("Rotate right - post", rotatedRightPost[1], root.order("post"));
		
	}

	private RBNode createNode(int key) {
		return tree.new RBNode(null, null, null, key, true);
	}
}
