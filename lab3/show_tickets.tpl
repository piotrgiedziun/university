<p>List of cinemas:</p>

<table border="1">
%for line in tickets:
<tr>
	%for elm in line:
		%if elm['ticket_id'] == None:
		<td style="background-color:green;">free</td>
		%else:
		<td style="background-color:red;">taken</td>
		%end

	%end
</tr>
%end
</table>
%rebase base title='Buy tickets'