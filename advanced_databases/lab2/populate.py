#!/usr/bin/python
import MySQLdb
import random
from datetime import datetime as dt, timedelta

# MySQL format
DATE_FORMAT = '%Y-%m-%d %H:%M:%S'

db = MySQLdb.connect(host="localhost", user="root", passwd="", db="sakila")

cur = db.cursor() 

print "connected"

# truncate old data
cur.execute("SET FOREIGN_KEY_CHECKS = 0;");
cur.execute("TRUNCATE `ticket`;");
cur.execute("TRUNCATE `seat`;");
cur.execute("TRUNCATE `show`;");
cur.execute("TRUNCATE `cinema`;");
cur.execute("TRUNCATE `theater`;");
cur.execute("SET FOREIGN_KEY_CHECKS = 1;");

print "cleaned"

# create cinema
cur.execute("INSERT INTO `cinema` (name, address) VALUES ('cinema', 'wroclaw');")

seat_id = 0
for theater_id in range(1, 1001):
	#is_3D = random.randint(0,1)
	is_3D = 1
	query = "INSERT INTO `theater` (theater_id, name, is_3D, cinema_cinema_id) VALUES ('%d', 'theater%d', '%d', '1');" % (theater_id, theater_id, is_3D,)
	#print query
	cur.execute(query)
	theater_real_id = db.insert_id()

	# create seats for theater
	for seat_col in range(0, 10):
		for seat_row in range(0, 10):
			price = random.randint(18,25)
			query = "INSERT INTO `seat` (row, col, price, theater_theater_id) VALUES (%d, %d, %d, %d);" % (seat_row, seat_col, price, theater_real_id)
			#print ">", query
			cur.execute(query)

	# create shows
	now = dt.now() + timedelta(days=1)
	for show_id in range(0, 1):
		film_id = random.randint(1,999)
		now += timedelta(minutes=185);
		query = "INSERT INTO `show` (start_date, theater_theater_id, film_film_id) VALUES ('%s', %d, %d);" % (now.strftime(DATE_FORMAT), theater_real_id, film_id)
		#print ">", query
		cur.execute(query)
		show_real_id = db.insert_id()

		# craete ticket
		for seat_col in range(0, 10):
			for seat_row in range(0, 10):
				price = random.randint(18,25)
				# get seat_id
				seat_id += 1
				query = "INSERT INTO `ticket` (price, seat_seat_id, show_show_id, cinema_cinema_id, theater_id) VALUES (%d, %d, %d, 1, %d);" % (price, seat_id, show_real_id, theater_real_id)
				#print ">", query
				cur.execute(query)

db.commit()