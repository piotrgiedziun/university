#!/usr/bin/python
import os

class TestUnit:
	def __init__(self, inst_size, time_size):
		self.time_size = time_size
		self.inst_size = inst_size

# populate test TestUnit
tests = []
for inst_size in [10, 50, 100]:
	for time_size in [10, 50]:
		tests.append(TestUnit(inst_size, time_size))

# run tests
for test in tests:
	os.system("rm output.txt")
	os.system("python gen.py %d %d" % (test.inst_size, test.time_size))
	os.system("echo \"%d\t%d\t\c\" >> output.txt" % (test.inst_size, test.time_size))
	os.system("python app.py -output_json >> output.txt")
	os.system("cat output.txt")
