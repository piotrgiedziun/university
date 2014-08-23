<p>List of cinemas:</p>

<table border="1">
<tr>
	<td>#</td>
	<td>name</td>
	<td>address</td>
	<td>link</td>
</tr>
%for row in cinemas:
<tr>
	<td>{{ row['cinema_id'] }}</td>
	<td>{{ row['name'] }}</td>
	<td>{{ row['address'] }}</td>
	<td><a href="/shows/{{ row['cinema_id'] }}">View schedule</a></td>
</tr>
%end
</table>
%rebase base title='Cinemas list'