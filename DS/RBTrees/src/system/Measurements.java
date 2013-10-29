package system;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Random;

public class Measurements {
	public static void main(String[] args) {
		float[][] res = new float[10][3];
		for (int i = 1; i <= 10; i++) {
			res[i-1] = oneRound(i);
			System.out.println(Arrays.toString(res[i-1]).replace(", ", "\t").replace("[", "").replace("]", ""));
		}
	}
	
	public static float[] oneRound(int multiplier) {
		int circulations = 10000 * multiplier;
		float floatMultiplier = (float)multiplier;
		List<Integer> randomNums = getRandomNums(circulations);
		
		int maxRotations = 0;
		float maxAverageRotations = 0;
		int count = 0;
		int sumRotations = 0;
		
		RBTree tree = new RBTree();
		int currentRotations;		
		float currentAverage;
		
		for (int number : randomNums) {
			count++;
			currentRotations = tree.insert(number);
			sumRotations += currentRotations;
			if (currentRotations > maxRotations) {
				maxRotations = currentRotations;
			}
			currentAverage = (float)sumRotations / count;
			if (currentAverage > maxAverageRotations) {
				maxAverageRotations = currentAverage;
			}
		}
		return new float[] {floatMultiplier, maxAverageRotations, maxRotations};
	}
	
	private static List<Integer> getRandomNums(int numberOfNums) {
		Random rand = new Random();
		HashSet<Integer> givenNums = new HashSet<Integer>();
		int maxNum = (int)Math.pow(2, 30);
		int num;
		
		for (int i = 0; i < numberOfNums; i++)  {
			num = rand.nextInt(maxNum) + 1;
			while (givenNums.contains(num)) {
				num = rand.nextInt(maxNum) + 1;
			}
			givenNums.add(num);
		}
		return new ArrayList<Integer>(givenNums);
	}

}
