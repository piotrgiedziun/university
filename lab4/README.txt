LAB 4

1) Performance issues involved with using indexes on VARCHAR fields.
How does prefixing them influence index size and QPS (query per second). [PART 5 of book]

2) Explain why EXPLAIN SELECT SQL_NO_CACHE * FROM sakila.ticket ORDER BY theater_id DESC is not using theater_id_price_idx

3) Explain why EXPLAIN SELECT ticket.price FROM ticket LEFT JOIN theater on theater.theater_id = ticket.theater_id ORDER BY ticket.price DESC is not using price_idx INDEX.

Please remember to provide explanation for why is MySQL choosing a full table scan instead of using index on price colum when doing a SELECT * FROM tickets ORDER BY price.