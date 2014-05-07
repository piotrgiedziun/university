<%@page import="java.text.SimpleDateFormat"%>
<%@page contentType="text/html; charset=UTF-8"%>
<%@page import="org.json.simple.JSONObject" %>
<%@page import="java.util.Date"%>
<%
    JSONObject obj=new JSONObject();
	SimpleDateFormat dt = new SimpleDateFormat("hh:mm:ss"); 
    obj.put("date", dt.format(new Date()));
    out.print(obj);
    out.flush();
%>