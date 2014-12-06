import smtplib

SERVERS = ["156.17.40.148", "156.17.40.162", "156.17.40.46", "156.17.40.85"]

for SERVER in SERVERS:
    FROM = "test@pwr.wroc.pl"
    TO = ["xx@plonk.ict.pwr.wroc.pl"]

    message = """\
    From: %s
    To: %s
    Subject: %s

    %s
    """ % (FROM, ", ".join(TO), "test", "test")

    server = smtplib.SMTP(SERVER)
    server.set_debuglevel(True)
    try:
        server.sendmail(FROM, TO, message)
    except smtplib.SMTPRecipientsRefused, e:
        print SERVER, e
    else:
        print SERVER, "ok"
    server.quit()
