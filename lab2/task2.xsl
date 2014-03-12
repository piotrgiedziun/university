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
	}
	th {
		background-color: #56aaff;
	}
	.day {
		background-color: #aad4ff;
	}
	</style>
	<body>
		<xsl:apply-templates select="TVSCHEDULE"/>
	</body>
	</html>
</xsl:template>

<xsl:template match="TVSCHEDULE">
	<h2><xsl:value-of select="@NAME"/></h2>
	<xsl:apply-templates select="CHANNEL"/>
</xsl:template>

<xsl:template match="CHANNEL">
	<table border="1" width="800px">
		<tr>
			<th rowspan="2">CHANEL</th>
			<th rowspan="2">TIME</th>
			<th colspan="2">PROGRAM</th>
			<th rowspan="2">DESCRIPTION</th>
		</tr>
		<tr>
			<th>RATING</th>
			<th>TITLE</th>
		</tr> 
		<xsl:apply-templates select="DAY"/>
	</table>
	<hr />
</xsl:template>

<xsl:template match="DAY">
	<tr>
		<td class="day" colspan="5" style="text-align: center;"><xsl:value-of select="DATE"/></td>
	</tr>
	<xsl:apply-templates select="PROGRAMSLOT"/>
</xsl:template>

<xsl:template match="PROGRAMSLOT">
	<tr>
		<td><xsl:value-of select="../../@CHAN"/></td>
		<td><xsl:value-of select="TIME"/></td>
		<xsl:apply-templates select="TITLE"/>
		<td><xsl:apply-templates select="DESCRIPTION"/></td>
	</tr>
</xsl:template>

<xsl:template match="TITLE">
	<xsl:choose>
		<xsl:when test="@RATING">
			<td><xsl:value-of select="@RATING"/></td><td><xsl:value-of select="."/></td>
		</xsl:when>
		<xsl:otherwise>
			<td>-</td><td><xsl:value-of select="."/></td>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>


</xsl:stylesheet>
