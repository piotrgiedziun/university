-- 5th, 6th highest prices seats
-- SELECT price FROM sakila.seat ORDER BY price DESC LIMIT 2, 4;
SELECT seat_id,GROUP_CONCAT(DISTINCT seat_id)
FROM sakila.seat
GROUP BY seat_id
ORDER BY GROUP_CONCAT(DISTINCT seat_id) ASC;