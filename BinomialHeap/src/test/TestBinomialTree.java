package test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;

import org.junit.Test;
import static junit.framework.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import system.BinomialHeap;

public class TestBinomialTree {

	@Test
	public void testInsertSimple() {
		BinomialHeap heap = new BinomialHeap();
		assertEquals(0, heap.size());
		heap.insert(10);
		assertEquals(1, heap.size());
		heap.insert(4);
		heap.insert(16);
		assertEquals(3, heap.size());
		heap.insert(4);
		assertEquals(4, heap.size());
	}

	@Test
	public void testFindMinSimple() {
		BinomialHeap heap = new BinomialHeap();
		heap.insert(10);
		heap.insert(4);
		heap.insert(16);
		heap.insert(4);
		assertEquals(4, heap.findMin());
	}

	@Test
	public void testDelMin() {
		BinomialHeap heap = new BinomialHeap();
		heap.insert(10);
		heap.insert(4);
		heap.insert(16);
		heap.insert(4);
		heap.deleteMin();
		assertEquals(4, heap.findMin());
		heap.deleteMin();
		assertEquals(10, heap.findMin());
	}

	@Test
	public void testUltimate() {
		List<Integer> randomNumbers = getRandomNumbersList(100);

		BinomialHeap heap = new BinomialHeap();

		int myMin = Integer.MAX_VALUE;
		for (int n : randomNumbers) {
			heap.insert(n);
			myMin = Math.min(myMin, n);
			assertEquals(myMin, heap.findMin());
		}

		List<Integer> newSortedList = new ArrayList<Integer>();

		while (heap.size() > 0) {
			newSortedList.add(heap.findMin());
			heap.deleteMin();
		}
		
		assertTrue(isSorted(newSortedList));
	}

	private boolean isSorted(List<Integer> newSortedList) {
		Integer[] beforeArray = newSortedList.toArray(new Integer[newSortedList.size()]);
		Collections.sort(newSortedList);
		Integer[] afterArray = newSortedList.toArray(new Integer[newSortedList.size()]);
		return Arrays.equals(beforeArray, afterArray);
	}

	private List<Integer> getRandomNumbersList(int numbersCount) {
		List<Integer> numbers = new ArrayList<Integer>();
		Random rand = new Random();
		for (int i = 0; i < numbersCount; i++) {
			numbers.add(rand.nextInt(1073741824)); // 2**30
		}
		return numbers;
	}

}
