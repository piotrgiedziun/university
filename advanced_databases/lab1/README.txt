Advanced databases - LAB 1 (10.03.2014)

THIS CODE IS BASED ON http://dev.mysql.com/doc/sakila/en/

LICENCE:
	http://dev.mysql.com/doc/sakila/en/sakila-preface.html#legalnotice

INSTALATION GUIDE:
	http://dev.mysql.com/doc/sakila/en/sakila-installation.html

INITIAL DATA:
	sakila-data.sql (from http://dev.mysql.com/doc/index-other.html	- sakila database)

LAB DESCRIPTION:
	- 2 movies can't start at the same time (same theater)
	- no two movies overlap in one theather
	- row & column have unique index
	- unique tickets for sit (no two ticket can be sell for same spot)
	- 3d,2d movies
	- buy ticket for selected movie (procedure)
	- search for 2 pair sits (procedure)
	- search for N pair sits (procedure)
	- 3 most expensive seats for selected movie (procedure)
	- 5th, 6th highest prices seats (procedure)
	- % of sold places for each show played at given date (procedure)