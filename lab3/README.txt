LAB 3

- determine the influence of indexing on insert performance
	- time the queries WITHOUT index on tickers.ID_THEATER
		> SELECT SQL_NO_CACHE * FROM `ticket` WHERE theater_id = 3; took 0.035 sec
		> EXPLAIN SELECT * FROM `ticket` WHERE theater_id = 3; 
		> id,select_type,table,type,possible_keys,key,key_len,ref,rows,Extra
		> 1,SIMPLE,ticket,ALL,NULL,NULL,NULL,NULL,99814,"Using where"

	- time the queries WITH index on tickers.ID_THEATER
		> SELECT SQL_NO_CACHE * FROM `ticket` WHERE theater_id = 3; took 0.001 sec
		> EXPLAIN SELECT * FROM `ticket` WHERE theater_id = 3;
		> id,select_type,table,type,possible_keys,key,key_len,ref,rows,Extra
		> 1,SIMPLE,ticket,ref,theater_id,theater_id,4,const,100,NULL

- using infor form task (1) try to find a way to reduce the avg time per query
	> using indexes improve performance

- repeat the prcedure for a query that finds the number of tickets sold in a time interval of 1 year (DATE_ADD)
	>   SELECT 
		    ti . *, sh.start_date
		FROM
		    `ticket` ti
		        INNER JOIN
		    `show` sh ON ti.show_show_id = sh.show_id
		WHERE
		    start_date > now()
		        AND start_date < DATE_ADD(now(), INTERVAL 1 YEAR);

- performance of indexes for strings find tickets sold for movies
	- starting with "the" -> "the%"
	- having the word "the" -> "%the%" 