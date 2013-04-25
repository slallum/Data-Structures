import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class HangmanTextUI {
	
	private static final String ENTER_GUESS_MSG = "Enter your guess:";

	private static final String SERVER_OPT = "--server";

	private static final String DICTIONARY_FILE = "resources/dictionary.txt";
	
	public static final String LOST_MESSAGE = "You Lost!";
	
	public static final String WIN_MESSAGE = "You Won!";
	
	public static final String[] graphics = {
			"+---+\r\n|   +\r\n|   \r\n|   \r\n|   \r\n|   \r\n|\r\n",
			"+---+\r\n|   +\r\n|   O\r\n|   \r\n|   \r\n|   \r\n|\r\n",
			"+---+\r\n|   +\r\n|   O\r\n|  / \r\n|   \r\n|   \r\n|\r\n",
			"+---+\r\n|   +\r\n|   O\r\n|  / \\\r\n|   \r\n|   \r\n|\r\n",
			"+---+\r\n|   +\r\n|   O\r\n|  /|\\\r\n|   |\r\n|   \r\n|\r\n",
			"+---+\r\n|   +\r\n|   O\r\n|  /|\\\r\n|   |\r\n|  / \r\n|\r\n",
			"+---+\r\n|   +\r\n|   O\r\n|  /|\\\r\n|   |\r\n|  / \\\r\n|\r\n" };

	private static GameServer server = null;

	private static PrintStream printOutput2 = null;

	private static Scanner readGuesses1 = null;

	private static Scanner readGuesses2 = null;

	private static PrintStream printOutput1 = null;

	/**
	 * Starts a game of hangman with a word randomly chosen from a dictionary.
	 * 
	 * @param args
	 * @throws IOException
	 */
	public static void main(String[] args) throws IOException {
		if (args.length > 1 || ((args.length == 1) && !args[0].equals(SERVER_OPT))) {
			System.out.println("Usage: HangmanTextUI [--server]");
			System.exit(0);
		}
		boolean twoPlayers = ((args.length == 1) && args[0].equals(SERVER_OPT));
		readGuesses1 = new Scanner(System.in);
		printOutput1 = System.out;
		if (twoPlayers) {
			server = new GameServer();
			readGuesses2 = new Scanner(server.getInputStream());
			printOutput2 = new PrintStream(server.getOutputStream());
		}
		playGame();
		if (twoPlayers) {
			readGuesses2.close();
			printOutput2.close();
			server.close();
		}
		readGuesses1.close();
	}

	/**
	 * One player gets all messages and is expected to make moves.
	 * Either wins or loses.
	 */
	private static void playGame() {
		Hangman game = new Hangman(chooseWord());
		boolean turn1st = true;
		Scanner currentGuesses = readGuesses1;
		int i = 0;
		// Allowed only 6 mistakes until game is over
		while ((i < 6) && (!game.isOver())) {
			prepareMove(game, i);
			askForGuess(turn1st);
			int currentMistakes = i;
			i = guess(game, currentGuesses, currentMistakes);
			if (i > currentMistakes) {
				if (turn1st && (readGuesses2 != null)) {
					currentGuesses = readGuesses2;
					turn1st = false;
				} else if (!turn1st) {
					currentGuesses = readGuesses1;
					turn1st = true;
				}
			}
		}
		prepareMove(game, i);
		if (i == 6) {
			declareBothLost();
		} else if (game.isOver()) {
			determineWinner(turn1st);
		}
	}

	/**
	 * @return	A randomly picked word from given dictionary
	 */
	private static String chooseWord() {
		try {
			Scanner readWords = new Scanner(new File(DICTIONARY_FILE));
			ArrayList<String> words = new ArrayList<>();
			while (readWords.hasNext()) {
				words.add(readWords.nextLine());
			}
			readWords.close();
			return words.get(new Random().nextInt(words.size()));
		} catch (FileNotFoundException e) {
			System.out.println("Dictionary file not found");
			return "";
		}
	}
	
	/**
	 * Makes all prints needed for user to make next move
	 * 
	 * @param game	Current game happening
	 * @param i		Number of mistaken guesses
	 */
	private static void prepareMove(Hangman game, int i) {
		if (printOutput1 != null) {
			prepareMoveTo(game, i, printOutput1);
		}
		if (printOutput2 != null) {
			prepareMoveTo(game, i, printOutput2);
		}
	}
	
	/**
	 * @param game
	 * @param i
	 * @param out
	 */
	private static void prepareMoveTo(Hangman game, int i, PrintStream out) {
		out.println(graphics[i]);
		out.println();
		String misses = game.getMisses();
		if (!misses.equals("")) {
			out.println("Misses:");
			out.println(game.getMisses());
			out.println();
		}
		out.println(game.getGuess());
		out.println();
	}

	
	/**
	 * @param turn1st
	 */
	private static void askForGuess(boolean turn1st) {
		if (turn1st) {
			printOutput1.println(ENTER_GUESS_MSG);
		} else {
			printOutput2.println(ENTER_GUESS_MSG);
		}
	}

	/**
	 * Get guess from user and update parameters accordingly
	 * 
	 * @param game
	 * @param currentGuesses
	 * @param i
	 * @return
	 */
	private static int guess(Hangman game, Scanner currentGuesses, int i) {
		try {
			if (game.guessLetter(currentGuesses.nextLine().charAt(0)) == Hangman.GUESS_WRONG) {				
				i++;
			}
		} catch (Exception e) {
			i = 6;
		}
		return i;
	}

	
	/**
	 * @param printOutput2	Output stream of second player, if exists.
	 * @param word			Word which was not guessed
	 */
	private static void declareBothLost() {
		System.out.println(LOST_MESSAGE);
		if (printOutput2 != null) {
			printOutput2.println(LOST_MESSAGE);
		}
	}

	/**
	 * @param printOutput2	Output stream of second player, if exists.
	 * @param turn1st		Whoever's turn it is now, is the one that did not
	 * 						make the winning move
	 */
	private static void determineWinner(boolean turn1st) {
		if (!turn1st && (printOutput2 != null)) {
			printOutput2.println(WIN_MESSAGE);
			System.out.println(LOST_MESSAGE);
		} else {
			System.out.println(WIN_MESSAGE);
			if (printOutput2 != null) {
				printOutput2.println(LOST_MESSAGE);
			}
		}
	}


}
