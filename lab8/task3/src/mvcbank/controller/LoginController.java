package mvcbank.controller;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import mvcbank.model.User;
import mvcbank.model.UsersList;

public class LoginController extends HttpServlet {
	private static final long serialVersionUID = 1L;

	public LoginController() {
		super();
	}

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		
		// look for existing cookie
		Cookie[] cookies = req.getCookies();
		Cookie cookie = null;
		if( cookies != null ){
		      for (int i = 0; i < cookies.length; i++){
		         cookie = cookies[i];
		         if(cookie.getName().equals("user_id")){
		        	 User user = new User(Integer.parseInt(cookie.getValue()), null, null, null);
		        	 int index = UsersList.users.indexOf(user);
		        	 req.setAttribute("user", UsersList.users.get(index));
		        	 req.getRequestDispatcher("/dashboard.jsp").forward(req, resp);
		        	 return;
		         }
		      }
		  }
		req.getRequestDispatcher("login.jsp").forward(req, resp);
	}

	protected void doPost(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {

		String username = request.getParameter("username");
		String password = request.getParameter("password");
		RequestDispatcher rd = null;

		User tmp_user = new User(null, username, password, null);

		if (UsersList.users.contains(tmp_user)) {
			int index = UsersList.users.indexOf(tmp_user);
			User user = UsersList.users.get(index);
			rd = request.getRequestDispatcher("/dashboard.jsp");
			Cookie user_id = new Cookie("user_id", user.getId().toString());
			user_id.setMaxAge(60 * 60 * 24);
			response.addCookie(user_id);
			request.setAttribute("user", UsersList.users.get(index));
		} else {
			rd = request.getRequestDispatcher("/error.jsp");
		}
		rd.forward(request, response);
	}

}