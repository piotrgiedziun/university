#!/usr/bin/python
from timeit import Timer

t = Timer('cur.execute("SELECT SQL_NO_CACHE * FROM `ticket` WHERE theater_id = 3;");cur.fetchall()', 'import MySQLdb;db = MySQLdb.connect(host="localhost", user="root", passwd="", db="sakila");cur = db.cursor()')
print "theater_id %0.3f sec " % t.timeit(100)

t = Timer('cur.execute("SELECT COUNT(*) FROM `ticket` ti INNER JOIN `show` sh ON ti.show_show_id = sh.show_id WHERE start_date > now() AND start_date < DATE_ADD(now(), INTERVAL 1 YEAR);");cur.fetchall()', 'import MySQLdb;db = MySQLdb.connect(host="localhost", user="root", passwd="", db="sakila");cur = db.cursor()')
print "date %0.3f sec " % t.timeit(1)


# DROP INDEX `theater_id` ON ticket;
# CREATE INDEX start_date_index ON `show` (start_date) USING BTREE;

# DROP INDEX `idx_title` ON `film`;
# DROP INDEX `idx_title` ON `film`;

t = Timer('cur.execute("SELECT SQL_NO_CACHE fi.title FROM `ticket` ti INNER JOIN `show` sh ON sh.show_id = ti.show_show_id LEFT JOIN `film` fi ON fi.film_id = sh.film_film_id WHERE fi.title LIKE \'%the%\'");cur.fetchall()', 'import MySQLdb;db = MySQLdb.connect(host="localhost", user="root", passwd="", db="sakila");cur = db.cursor()')
print "the+ %0.3f sec " % t.timeit(10)

t = Timer('cur.execute("SELECT SQL_NO_CACHE fi.title FROM `ticket` ti INNER JOIN `show` sh ON sh.show_id = ti.show_show_id LEFT JOIN `film` fi ON fi.film_id = sh.film_film_id WHERE fi.title LIKE \'the%\'");cur.fetchall()', 'import MySQLdb;db = MySQLdb.connect(host="localhost", user="root", passwd="", db="sakila");cur = db.cursor()')
print "+the+ %0.3f sec " % t.timeit(10)
