#!/usr/bin/python
import MySQLdb
import random
import datetime as dt

db = MySQLdb.connect(host="localhost", user="root", passwd="", db="sakila")

cur = db.cursor() 

# create cinema
cur.execute("INSERT INTO cinema (name, address) VALUES ('cinema', 'wroclaw')")

for theater_id in range(0, 100):
	is_3D = random.randint(0,1)
	query = "INSERT INTO theater (theater_id, name, is_3D, cinema_cinema_id) VALUES ('theater%d', %d, 1)" % (theater_id, is_3D)
	cur.execute(query)
	theater_real_id = db.insert_id()

	# create seats for theater
	for seat_col in range(0, 10):
		for seat_row in range(0, 10):
			price = random.randint(18,25)
			query = "INSERT INTO seat (row, col, price, theater_theater_id) VALUES (%d, %d, %d, %d)" % (seat_row, seat_col, price, theater_real_id)
			cur.execute(query)

	# create shows
	now = dt.datetime.now()
	for show_id in range(0, 10):
		film_id = random.randint(1,1000)
		start_date = dt.datetime.combine(dt.date(1,1,1),t) + dt.timedelta(hours=2)).time()
		query = "INSERT INTO show (start_date, theater_theater_id, film_film_id) VALUES (%d, %d, %d)" % (start_date, theater_real_id, film_id)
		cur.execute(query)
