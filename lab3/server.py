#!/usr/bin/python
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
	db.execute('SELECT se.* FROM `show` sh INNER JOIN `seat` se ON sh.theater_theater_id = se.theater_theater_id WHERE sh.show_id = %d;' % (show_id,))
	rows = db.fetchall()
	rows_fixed = {}
	for row in rows:
		if not row['seat_id'] in rows_fixed:
			print row['seat_id']
			rows_fixed[row['seat_id']] = []
		rows_fixed[row['seat_id']].append(row)
	print rows_fixed
	if rows:
		return template('show_tickets', tickets=rows_fixed)

@app.route('/')
def index(db):
	return template('index')

app.run(host='localhost', port=8080, reloader=True)