<%@ page language="java" contentType="text/xml; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<hosts>
<c:forEach items="${requestScope['hostsList']}" var="host">
	<c:choose>
	   <c:when test="${host.user != null}">
	      <host user="<c:out value="${host.user}"/>" name="<c:out value="${host.name}"/>">
				<ip><c:out value="${host.ip}"/></ip>
			</host>
	   </c:when>
	   <c:otherwise>
	      <host name="<c:out value="${host.name}"/>">
				<ip><c:out value="${host.ip}"/></ip>
			</host>
	   </c:otherwise>
	</c:choose>
</c:forEach>
</hosts>