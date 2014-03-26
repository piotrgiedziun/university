package project;

import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		/**
		 * LAB 4
		 * URL: http://szymon.jagiello.staff.iiar.pwr.wroc.pl/lab4.html
		 */
		Scanner reader = new Scanner(System.in);
		System.out.println("Pick an option (1-5): ");
		
		while(true) {
			switch(reader.nextInt()) {
				case 0:
					return;
				case 1:
					Task1.build();
					break;
				case 2:
					Task2.build();
					break;
				case 3:
					Task3.build();
					break;
				case 4:
					Task4.build();
					break;
				case 5:
					break;
				default:
					System.err.println("Invalid option.");
			}
			System.out.println("Select 0 in order to close");
		}
	}
}
