package test;

import static junit.framework.Assert.assertEquals;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Random;
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
		assertEquals(
				"Comparing tree created from sorted array with tree inserted one by one:",
				displayTree(treeFromArray.getRoot()),
				displayTree(treeFromInsert.getRoot()));
		assertEquals(isValidTree(treeFromInsert), true);
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
		assertEquals(isValidTree(testDelete), true);
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
		testDelete.delete(6);
		assertEquals("Delete Case 1 Right Tree",
				displayTree(testDelete.getRoot()), expectedDeleteCase1RightTree);
		assertEquals(isValidTree(testDelete), true);
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
		testDelete.delete(3);
		assertEquals("Delete Case 2 Right (Both) Tree",
				displayTree(testDelete.getRoot()), expectedDeleteCase2LeftTree);
		assertEquals(isValidTree(testDelete), true);
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
		testDelete.delete(8);
		assertEquals("Delete Case 2 Left (Both) Tree",
				displayTree(testDelete.getRoot()),
				excpectedDeleteCase2RightTree);
		assertEquals(isValidTree(testDelete), true);
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
		testDelete.delete(3);
		assertEquals("Delete Case 3 Left (goes to case 4) Tree",
				displayTree(testDelete.getRoot()), excpectedDeleteCaseLeft3Tree);
		assertEquals(isValidTree(testDelete), true);
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
		testDelete.delete(12);
		assertEquals("Delete Case 3 Right (goes to case 4) Tree",
				displayTree(testDelete.getRoot()),
				excpectedDeleteCase3RightTree);
		assertEquals(isValidTree(testDelete), true);
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
		testDelete.delete(3);
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
		testDelete.delete(14);
		assertEquals("Delete Case 4 Right Tree",
				displayTree(testDelete.getRoot()),
				excpectedDeleteCase4RightTree);
		assertEquals(isValidTree(testDelete), true);
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
		testDelete.delete(5);
		assertEquals("Delete Case 4 Left Tree",
				displayTree(testDelete.getRoot()),
				excpectedDeleteRootFromCase4Tree);

		assertEquals(isValidTree(testDelete), true);
	}

	@Test
	public void TestCase3RightSpecific() {
		RBTree tree = new RBTree();
		tree.insert(4);
		tree.insert(1);
		tree.insert(5);
		tree.insert(3);
		tree.delete(5);
		assertEquals(isValidTree(tree), true);
	}

	@Test
	public void TestCase3RightSpecific2() {
		RBTree tree = new RBTree();
		tree.insert(4);
		tree.insert(1);
		tree.insert(5);
		tree.insert(6);
		tree.delete(5);
		assertEquals(isValidTree(tree), true);
	}
	
	@Test
	public void TestCase3RightSpecific3() {
		RBTree tree = new RBTree();
		tree.insert(4);
		tree.insert(5);
		tree.delete(5);
		assertEquals(isValidTree(tree), true);
	}
	
	@Test
	public void TestCase3RightSpecific4() {
		RBTree tree = new RBTree();
		tree.insert(4);
		tree.insert(1);
		tree.insert(7);
		tree.insert(5);
		tree.insert(8);
		tree.delete(4);
		assertEquals(isValidTree(tree), true);
	}

	
	@Test
	public void TestInsertAndDeleteRandomNumbers() {
		List<Integer> randomNumbers = getRandomNumbersList(1000);
		RBTree tree = new RBTree();
		for (int n : randomNumbers) {
			tree.insert(n);
			assertEquals(isValidTree(tree), true);
		}
		// System.out.println(displayTree(tree.getRoot()));
		Collections.shuffle(randomNumbers);
		String beforeTree;
		String afterTree;
		for (int n : randomNumbers) {
			beforeTree = displayTree(tree.getRoot());
			tree.delete(n);
			afterTree = displayTree(tree.getRoot());
			if (!isValidTree(tree)) {
				System.out.println(beforeTree);
				System.out.println(afterTree);
				isValidTree(tree);
				System.out.println("oh noes!");
			}
		}
		System.out.println(displayTree(tree.getRoot()));
	}
	
	@Test
	public void TestArrayToTree() {
		int[] arr = new int[] {1, 4, 6, 8, 12, 14, 17, 23, 31, 32, 34, 36, 41, 42, 51, 52, 53, 62, 63, 65, 76, 78, 79, 84, 95, 111, 112, 113, 141, 151};
		RBTree tree = new RBTree();
		tree.insert(4);
		tree.arrayToTree(arr);
		assertEquals(true, isValidTree(tree));
	}

	private List<Integer> getRandomNumbersList(int numbersCount) {
		HashSet<Integer> numbers = new HashSet<Integer>();
		Random rand = new Random();
		for (int i = 0; i < numbersCount; i++) {
			numbers.add(rand.nextInt(1073741824)); // 2**30
		}
		List<Integer> numbersList = new ArrayList<Integer>(numbers);
		return numbersList;
	}

	private boolean isValidTree(RBTree tree) {
		if (tree.getRoot() == null) {
			return true;
		}
		List<Integer> depths = new ArrayList<>();
		depths.add(0);
		buildDepths(tree.getRoot(), depths, 0);
		// System.out.println(Arrays.toString(depths.toArray()));
		int i = 1;
		while (i < depths.size()) {
			if (depths.get(i) != depths.get(i - 1)) {
				return false;
			}
			i++;
		}
		int[] values = makeArray(TestNode.order(tree.getRoot(), "in"));
		int ind = 1;
		while ((ind < values.length) && (values[ind] >= values[ind-1])) {
			ind++;
		}
		if (i < values.length) {
			return false;
		}
		return checkRed(tree.getRoot(), false);

	}

	/**
	 * Build an array of black sizes of all possible roots to leafs in tree
	 * 
	 * @param currentNode
	 * @param depths
	 * @param currentInd
	 */
	private void buildDepths(RBNode currentNode, List<Integer> depths,
			int currentInd) {

		if (currentNode == null) {
			return;
		}
		if (currentNode.isBlack()) {
			depths.set(currentInd, depths.get(currentInd) + 1);
		}
		depths.add(depths.get(currentInd));
		int newInd = depths.size() - 1;
		buildDepths(currentNode.getRight(), depths, currentInd);
		buildDepths(currentNode.getLeft(), depths, newInd);
	}
	
	private int[] makeArray(String values) {
		String[] strValues = values.split(",");
		int[] intValues = new int[strValues.length];
		for(int i=0; i < strValues.length; i++) {
			intValues[i] = Integer.parseInt(strValues[i]);
		}
		return intValues;
	}

	private boolean checkRed(RBNode currentNode, boolean lastRed) {
		if (currentNode == null) {
			return true;
		}
		if (lastRed && !currentNode.isBlack()) {
			return false;
		}
		lastRed = !currentNode.isBlack();
		return checkRed(currentNode.getLeft(), lastRed)
				&& checkRed(currentNode.getRight(), lastRed);
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
