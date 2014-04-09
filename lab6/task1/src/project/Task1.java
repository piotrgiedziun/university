package project;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;

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
	    for (Piece piece : list) {
	      System.out.format("%s %s: %s\n", piece.getColor(), piece.getName().toLowerCase(), piece.getPosition());
	    }
	}

}
