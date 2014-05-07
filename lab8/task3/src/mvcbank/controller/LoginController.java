package mvcbank.controller;

import java.io.IOException;
import java.util.ArrayList;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import mvcbank.model.Money;
import mvcbank.model.User;

public class LoginController extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private ArrayList<User> users;

	public LoginController() {
		super();
		users = new ArrayList<User>();
		users.add(new User("test", "test", new Money(100.50, "PLN")));
		users.add(new User("test1", "test1", new Money(200.00, "PLN")));
		users.add(new User("test2", "test2", new Money(10.50, "USD")));
	}

	protected void doPost(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {

		String username = request.getParameter("username");
		String password = request.getParameter("password");
		RequestDispatcher rd = null;
		
		User tmp_user = new User(username, password, null);

		if (users.contains(tmp_user)) {
			int index = users.indexOf(tmp_user);
			rd = request.getRequestDispatcher("/dashboard.jsp");
			request.setAttribute("user", users.get(index));
		} else {
			rd = request.getRequestDispatcher("/error.jsp");
		}
		rd.forward(request, response);
	}

}