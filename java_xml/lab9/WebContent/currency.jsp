<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="x" uri="http://java.sun.com/jsp/jstl/xml" %>

<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>MVCBank - Error</title>

    <!-- Bootstrap -->
    <link href="http://getbootstrap.com/dist/css/bootstrap.min.css" rel="stylesheet">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
      <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->
    <style type="text/css">
    body {
	  padding-top: 40px;
	  padding-bottom: 40px;
	  background-color: #eee;
	}
	.container {
		width: 500px;
	}
	</style>
  </head>
  <body>
  
  <%
  	Double min = 99999.0;
  	Double max = 0.0;
  	Integer elms = 0;
  	Double sum = 0.0;
  
  %>
  
  	<div class="container">

		<c:import var="currencyInfo" url="http://www.ny.frb.org/xml/data/fx/${param.id}.xml"/>
		<x:parse xml="${currencyInfo}" var="output"/>
		
		<x:forEach var="currency"
                select="$output/*[local-name()='UtilityData']/*[local-name()='DataSet']/*[local-name()='Series']/*[local-name()='Obs']/*[local-name()='OBS_VALUE']"
                varStatus="currencyStatus">
        <c:set var="current"><x:out select="$currency"/></c:set><%
		Double value = Double.parseDouble((String) pageContext.getAttribute("current"));
		if(value > max) {
			max = value;
		}
		if (value < min) {
			min = value;
		}
		elms++;
		sum += value;
		%>
		</x:forEach>
		
		<%
		pageContext.setAttribute("max", String.valueOf(max));
		pageContext.setAttribute("min", String.valueOf(min));
		// calculate avg
		pageContext.setAttribute("avg", String.valueOf(sum/elms));
		%>
		
		<div class="row" style="margin-top:30px;">
			<div class="col-md-12">
				<h3>Currency</h3>
				<form method="GET">
				<select name="id" onchange="this.form.submit();">
				  <option value="EUR10" <% if(request.getParameter("id").equals("EUR10")) { %>selected<% } %>>Euro</option>
				  <option value="GBP10" <% if(request.getParameter("id").equals("GBP10")) { %>selected<% } %>>British Pound</option>
				  <option value="FRF10" <% if(request.getParameter("id").equals("FRF10")) { %>selected<% } %>>French Franc</option>
				</select>
				</form>
			</div>
		</div>
		
		<div class="row" style="margin-top:30px;">
			<div class="col-md-12">
						min: <c:out value="${min}"/><br/>
						max: <c:out value="${max}"/><br/>
						avg: <c:out value="${avg}"/><br/>
			</div>
		</div>
		
		
    </div>

    <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.0/jquery.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src="http://getbootstrap.com/dist/js/bootstrap.min.js"></script>
  </body>
</html>