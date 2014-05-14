<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="x" uri="http://java.sun.com/jsp/jstl/xml" %>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
</head>
<body>
<c:import var="weatherInfo" url="http://weather.yahooapis.com/forecastrss?w=2502265"/>
<x:parse xml="${weatherInfo}" var="output"/>
<x:out select="$output/rss/channel/yweather:location/@city" />
</body>
</html>