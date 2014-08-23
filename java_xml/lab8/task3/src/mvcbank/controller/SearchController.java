package mvcbank.controller;

import java.io.IOException;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import mvcbank.model.User;
import mvcbank.model.UsersList;

public class SearchController extends HttpServlet {
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		// look for existing cookie
		Cookie[] cookies = req.getCookies();
		Cookie cookie = null;
		if (cookies != null) {
			for (int i = 0; i < cookies.length; i++) {
				cookie = cookies[i];
				if (cookie.getName().equals("user_id")) {
					User user = new User(Integer.parseInt(cookie.getValue()),
							null, null, null);
					int index = UsersList.users.indexOf(user);
					String name = req.getParameter("name");
					
					ArrayList<User> users = new ArrayList<User>();
					
					for(User u : UsersList.users) {
						if(u.getUsername().equals(name)) {
							users.add(u);
						}
					}
					
					req.setAttribute("name", name);
					req.setAttribute("users", users);
					
					req.getRequestDispatcher("/search.jsp").forward(req,
							resp);
					return;
				}
			}
		}
		req.getRequestDispatcher("/error.jsp").forward(req, resp);
	}
}
