<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
	<html>
	<body>
		<table border="1">
			<tr>
				<th>Name</th>
				<th>Surname</th>
				<th>Home address</th>
				<th>Phone</th>
				<th>Mobile</th>
				<th>Job</th>
			</tr>
			<xsl:for-each select="contact">
				<tr>
					<td><xsl:value-of select="name"/></td>
					<td><xsl:value-of select="surname"/></td>
					<td><xsl:value-of select="home_address"/></td>
					<td><xsl:value-of select="phone"/></td>
					<td><xsl:value-of select="mobile"/></td>
					<td><xsl:value-of select="job"/></td>
				</tr>
			</xsl:for-each>
		</table>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>