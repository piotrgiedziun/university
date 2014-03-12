<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
	<html>
	<body>
		<div style="width:400px">
		<xsl:for-each select="mails/mail">
			Message to <xsl:value-of select="@mail"/>
			<br/>---------------<br/>
			Dear <xsl:value-of select="author"/>,<br/>
			<br/>
			Your paper under title <xsl:value-of select="title"/> that was register under nr ID <xsl:value-of select="id"/> was successfully uploaded to a DepCoS-RELCOMEX conference. <br/>
			<br/>
			 You can check that the file is correctly uploaded by following this link: <a href="#">fake link</a><br/>

			 Thanks for submitting to DepCoS-RELCOMEX 2011. Until the deadline, you can still update your information or transmit a revised file.<br/><br/>

			 Best regards,<br/><br/>

			 DepCoS-RELCOMEX 2011 chairs.
			 <hr/>
		</xsl:for-each>
		</div>
	</body>
	</html>
</xsl:template>

</xsl:stylesheet>