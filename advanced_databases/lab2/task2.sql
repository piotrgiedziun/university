-- lista wolnych miejsc
SELECT 
    *
FROM
    sakila.seat
WHERE
    seat_id NOT IN (SELECT 
            seat_seat_id
        FROM
            sakila.ticket
        WHERE
            show_show_id = 2)
        AND theater_theater_id = 1;