-- buy ticket for selected movie
SET @MOVIE_TITLE = "ACADEMY DINOSAUR";
SET @MOVIE_TIME = "2014-03-10 12:03:51";
SET @THEATER_ID = 1;
SET @SEAT_ROW = 1;
SET @SEAT_COL = 1;

-- QUERIES
SET @FILM_ID = (SELECT film_id FROM film WHERE title = @MOVIE_TITLE);

SET @SHOW_ID = (SELECT sh.show_id
	FROM `show` sh
	INNER JOIN film fm
		ON sh.film_film_id = fm.film_id
	WHERE sh.theater_theater_id = @THEATER_ID
	AND sh.start_date = @MOVIE_TIME);

SET @SEAT_ID = (SELECT se.seat_id 
	FROM sakila.seat as se
	WHERE se.seat_id NOT IN (
		SELECT seat_seat_id
		FROM sakila.ticket
		WHERE show_show_id != se.seat_id
		AND theater_theater_id = @THEATER_ID) 
	AND se.theater_theater_id = @THEATER_ID
	AND se.col = @SEAT_COL
	AND se.row = @SEAT_ROW);

-- IF SEAT_ID == NULL - seat is taken
SELECT @SEAT_ID as 'seat_id';

-- CREATE TICKET
-- INSERT INTO ticket (price, seat_seat_id, show_show_id) VALUES (20, @SEAT_ID, @SHOW_ID);