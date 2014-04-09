package project;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;

import project.Catalog.Book;

public class Task3 {
	public static final String XML_FILE = "task3.xml";
	private static ArrayList<Book> list;

	public static void main(String[] args) {
		Catalog catalog = null;

		try {
			JAXBContext context = JAXBContext.newInstance(Catalog.class);
			Unmarshaller um = context.createUnmarshaller();
			catalog = (Catalog) um.unmarshal(new FileReader(XML_FILE));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (JAXBException e) {
			e.printStackTrace();
		}

		list = (ArrayList<Book>) catalog.getBook();
		
		displayBooks("Books form xml");
		
		// change book
		Book searchBook = new Book();
		searchBook.setId("bk101");
		int index = list.indexOf(searchBook);
		if ( index != -1 ) {
			Book book = list.get(index);
			book.setTitle("New title");
		}
		displayBooks("Changed book #bk101");
		
		// add book
		Book newBook = new Book();
		newBook.setAuthor("Piotr Giedziun");
		newBook.setDescription("All about pizzas");
		newBook.setGenre("Horror");
		newBook.setTitle("Pizza!");
		newBook.setId("bk333");
		list.add(newBook);
		
		displayBooks("Added book #bk333");
		
		// remove book by id
		searchBook = new Book();
		searchBook.setId("bk101");
		index = list.indexOf(searchBook);
		if ( index != -1 ) {
			list.remove(index);
		}

		displayBooks("Removed book #bk101");
	}

	private static void displayBooks(String title) {
		System.out.println(title);
		for (Book book : list) {
			System.out.format("\t(%s) %s by  %s\n", book.getId(), book.getTitle(), book.getAuthor());
		}
	}
}
