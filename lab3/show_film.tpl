<p>List of movies:</p>

<table border="1">
<tr>
	<td>#</td>
	<td>title</td>
	<td>length</td>
</tr>
%for row in films:
<tr>
	<td>{{ row['film_id'] }}</td>
	<td>{{ row['title'] }}</td>
	<td>{{ row['length'] }}</td>
</tr>
%end
</table>
%rebase base title='Movies list'