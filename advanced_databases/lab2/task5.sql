SET @MOVIE_ID = 1;
SET @SHOW_ID = 2;

SET @THEATER_ID = (SELECT theater_theater_id FROM `show` WHERE show_id = @SHOW_ID);

-- SELECT price FROM `seat` WHERE theater_theater_id = @THEATER_ID ORDER BY price DESC LIMIT 1;
SELECT price FROM `ticket` WHERE show_show_id = @SHOW_ID ORDER BY price DESC LIMIT 1;