package test;

import java.util.Stack;

import org.junit.Test;

import system.RBTree;
import system.RBTree.RBNode;

public class TestTree {

	@Test
	public void testSearch() throws Exception {
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
		tree.insert(4);
		displayTree(tree.getRoot());
	}

	public void displayTree(RBNode root) {
		Stack<RBNode> globalStack = new Stack<RBNode>();
		globalStack.push(root);
		int emptyLeaf = 32;
		boolean isRowEmpty = false;

		while (isRowEmpty == false) {

			Stack<RBNode> localStack = new Stack<RBNode>();
			isRowEmpty = true;
			for (int j = 0; j < emptyLeaf; j++)
				System.out.print(' ');
			while (globalStack.isEmpty() == false) {
				RBNode temp = globalStack.pop();
				if (temp != null) {
					System.out.print(temp.getKey() + "-");
					if (temp.isBlack()) {
						System.out.print("B");
					} else {
						System.out.print("R");
					}
					localStack.push(temp.getLeft());
					localStack.push(temp.getRight());
					if (temp.getLeft() != null || temp.getRight() != null)
						isRowEmpty = false;
				} else {
					System.out.print("--");
					localStack.push(null);
					localStack.push(null);
				}
				for (int j = 0; j < emptyLeaf * 2 - 2; j++)
					System.out.print(' ');
			}
			System.out.println();
			emptyLeaf /= 2;
			while (localStack.isEmpty() == false)
				globalStack.push(localStack.pop());
		}
	}
}
