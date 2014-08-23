<%@ page language="java" contentType="text/html; charset=US-ASCII"
    pageEncoding="UTF-8"%>

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
	</style>
  </head>
  <body>
  
  <div class="container">

    <h1>Hello ${requestScope['user'].getUsername()}!</h1>
    
    <strong>Current account balance is ${requestScope['user'].getAccount_balance()}</strong>
	<br/><br/>
	<form action="SearchController" method="get">
		<input type="text" name="name" placeholder="Search" autofocus>
        <button class="btn btn-primary" type="submit">Search</button>
	</form>

    </div>

    <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.0/jquery.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src="http://getbootstrap.com/dist/js/bootstrap.min.js"></script>
  </body>
</html>