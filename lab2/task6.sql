SET @THEATER_ID = 1;
SET @SHOW_ID = 1;

SELECT se.seat_id, se2.seat_id
	FROM `seat` se
	INNER JOIN `seat` se2
		ON se.theater_theater_id = se2.theater_theater_id
		AND se.row = se2.row
		AND se.col = se2.col + 1
	WHERE se.theater_theater_id = @THEATER_ID
	AND se.seat_id NOT IN (SELECT seat_seat_id FROM sakila.ticket WHERE show_show_id = @SHOW_ID)
	AND se2.seat_id NOT IN (SELECT seat_seat_id FROM sakila.ticket WHERE show_show_id = @SHOW_ID);