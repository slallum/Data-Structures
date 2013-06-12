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
	public void testSpecific() {
		int[] numbers = new int[] { 21, 89, 37, 61, 19, 84, 13, 2, 78, 67, 28,
				44, 19, 72 };
		BinomialHeap heap = new BinomialHeap();

		int myMin = Integer.MAX_VALUE;
		for (int n : numbers) {
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
	
	@Test
	public void testTreeRanksOrder() {
		
		BinomialHeap heap1 = new BinomialHeap();
		BinomialHeap heap2 = new BinomialHeap();
		List<Integer> randomNumbers = getRandomNumbersList(100);
		for (int n : randomNumbers) {
			heap1.insert(n);
		}
		randomNumbers = getRandomNumbersList(100);
		for (int n : randomNumbers) {
			heap2.insert(n);
		}
		heap1.meld(heap2);
		assertTrue(heap1.size() == 200);
		int[] ranks = heap1.treesRanks();
		int i = 1;
		while (i < ranks.length && ranks[i] >= ranks[i-1]) {
			i++;
		}
		assertTrue(i == ranks.length);
		
		heap1 = new BinomialHeap();
		randomNumbers = getRandomNumbersList(100);
		for (int n : randomNumbers) {
			heap1.insert(n);
		}
		heap2 = new BinomialHeap();
		randomNumbers = getRandomNumbersList(100);
		for (int n : randomNumbers) {
			heap2.insert(n);
		}
		heap1.deleteMin();
		heap1.meld(heap2);
		assertTrue(heap1.size() == 199);
		ranks = heap1.treesRanks();
		i = 1;
		while (i < ranks.length && ranks[i] >= ranks[i-1]) {
			i++;
		}
		assertTrue(i == ranks.length);
		
		heap1 = new BinomialHeap();
		randomNumbers = getRandomNumbersList(100);
		for (int n : randomNumbers) {
			heap1.insert(n);
		}
		heap2 = new BinomialHeap();
		randomNumbers = getRandomNumbersList(100);
		for (int n : randomNumbers) {
			heap2.insert(n);
		}
		heap1.meld(heap2);
		heap1.deleteMin();
		assertTrue(heap1.size() == 199);
		ranks = heap1.treesRanks();
		i = 1;
		while (i < ranks.length && ranks[i] >= ranks[i-1]) {
			i++;
		}
		assertTrue(i == ranks.length);
		
		heap1 = new BinomialHeap();
		randomNumbers = getRandomNumbersList(100);
		for (int n : randomNumbers) {
			heap1.insert(n);
		}
		heap2 = new BinomialHeap();
		randomNumbers = getRandomNumbersList(100);
		for (int n : randomNumbers) {
			heap2.insert(n);
		}
		heap2.deleteMin();
		assertTrue(heap1.size() == 100);
		heap1.meld(heap2);
		ranks = heap1.treesRanks();
		i = 1;
		while (i < ranks.length && ranks[i] >= ranks[i-1]) {
			i++;
		}
		assertTrue(i == ranks.length);
	}

	@Test
	public void testUltimate() {
		List<Integer> randomNumbers = getRandomNumbersList(1000);

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
		Integer[] beforeArray = newSortedList.toArray(new Integer[newSortedList
				.size()]);
		Collections.sort(newSortedList);
		Integer[] afterArray = newSortedList.toArray(new Integer[newSortedList
				.size()]);
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
