package test;

import java.util.Stack;

import org.junit.Test;
import static junit.framework.Assert.*;
import system.RBTree;
import system.RBTree.RBNode;

public class TestTree {

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
		//case 2 -> case 3
		tree.insert(4);
		//case 3
		tree.insert(7);
		// rotate the ROOT (case 3)
		tree.insert(10);
		tree.insert(13);
		String output = displayTree(tree.getRoot());
		System.out.println(output);
		assertEquals(expectedInsertedTree, output);
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

	private String expectedInsertedTree = "                                6-B                                                              \n"
			+ "                2-R                              8-R                              \n"
			+ "        1-B              4-B              7-B              10-B              \n"
			+ "    --      --      3-R      5-R      --      --      9-R      13-R      \n";

}
