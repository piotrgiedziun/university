<p>List of cinemas:</p>

<table border="1">
<tr>
	<td>#</td>
</tr>
%for line in tickets:
<tr>
	{{ line }}
	%for elm in line:
		<td>{{ elm['seat_id'] }} {{ elm['row'] }} {{ elm['col'] }}</td>
	%end
</tr>
%end
</table>
%rebase base title='Buy tickets'