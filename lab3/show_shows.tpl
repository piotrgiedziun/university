<p>List of shows:</p>

<table border="1">
<tr>
	<td>#</td>
	<td>title</td>
	<td>start date</td>
	<td>ticket</td>
</tr>
%for row in shows:
<tr>
	<td>{{ row['show_id'] }}</td>
	<td>{{ row['title'] }}</td>
	<td>{{ row['start_date'] }}</td>
	<td><a href="#">Buy tickets</a></td>
</tr>
%end
</table>
%rebase base title='Shows list'