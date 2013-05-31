package test;

import org.junit.Test;
import static junit.framework.Assert.assertEquals;

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

}
