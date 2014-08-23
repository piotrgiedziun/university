package project;

import java.util.ArrayList;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;

import project.Menu.Food;

public class Task2 {

	public static void main(String[] args) {
		 ArrayList<Food> foodList = new ArrayList<Food>();

		    // create fake food
		 	for(int i=0; i<10; i++) {
		 		int price = (int) (Math.random() * (20 - 1) + 20);
		 		int calories = (int) (Math.random() * (200 - 20) + 200);
		 		
			 	Food food = new Food();
			 	food.setName(String.format("Food %d", i+1));
			 	food.setPrice(price);
			 	if(Math.random() > 0.5)
			 		food.setDescription(String.format("Description %d", i+1));
			 	food.setCalories(calories);;
			    foodList.add(food);
		 	}
		 	
		 	// create real food
		 	Food food = new Food();
		 	food.setName("All the chicken you need");
		 	food.setPrice(20);
		 	food.setDescription("Brand new KFC bucket full of chicken.");
		 	food.setCalories(999);;
		    foodList.add(food);

		    // create bookstore, assigning book
		    Menu menu = new Menu();
		    menu.food = foodList;

		    // create JAXB context and instantiate marshaller
			try {
				JAXBContext context = JAXBContext.newInstance(Menu.class);
				Marshaller m = context.createMarshaller();
		    	m.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, Boolean.TRUE);
		    	m.marshal(menu, System.out);
			} catch (JAXBException e) {
				e.printStackTrace();
			}

	}

}
