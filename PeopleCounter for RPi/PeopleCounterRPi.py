#!/usr/bin/python

import requests
import RPi.GPIO as GPIO
from time import sleep

door_id = 5

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)
GPIO.setup(17, GPIO.IN)
GPIO.setup(27, GPIO.IN)

GPIO.output(18, True)
print "Application ready..."
while True:
	if GPIO.input(17):
		GPIO.output(18, False)
		url_enter  = "http://flextronicschallenge.herokuapp.com/counts/door/"+str(door_id)+".json?enter=1"
		print "Enter 1"
		response = requests.get(url=url_enter)
		print response.status_code
		print response.text
		print "***********************"
		GPIO.output(18, True)
	if GPIO.input(27):
		GPIO.output(18, False)
		url_leave  = "http://flextronicschallenge.herokuapp.com/counts/door/"+str(door_id)+".json?leave=1"
		print "Leave 1"
		response = requests.get(url=url_leave)
		print response.status_code
		print response.text
		print "***********************"
		GPIO.output(18, True)

GPIO.cleanup()
