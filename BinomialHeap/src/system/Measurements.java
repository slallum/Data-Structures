package system;

import java.util.Arrays;
import java.util.Random;

public class Measurements {

	
	public static void main(String[] args) {
		for (int i = 1; i <= 10; i++) {
			float[] linksAv = runSingleTest(i * 10000);
			System.out.println(Arrays.toString(linksAv).replace(", ", "\t").replace("[", "").replace("]", ""));
		}
	}
	
	
	public static float[] runSingleTest(int numberOfNums) {
		int[] linksNum = new int[3];
		for (int i = 0; i < 10; i++) {
			int[] nums = getRandomNums(numberOfNums);
			linksNum[0] += BinomialHeap.sortArray(nums);
			linksNum[1] += BinomialHeap.sortArray(nums);
			nums = reverse(nums);
			linksNum[2] += BinomialHeap.sortArray(nums);
		}
		return new float[]{ (float) (linksNum[0]/10.0), (float) (linksNum[1]/10.0), (float) (linksNum[2]/10.0) };
	}
	
	
	private static int[] reverse(int[] nums) {
		for (int i = 0; i < nums.length / 2; i++) {
			int temp = nums[i];
			nums[i] = nums[nums.length - 1 - i];
			nums[nums.length - 1 - i] = temp;
		}
		return nums;
	}


	private static int[] getRandomNums(int numberOfNums) {
		int[] nums = new int[numberOfNums];
		Random rand = new Random();
		int maxNum = (int)100000;
		int num;
		
		for (int i = 0; i < numberOfNums; i++)  {
			num = rand.nextInt(maxNum) + 1;
			nums[i] = num;
		}
		return nums;
	}
}
