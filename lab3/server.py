#!/usr/bin/python
import json
import bottle_mysql
import bottle
from bottle import route, run, template


app = bottle.Bottle()
# dbhost is optional, default is localhost
plugin = bottle_mysql.Plugin(dbuser='root', dbpass='', dbname='sakila')
app.install(plugin)

@app.route('/movies')
def movies(db):
	db.execute('SELECT * from film;')
	rows = db.fetchall()
	if rows:
		return template('show_film', films=rows)

@app.route('/shows/<cinema_id>')
def shows(db, cinema_id):
	cinema_id = int(cinema_id)
	db.execute('SELECT * FROM `show` as sh INNER JOIN `film` fi ON sh.film_film_id = fi.film_id WHERE sh.theater_theater_id IN (SELECT theater_id FROM `theater` WHERE cinema_cinema_id = %d);' % (cinema_id, ))
	rows = db.fetchall()
	if rows:
		return template('show_shows', shows=rows)

@app.route('/cinemas')
def cinemas(db):
	db.execute('SELECT * FROM `cinema`;')
	rows = db.fetchall()
	if rows:
		return template('show_cinemas', cinemas=rows)

@app.route('/tickets/<show_id>')
def tickets(db, show_id):
	show_id = int(show_id)
	db.execute("""SELECT 
		    se . *, ti.ticket_id
		FROM
		    `show` sh
		        INNER JOIN
		    `seat` se ON sh.theater_theater_id = se.theater_theater_id
				LEFT JOIN
		    `ticket` ti ON se.seat_id = ti.seat_seat_id
		WHERE
		    sh.show_id = %d
		ORDER BY col;""" % (show_id,))
	rows = db.fetchall()
	rows_fixed = {}
	rows_list = []
	for row in rows:
		if not row['row'] in rows_fixed:
			rows_fixed[row['row']] = []
		rows_fixed[row['row']].append(row)

	for key,value in rows_fixed.items():
		rows_list.append(value)

	if rows:
		return template('show_tickets', tickets=rows_list)

@app.route('/task1')
def task1(db):
	db.execute('SELECT SQL_NO_CACHE se.* FROM `show` sh INNER JOIN `seat` se ON sh.theater_theater_id = se.theater_theater_id WHERE sh.show_id = 1 ORDER BY col;')
	rows = db.fetchall()
	return template('<pre style="white-space: pre-wrap;white-space: -moz-pre-wrap;white-space: -pre-wrap;white-space: -o-pre-wrap;word-wrap: break-word;">{{html}}</pre>', html=json.dumps(rows))

@app.route('/')
def index(db):
	return template('index')

app.run(host='localhost', port=8080, reloader=True)