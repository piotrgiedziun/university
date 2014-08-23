<%@ page import="java.io.*,java.util.*, javax.servlet.*" 
	language="java" contentType="text/html; charset=US-ASCII"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	<script type="text/javascript" src="http://code.jquery.com/jquery.min.js"></script>
	<script type="text/javascript" src="http://momentjs.com/downloads/moment-with-langs.min.js"></script>
	<script type="text/javascript">
	$(function() {
		function get_time_request() {
			$.getJSON("json.jsp", function(data) {
				$("#browser_date").text(moment().format('hh:mm:ss'));
				$("#server_date").text(data.date);
			});
		}
		get_time_request();
		setInterval(get_time_request, 1000);
	});
	</script>
</head>
<body>
<table border="0">
	<tr>
		<td>Browser date</td>
		<td><span id="browser_date">-</span></td>
	</tr>
	<tr>
		<td>Server date</td>
		<td><span id="server_date">-</span></td>
	</tr>
</table>
</body>
</html>