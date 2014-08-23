package project;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;

import project.Pieces.Piece;

public class Task1 {

	public static final String XML_FILE = "lab5_task1.xml";

	public static void main(String[] args) {
		Pieces pieces = null;

		try {
			JAXBContext context = JAXBContext.newInstance(Pieces.class);
			Unmarshaller um = context.createUnmarshaller();
			pieces = (Pieces) um.unmarshal(new FileReader(XML_FILE));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (JAXBException e) {
			e.printStackTrace();
		}
		ArrayList<Piece> list = (ArrayList<Piece>) pieces.getPiece();
		
		System.out.println("Pieces in XML:");
		for (Piece piece : list) {
			System.out.format("\t%s %s: %s - %s\n", piece.getColor(), piece.getName()
					.toLowerCase(), piece.getPosition(),
					piece.isUsed() ? "used" : "not used");
		}
		
		System.out.println("Missing in XML:");
		
		// create list of all pieces
		String[] pices_names = new String[] { "Pawn", "Knight", "Bishop",
				"Rook", "Queen", "King" };
		String[] colors_names = new String[] { "Black", "White" };
		List<Piece> allPieces = new ArrayList<>();

		for (String name : pices_names) {
			for (String color : colors_names) {
				Piece piece = new Piece();
				piece.setName(name);
				piece.setColor(color);
				allPieces.add(piece);
			}
		}
		
		for (Piece piece : allPieces) {
			if(!list.contains(piece)) {
				System.out.format("\t%s %s\n", piece.getColor(), piece.getName()
					.toLowerCase());
			}
		}
		
	}

}
