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
	public void testDeleteCase1Left() {
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
		assertEquals("Delete Case 1 Left Tree",
				displayTree(testDelete.getRoot()), expectedDeleteCase1LeftTree);
	}

	@Test
	public void testDeleteCase1Right() {
		RBNode root = createNode(5);
		RBNode nodeToDelete = createNode(6);
		RBNode nodeToRemain = createNode(3);
		RBNode nodeToRemainL = createNode(1);
		RBNode nodeToRemainR = createNode(4);
		nodeToRemain.setLeft(nodeToRemainL);
		nodeToRemain.setRight(nodeToRemainR);
		nodeToRemain.setRed();
		root.setRight(nodeToDelete);
		root.setLeft(nodeToRemain);
		RBTree testDelete = new RBTree(root);
		// System.out.println(displayTree(testDelete.getRoot()));
		testDelete.delete(6);
		// System.out.println(displayTree(testDelete.getRoot()));
		assertEquals("Delete Case 1 Right Tree",
				displayTree(testDelete.getRoot()), expectedDeleteCase1RightTree);
	}

	@Test
	public void testDeleteCase2Left() {
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
		// System.out.println(displayTree(testDelete.getRoot()));
		testDelete.delete(3);
		// System.out.println(displayTree(testDelete.getRoot()));
		assertEquals("Delete Case 2 Right (Both) Tree",
				displayTree(testDelete.getRoot()), expectedDeleteCase2LeftTree);
	}

	@Test
	public void testDeleteCase2Right() {
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
		// System.out.println(displayTree(testDelete.getRoot()));
		testDelete.delete(8);
		// System.out.println(displayTree(testDelete.getRoot()));
		assertEquals("Delete Case 2 Left (Both) Tree",
				displayTree(testDelete.getRoot()),
				excpectedDeleteCase2RightTree);
	}

	@Test
	public void testDeleteCase3Left() {
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
		// System.out.println(displayTree(testDelete.getRoot()));
		testDelete.delete(3);
		// System.out.println(displayTree(testDelete.getRoot()));
		assertEquals("Delete Case 3 Left (goes to case 4) Tree",
				displayTree(testDelete.getRoot()), excpectedDeleteCaseLeft3Tree);
	}

	@Test
	public void testDeleteCase3Right() {
		RBNode root = createNode(10);
		RBNode nodeToDelete = createNode(12);
		RBNode nodeToDeleteL = createNode(11);
		RBNode nodeToDeleteR = createNode(13);
		nodeToDelete.setLeft(nodeToDeleteL);
		nodeToDelete.setRight(nodeToDeleteR);
		RBNode nodeToRemain = createNode(4);
		RBNode nodeToRemainL = createNode(2);
		RBNode nodeToRemainR = createNode(7);
		nodeToRemainR.setRed();
		RBNode nodeToRemainSonL = createNode(6);
		RBNode nodeToRemainSonR = createNode(8);
		nodeToRemainR.setLeft(nodeToRemainSonL);
		nodeToRemainR.setRight(nodeToRemainSonR);
		nodeToRemain.setLeft(nodeToRemainL);
		nodeToRemain.setRight(nodeToRemainR);
		root.setRight(nodeToDelete);
		root.setLeft(nodeToRemain);
		RBTree testDelete = new RBTree(root);
		// System.out.println(displayTree(testDelete.getRoot()));
		testDelete.delete(12);
		// System.out.println(displayTree(testDelete.getRoot()));
		assertEquals("Delete Case 3 Right (goes to case 4) Tree",
				displayTree(testDelete.getRoot()),
				excpectedDeleteCase3RightTree);
	}

	@Test
	public void testDeleteCase4Left() {
		RBNode root = createNode(5);
		RBNode nodeToDelete = createNode(3);
		RBNode nodeToDeleteL = createNode(1);
		RBNode nodeToDeleteR = createNode(4);
		nodeToDelete.setLeft(nodeToDeleteL);
		nodeToDelete.setRight(nodeToDeleteR);
		RBNode nodeToRemain = createNode(9);
		RBNode nodeToRemainL = createNode(7);
		nodeToRemainL.setRed();
		RBNode nodeToRemainR = createNode(11);
		nodeToRemainR.setRed();
		RBNode nodeToRemainRSonL = createNode(10);
		RBNode nodeToRemainRSonR = createNode(12);
		nodeToRemainR.setLeft(nodeToRemainRSonL);
		nodeToRemainR.setRight(nodeToRemainRSonR);
		RBNode nodeToRemainLSonL = createNode(6);
		RBNode nodeToRemainLSonR = createNode(8);
		nodeToRemainL.setLeft(nodeToRemainLSonL);
		nodeToRemainL.setRight(nodeToRemainLSonR);
		nodeToRemain.setLeft(nodeToRemainL);
		nodeToRemain.setRight(nodeToRemainR);
		root.setLeft(nodeToDelete);
		root.setRight(nodeToRemain);
		RBTree testDelete = new RBTree(root);
		// System.out.println(displayTree(testDelete.getRoot()));
		testDelete.delete(3);
		// System.out.println(displayTree(testDelete.getRoot()));
		assertEquals("Delete Case 4 Left Tree",
				displayTree(testDelete.getRoot()), excpectedDeleteCase4LeftTree);
	}

	@Test
	public void testDeleteCase4Right() {
		RBNode root = createNode(12);
		RBNode nodeToDelete = createNode(14);
		RBNode nodeToDeleteL = createNode(13);
		RBNode nodeToDeleteR = createNode(15);
		nodeToDelete.setLeft(nodeToDeleteL);
		nodeToDelete.setRight(nodeToDeleteR);
		RBNode nodeToRemain = createNode(6);
		RBNode nodeToRemainL = createNode(3);
		nodeToRemainL.setRed();
		RBNode nodeToRemainR = createNode(8);
		nodeToRemainR.setRed();
		RBNode nodeToRemainRSonL = createNode(7);
		RBNode nodeToRemainRSonR = createNode(9);
		nodeToRemainR.setLeft(nodeToRemainRSonL);
		nodeToRemainR.setRight(nodeToRemainRSonR);
		RBNode nodeToRemainLSonL = createNode(1);
		RBNode nodeToRemainLSonR = createNode(4);
		nodeToRemainL.setLeft(nodeToRemainLSonL);
		nodeToRemainL.setRight(nodeToRemainLSonR);
		nodeToRemain.setLeft(nodeToRemainL);
		nodeToRemain.setRight(nodeToRemainR);
		root.setRight(nodeToDelete);
		root.setLeft(nodeToRemain);
		RBTree testDelete = new RBTree(root);
		// System.out.println(displayTree(testDelete.getRoot()));
		testDelete.delete(14);
		// System.out.println(displayTree(testDelete.getRoot()));
		assertEquals("Delete Case 4 Right Tree",
				displayTree(testDelete.getRoot()),
				excpectedDeleteCase4RightTree);
	}

	@Test
	public void testDeleteRootFromCase4Left() {
		RBNode root = createNode(5);
		RBNode nodeToDelete = createNode(3);
		RBNode nodeToDeleteL = createNode(1);
		RBNode nodeToDeleteR = createNode(4);
		nodeToDelete.setLeft(nodeToDeleteL);
		nodeToDelete.setRight(nodeToDeleteR);
		RBNode nodeToRemain = createNode(9);
		RBNode nodeToRemainL = createNode(7);
		nodeToRemainL.setRed();
		RBNode nodeToRemainR = createNode(11);
		nodeToRemainR.setRed();
		RBNode nodeToRemainRSonL = createNode(10);
		RBNode nodeToRemainRSonR = createNode(12);
		nodeToRemainR.setLeft(nodeToRemainRSonL);
		nodeToRemainR.setRight(nodeToRemainRSonR);
		RBNode nodeToRemainLSonL = createNode(6);
		RBNode nodeToRemainLSonR = createNode(8);
		nodeToRemainL.setLeft(nodeToRemainLSonL);
		nodeToRemainL.setRight(nodeToRemainLSonR);
		nodeToRemain.setLeft(nodeToRemainL);
		nodeToRemain.setRight(nodeToRemainR);
		root.setLeft(nodeToDelete);
		root.setRight(nodeToRemain);
		RBTree testDelete = new RBTree(root);
		// System.out.println(displayTree(testDelete.getRoot()));
		testDelete.delete(5);
		// System.out.println(displayTree(testDelete.getRoot()));
		assertEquals("Delete Case 4 Left Tree",
				displayTree(testDelete.getRoot()),
				excpectedDeleteRootFromCase4Tree);
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
	private String expectedDeleteCase1LeftTree = "                                8-B                                                              \n"
			+ "                5-B                              10-B                              \n"
			+ "        --              6-R              --              --              \n";

	private String expectedDeleteCase1RightTree = "                                3-B                                                              \n"
			+ "                1-B                              5-B                              \n"
			+ "        --              --              4-R              --              \n";

	private String expectedDeleteCase2LeftTree = "                                5-B                                                              \n"
			+ "                4-B                              8-R                              \n"
			+ "        1-R              --              6-B              10-B              \n";
	private String excpectedDeleteCase2RightTree = "                                5-B                                                              \n"
			+ "                3-R                              10-B                              \n"
			+ "        1-B              4-B              6-R              --              \n";
	private String excpectedDeleteCaseLeft3Tree = "                                7-B                                                              \n"
			+ "                5-B                              9-B                              \n"
			+ "        4-B              6-B              8-B              10-B              \n"
			+ "    1-R      --      --      --      --      --      --      --      \n";
	private String excpectedDeleteCase3RightTree = "                                7-B                                                              \n"
			+ "                4-B                              10-B                              \n"
			+ "        2-B              6-B              8-B              13-B              \n"
			+ "    --      --      --      --      --      --      11-R      --      \n";
	private String excpectedDeleteCase4LeftTree = "                                9-B                                                              \n"
			+ "                5-B                              11-B                              \n"
			+ "        4-B              7-R              10-B              12-B              \n"
			+ "    1-R      --      6-B      8-B      --      --      --      --      \n";
	private String excpectedDeleteCase4RightTree = "                                6-B                                                              \n"
			+ "                3-B                              12-B                              \n"
			+ "        1-B              4-B              8-R              15-B              \n"
			+ "    --      --      --      --      7-B      9-B      13-R      --      \n";
	private String excpectedDeleteRootFromCase4Tree = "                                6-B                                                              \n"
			+ "                3-B                              9-B                              \n"
			+ "        1-B              4-B              7-B              11-R              \n"
			+ "    --      --      --      --      --      8-R      10-B      12-B      \n";
}
