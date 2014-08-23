package mvcbank.model;

import java.util.ArrayList;
import static java.util.Arrays.asList;

public class UsersList {
	public static ArrayList<User> users = 
			new ArrayList<User>(asList(
					new User(1, "test", "test", new Money(100.50, "PLN")),
					new User(2, "test1", "test1", new Money(200.50, "USD"))
			));
}
