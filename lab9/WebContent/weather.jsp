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
  
  	<div class="container">

		<c:import var="weatherInfo" url="http://weather.yahooapis.com/forecastrss?w=2502265"/>
		<x:parse xml="${weatherInfo}" var="output"/>
		
		<div class="row" style="margin-top:30px;">
			<div class="col-md-12">
				<h3>Weather</h3>
			</div>
		</div>
		
		<div class="row">
		  <div class="col-md-4">City</div>
		  <div class="col-md-4">Country</div>
		  <div class="col-md-4">Region</div>
		</div>
		
		<div class="row">
		  <div class="col-md-4"><x:out select="$output/rss/channel/*[local-name()='location']/@city" /></div>
		  <div class="col-md-4"><x:out select="$output/rss/channel/*[local-name()='location']/@country" /></div>
		  <div class="col-md-4"><x:out select="$output/rss/channel/*[local-name()='location']/@region" /></div>
		</div>
		
		<div class="row" style="margin-top:30px;">
			<div class="col-md-12">
				<small>temperature:</small> <x:out select="$output/rss/channel/item/*[local-name()='condition']/@temp" /> <x:out select="$output/rss/channel/*[local-name()='units']/@temperature" /><br/>
				<small>pressure:</small> <x:out select="$output/rss/channel/*[local-name()='atmosphere']/@pressure" /> <x:out select="$output/rss/channel/*[local-name()='units']/@pressure" /><br/>
				<small>sunrise:</small> <x:out select="$output/rss/channel/*[local-name()='astronomy']/@sunrise" /><br/>
				<small>sunset:</small> <x:out select="$output/rss/channel/*[local-name()='astronomy']/@sunset" />
			</div>
		</div>
		
		<div class="row" style="margin-top:30px;">
			<div class="col-md-12">
				<h3>Forecast (5 days)</h3>
				<c:forEach begin="1" end="6" var="val">
				    <x:out select="$output/rss/channel/item/*[local-name()='forecast'][$val]/@date" /> h:<x:out select="$output/rss/channel/item/*[local-name()='forecast'][$val]/@high" /> <x:out select="$output/rss/channel/*[local-name()='units']/@temperature" />   l:<x:out select="$output/rss/channel/item/*[local-name()='forecast'][$val]/@low" /> <x:out select="$output/rss/channel/*[local-name()='units']/@temperature" /> <br/>
				</c:forEach>
			
			</div>
		</div>
    
    </div>

    <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.0/jquery.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src="http://getbootstrap.com/dist/js/bootstrap.min.js"></script>
  </body>
</html>