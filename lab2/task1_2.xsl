<xsl:stylesheet version="1.0"
 xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
 <xsl:output omit-xml-declaration="yes" indent="yes"/>

 <xsl:template match="/">
 	<html>
 	<body>
    	<table border="1"><xsl:apply-templates select="contact"/></table>
	</body>
	</html>
 </xsl:template>

 <xsl:template match="contact">
  <tr><xsl:apply-templates select="*"/></tr>
 </xsl:template>

 <xsl:template match="contact/*">
  <td><xsl:apply-templates select="node()"/></td>
 </xsl:template>

</xsl:stylesheet>