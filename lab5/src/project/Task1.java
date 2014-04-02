package project;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;

import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;

import org.xml.sax.Attributes;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.helpers.XMLReaderFactory;

class Piece {
	String name;
	String color;
	String position;

	public Piece(String name, String color, String position) {
		super();
		this.name = name;
		this.color = color;
		this.position = position;
	}

	@Override
	public boolean equals(Object obj) {
		if (!(obj instanceof Piece))
			return false;

		Piece objPiece = (Piece) obj;

		return (objPiece.name.equals(name) && objPiece.color.equals(color));
	}

	@Override
	public String toString() {
		if(position == null)
			return String.format("%s %s", color, name.toLowerCase());
		return String.format("%s %s: %s", color, name.toLowerCase(), position);
	}

}

class Task1Handler extends DefaultHandler {
	List<Piece> pieces = new ArrayList<>();

	public void startElement(String uri, String localName, String qName,
			Attributes atts) {
		if ("piece".equals(localName)) {
			pieces.add(new Piece(atts.getValue("name"), atts.getValue("color"),
					atts.getValue("position")));
		}
	}
}

public class Task1 {

	public static void main(String[] args) {

		// create list of all pieces
		String[] pices_names = new String[] { "Pawn", "Knight", "Bishop",
				"Rook", "Queen", "King" };
		String[] colors_names = new String[] { "Black", "White" };
		List<Piece> pieces = new ArrayList<>();
		
		for(String name : pices_names) {
			for(String color : colors_names) {
				pieces.add(new Piece(name, color, null));
			}
		}

		Task1Handler handler = new Task1Handler();
		try {
			XMLReader reader = XMLReaderFactory.createXMLReader();
			reader.setContentHandler(handler);
			reader.parse("task1.xml");
		} catch (Exception e) {
			System.err.println(e);
		}
		
		System.out.println("Pieces:");
		for (Piece item : handler.pieces) {
			System.out.println(item);
		}
		System.out.println("\nMissing:");
		for (Piece item : pieces) {
			if(!handler.pieces.contains(item)) {
				System.out.println(item);
			}
		}
	}
}
