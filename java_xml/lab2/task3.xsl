<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
	<html>
	<style>
		table {
			border-collapse:collapse;
			maring: 0 auto;
		}
		table, td, th {
			border:1px solid black;
			padding: 10px;
		}
		th {
			background-color: #56aaff;
			b
		}
		img {
			height: 200px;
		}
	</style>
	<script>
		function nice() {
			var color = ['white', '#caf0fe'];
			var text_color = ['white', 'black'];
			var color_index = 0;
			setInterval(function() {
				document.getElementById('table').style.background = color[color_index];
				document.getElementById('title').style.color = text_color[color_index];
				color_index = (color_index == 0) ? 1 : 0;
			}, 600);
		}
	</script>
	<body onload="nice()">
		<div style="text-align: center;">
			<img src="happy.gif" />
			<img src="happy.gif" />
			<img src="happy.gif" />
		</div>
		<h1 id="title" style="text-align: center;">List of employees</h1>
		<table id="table" border="1" width="100%">
			<tr>
				<th>#ID</th>
				<th>Name</th>
				<th>Surname</th>
				<th>Home address</th>
				<th>Mobile</th>
				<th>Job</th>
				<th>Salary</th>
			</tr>
			<xsl:for-each select="company/employee">
				<tr>
					<td><xsl:value-of select="@employee_id"/></td>
					<td><xsl:value-of select="name"/></td>
					<td><xsl:value-of select="surname"/></td>
					<td><xsl:value-of select="home_address"/></td>
					<td>
						<xsl:for-each select="mobile">
							<xsl:if test="@mobile_type">
								(<xsl:value-of select="@mobile_type"/>)
							</xsl:if>
							<xsl:value-of select="."/><br />
						</xsl:for-each>
					</td>
					<td><xsl:value-of select="job"/></td>
					<td>
						<xsl:choose>
							<xsl:when test="salary &gt; 19999">
								<b>####</b>
							</xsl:when>
							<xsl:otherwise>
								<xsl:value-of select="salary"/>&#160;<xsl:value-of select="salary/@currency"/>
							</xsl:otherwise>
						</xsl:choose>
					</td>
				</tr>
			</xsl:for-each>
		</table>
		<div style="text-align: center;">
			<img src="happy.gif" />
			<img src="happy.gif" />
			<img src="happy.gif" />
		</div>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>