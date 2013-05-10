package test;

import static junit.framework.Assert.assertEquals;

import java.util.Stack;

import org.junit.Test;

import system.RBTree;
import system.RBTree.RBNode;

public class TestTree {

	private RBTree tree = new RBTree();

	@Test
	public void testInsert() throws Exception {
		RBTree tree = new RBTree();
		tree.insert(2);
		tree.insert(6);
		tree.insert(1);
		tree.insert(3);
		tree.insert(3);
		tree.insert(1);
		tree.insert(9);
		tree.insert(8);
		tree.insert(5);
		// case 2 -> case 3
		tree.insert(4);
		// case 3
		tree.insert(7);
		// rotate the ROOT (case 3)
		tree.insert(10);
		tree.insert(13);
		String output = displayTree(tree.getRoot());
		assertEquals("Comparing inserted tree with pre-created string",
				expectedInsertedTree, output);
	}

	@Test
	public void testArrayToTree() {
		int[] sortedArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 13 };
		RBTree treeFromArray = new RBTree();
		treeFromArray.arrayToTree(sortedArray);

		RBTree treeFromInsert = new RBTree();
		treeFromInsert.insert(1);
		treeFromInsert.insert(2);
		treeFromInsert.insert(3);
		treeFromInsert.insert(4);
		treeFromInsert.insert(5);
		treeFromInsert.insert(6);
		treeFromInsert.insert(7);
		treeFromInsert.insert(8);
		treeFromInsert.insert(9);
		treeFromInsert.insert(10);
		treeFromInsert.insert(13);
		// System.out.println(displayTree(treeFromArray.getRoot()));
		// System.out.println(displayTree(treeFromInsert.getRoot()));
		assertEquals(
				"Comparing tree created from sorted array with tree inserted one by one:",
				displayTree(treeFromArray.getRoot()),
				displayTree(treeFromInsert.getRoot()));
	}

	@Test
	public void testDeleteCase1() {
		RBNode root = createNode(5);
		RBNode nodeToDelete = createNode(3);
		RBNode nodeToRemain = createNode(8);
		RBNode nodeToRemainL = createNode(6);
		RBNode nodeToRemainR = createNode(10);
		nodeToRemain.setLeft(nodeToRemainL);
		nodeToRemain.setRight(nodeToRemainR);
		nodeToRemain.setRed();
		root.setLeft(nodeToDelete);
		root.setRight(nodeToRemain);
		RBTree testDelete = new RBTree(root);
		testDelete.delete(3);
		assertEquals("Delete Case 1 Tree", displayTree(testDelete.getRoot()),
				expectedDeleteCase1Tree);
	}

	@Test
	public void testDeleteCase2() {
		RBNode root = createNode(5);
		RBNode nodeToDelete = createNode(3);
		RBNode nodeToDeleteL = createNode(1);
		RBNode nodeToDeleteR = createNode(4);
		nodeToDelete.setLeft(nodeToDeleteL);
		nodeToDelete.setRight(nodeToDeleteR);
		RBNode nodeToRemain = createNode(8);
		RBNode nodeToRemainL = createNode(6);
		RBNode nodeToRemainR = createNode(10);
		nodeToRemain.setLeft(nodeToRemainL);
		nodeToRemain.setRight(nodeToRemainR);
		root.setLeft(nodeToDelete);
		root.setRight(nodeToRemain);
		RBTree testDelete = new RBTree(root);
		testDelete.delete(3);
		assertEquals("Delete Case 2 (Both) Tree",
				displayTree(testDelete.getRoot()), expectedDeleteCase2Tree);
	}

	@Test
	public void testDeleteCase3() {
		RBNode root = createNode(5);
		RBNode nodeToDelete = createNode(3);
		RBNode nodeToDeleteL = createNode(1);
		RBNode nodeToDeleteR = createNode(4);
		nodeToDelete.setLeft(nodeToDeleteL);
		nodeToDelete.setRight(nodeToDeleteR);
		RBNode nodeToRemain = createNode(9);
		RBNode nodeToRemainL = createNode(7);
		nodeToRemainL.setRed();
		RBNode nodeToRemainR = createNode(10);
		RBNode nodeToRemainSonL = createNode(6);
		RBNode nodeToRemainSonR = createNode(8);
		nodeToRemainL.setLeft(nodeToRemainSonL);
		nodeToRemainL.setRight(nodeToRemainSonR);
		nodeToRemain.setLeft(nodeToRemainL);
		nodeToRemain.setRight(nodeToRemainR);
		root.setLeft(nodeToDelete);
		root.setRight(nodeToRemain);
		RBTree testDelete = new RBTree(root);
//		System.out.println(displayTree(testDelete.getRoot()));
		testDelete.delete(3);
//		System.out.println(displayTree(testDelete.getRoot()));
		assertEquals("Delete Case 2 (Both) Tree",
				displayTree(testDelete.getRoot()), excpectedDeleteCase3Tree);
	}

	public String displayTree(RBNode root) {
		StringBuilder buildOutput = new StringBuilder();
		Stack<RBNode> globalStack = new Stack<RBNode>();
		globalStack.push(root);
		int emptyLeaf = 32;
		boolean isRowEmpty = false;

		while (isRowEmpty == false) {

			Stack<RBNode> localStack = new Stack<RBNode>();
			isRowEmpty = true;
			for (int j = 0; j < emptyLeaf; j++)
				buildOutput.append(' ');
			while (globalStack.isEmpty() == false) {
				RBNode temp = globalStack.pop();
				if (temp != null) {
					buildOutput.append(temp.getKey() + "-");
					if (temp.isBlack()) {
						buildOutput.append("B");
					} else {
						buildOutput.append("R");
					}
					localStack.push(temp.getLeft());
					localStack.push(temp.getRight());
					if (temp.getLeft() != null || temp.getRight() != null)
						isRowEmpty = false;
				} else {
					buildOutput.append("--");
					localStack.push(null);
					localStack.push(null);
				}
				for (int j = 0; j < emptyLeaf * 2 - 2; j++)
					buildOutput.append(' ');
			}
			buildOutput.append("\n");
			emptyLeaf /= 2;
			while (localStack.isEmpty() == false)
				globalStack.push(localStack.pop());
		}
		return buildOutput.toString();
	}

	private RBNode createNode(int key) {
		return tree.new RBNode(null, null, null, key, true);
	}

	private String expectedInsertedTree = "                                6-B                                                              \n"
			+ "                2-R                              8-R                              \n"
			+ "        1-B              4-B              7-B              10-B              \n"
			+ "    --      --      3-R      5-R      --      --      9-R      13-R      \n";
	private String expectedDeleteCase1Tree = "                                8-B                                                              \n"
			+ "                5-B                              10-B                              \n"
			+ "        --              6-R              --              --              \n";

	private String expectedDeleteCase2Tree = "                                5-B                                                              \n"
			+ "                4-B                              8-R                              \n"
			+ "        1-R              --              6-B              10-B              \n";
	private String excpectedDeleteCase3Tree = "                                7-B                                                              \n"
			+ "                5-B                              9-B                              \n"
			+ "        4-B              6-B              8-B              10-B              \n"
			+ "    1-R      --      --      --      --      --      --      --      \n";
}
