<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/rss/channel">
	<html>
	<body>

		<h1><xsl:value-of select="title"/></h1>
		<xsl:apply-templates select="image"/>
		<xsl:apply-templates select="item"/>
	</body>
	</html>
</xsl:template>

<xsl:template match="rss/channel/item">
	<h3>
		<a href="{link}"><xsl:value-of select="title"/></a>
	</h3>
	<p>
		<small>
			<xsl:value-of select="pubDate"/>
			<xsl:if test="author != ''">
				by <xsl:value-of select="author"/>
			</xsl:if>
		</small>
	</p>
	<p><xsl:value-of select="description"/></p>
	<hr />
</xsl:template>

<xsl:template match="rss/channel/image">
	<a href="{link}"><img src="{url}" alt="{title}" /></a>
</xsl:template>

</xsl:stylesheet>