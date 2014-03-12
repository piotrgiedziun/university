<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
	<html>
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
	<table border="1">
		<tr>
			<th>CHANEL</th>
			<th>TIME</th>
			<th>TITLE</th>
			<th>DESCRIPTION</th>
		</tr>
		<xsl:apply-templates select="DAY"/>
	</table>
	<hr />
</xsl:template>

<xsl:template match="DAY">
	<tr>
		<td colspan="4" style="text-align: center;"><xsl:value-of select="DATE"/></td>
	</tr>
	<xsl:apply-templates select="PROGRAMSLOT"/>
</xsl:template>

<xsl:template match="PROGRAMSLOT">
	<tr>
		<td><xsl:value-of select="../../@CHAN"/></td>
		<td><xsl:value-of select="TIME"/></td>
		<td><xsl:apply-templates select="TITLE"/></td>
		<td><xsl:apply-templates select="DESCRIPTION"/></td>
	</tr>
</xsl:template>

<xsl:template match="TITLE">
	<xsl:choose>
		<xsl:when test="@RATING">
			<strong>(<xsl:value-of select="@RATING"/>)</strong> - <xsl:value-of select="."/>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="."/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>


</xsl:stylesheet>
