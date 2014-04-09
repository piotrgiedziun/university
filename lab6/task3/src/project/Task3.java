package project;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.Comparator;
import java.util.GregorianCalendar;
import java.util.Iterator;
import java.util.List;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;
import javax.xml.datatype.DatatypeConfigurationException;
import javax.xml.datatype.DatatypeFactory;
import javax.xml.datatype.XMLGregorianCalendar;

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
		if (index != -1) {
			Book book = list.get(index);
			book.setTitle("New title");
			book.setAuthor("Eclipse");
		}
		displayBooks("Changed book #bk101");

		// add book
		Book newBook = new Book();
		newBook.setAuthor("Piotr Giedziun");
		newBook.setDescription("All about pizzas");
		newBook.setGenre("Horror");
		newBook.setTitle("Pizza!");
		newBook.setId("bk333");

		// create date object
		XMLGregorianCalendar xgc;
		try {
			xgc = DatatypeFactory.newInstance().newXMLGregorianCalendar();
			GregorianCalendar now = new GregorianCalendar();
			xgc.setYear(now.get(Calendar.YEAR));
			xgc.setMonth(now.get(Calendar.MONTH) + 1);
			xgc.setDay(now.get(Calendar.DAY_OF_MONTH));

			newBook.setPublishDate(xgc);
		} catch (DatatypeConfigurationException e) {
			e.printStackTrace();
		}

		list.add(newBook);

		displayBooks("Added book #bk333");

		// remove book by id
		searchBook = new Book();
		searchBook.setId("bk101");
		index = list.indexOf(searchBook);
		if (index != -1) {
			list.remove(index);
		}

		// remove books by gendre

		Iterator<Book> i = list.iterator();
		while (i.hasNext()) {
			Book book = i.next();
			
			if (book.getGenre().equals("Computer")) {
				i.remove();
			}
		}
		displayBooks("Removed book #bk101 & all with computer genre");

		// sort by price
		Collections.sort(list, new Comparator<Book>() {
			public int compare(Book b1, Book b2) {
				return Float.compare(b2.price, b1.price);
			}
		});

		System.out.println("\nMost expensive book");
		System.out.println(list.get(0).toString());

		// sort by price
		Collections.sort(list, new Comparator<Book>() {
			public int compare(Book b1, Book b2) {
				return b2.publishDate.compare(b1.publishDate);
			}
		});

		System.out.println("\nOldest book");
		System.out.println(list.get(0).toString());

		// estimate average price
		System.out.format("\nAverage price is %f\n", calculateAverage(list));
	}

	private static double calculateAverage(List<Book> books) {
		if (books == null || books.isEmpty()) {
			return 0;
		}

		double sum = 0;
		for (Book book : books) {
			sum += book.price;
		}

		return sum / books.size();
	}

	private static void displayBooks(String title) {
		System.out.println("\n" + title);
		for (Book book : list) {
			System.out.println(book.toString());
		}
	}
}
