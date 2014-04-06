-- % of sold places for each show played at given date
SET @SHOW_ID = 2;
SET @THEATER_ID = (SELECT theater_theater_id FROM `show` WHERE show_id = @SHOW_ID);

SET @SEATS_ALL_COUNT = (SELECT COUNT(*) FROM `seat` WHERE theater_theater_id = @THEATER_ID);
SET @SEATS_TAKEN_COUNT = (SELECT COUNT(*) FROM `ticket` WHERE show_show_id = @SHOW_ID);

-- SELECT @SEATS_TAKEN_COUNT*100/@SEATS_ALL_COUNT; 


-- SELECT count_taken_seat*100/count_all_seat
--   FROM (SELECT COUNT(se.seat_id) as count_all_seat, COUNT(ti.ticket_id) as count_taken_seat FROM `seat` se
-- 	LEFT JOIN  `ticket` ti
-- 	ON ti.seat_seat_id = se.seat_id) AS t1;
-- 
-- SELECT COUNT(se.seat_id), COUNT(ti.ticket_id)
-- FROM seat as se, ticket as ti
-- WHERE se.seat_id = ti.seat_seat_id OR se.seat_id = NULL;

SELECT count_taken_seat*100/count_all_seat
  FROM (SELECT COUNT(se.seat_id) as count_all_seat FROM seat se) AS t1,
	(SELECT COUNT(ti.ticket_id) as count_taken_seat FROM ticket ti WHERE ti.seat_seat_id = se.seat_id) AS t2;