#!/bin/python

from flask import Flask
import threading
import time
from datetime import datetime, timedelta
import sys
import RPi.GPIO as GPIO

PIN = 25
app = Flask(__name__)

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(PIN, GPIO.OUT)

led_status = False
time_thread = None

@app.route('/time/off')
def time_trigger_off():
	print "off timer"
	global time_thread
	if time_thread != None:
		time_thread.working = False
	return "ok"

@app.route('/time/<h>/<m>')
def time_trigger(h,m):
	print "start timer", h,m
	global time_thread
	time_thread = timeThread("%s:%s" % (h,m))
	time_thread.start()
	return "ok"

@app.route('/location/<x>/<y>')
def location_trigger(x,y):
	print "location", x, y

	return "ok"

@app.route('/status/<status>')
def led(status=None):

	global led_status
	global PIN

	if not status in ["on", "off"]:
		if led_status:
			return "on"
		else:
			return "off"

	if led_status:
		led_status = False
		GPIO.output(PIN, GPIO.LOW)
		return "off"
	else:
		led_status = True
		GPIO.output(PIN, GPIO.HIGH)
		return "on"

@app.route('/info')
def info():
	return """<div style="font-size:20px">
	System: HOME<br/>
	Status: ON<br/>
	Uptime: %(uptime)s<br/>
	</div>
	""" % {
		'uptime': get_uptime()
	}

def get_uptime():
	with open('/proc/uptime', 'r') as f:
	    uptime_seconds = float(f.readline().split()[0])
	    uptime_string = str(timedelta(seconds = uptime_seconds))

	return uptime_string

def date_diff(time1, time2):
	diff = datetime.strptime(time1, '%H:%M') - datetime.strptime(time2, '%H:%M')
	return diff.seconds

class timeThread(threading.Thread):
	def __init__(self, time1):
		threading.Thread.__init__(self)
		self.time1 = time1
		self.working = True

	def run(self):
		print "Starting " + self.name
		self.print_time(self.time1)
		print "Exiting " + self.name

	def print_time(self, time1):
		now = datetime.now()
		while self.working and date_diff(time1, now.strftime("%H:%M")) > 0:
			now = datetime.now()
			time.sleep(1)
			print "date diff: %d" % ( date_diff(time1, now.strftime("%H:%M")) )

		# event
		doEvent()

def doEvent():
	print "event"

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug = True)
    GPIO.cleanup()