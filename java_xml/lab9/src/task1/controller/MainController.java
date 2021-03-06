package task1.controller;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import task1.model.Host;

@WebServlet("/")
public class MainController extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	Host.hosts.clear();
    	Host.hosts.add(new Host("localhost", "127.0.0.1", "Piotr"));
    	Host.hosts.add(new Host("google.com", "173.194.65.139", "Bob"));
    	
    	Host host = new Host(request.getRemoteHost(), request.getRemoteAddr());
    	
    	if(!Host.hosts.contains(host))
    		Host.hosts.add(host);
    	
        request.setAttribute("hostsList", Host.hosts);

        RequestDispatcher rd = getServletContext().getRequestDispatcher("/home.jsp");
        rd.forward(request, response);
    }
 
}