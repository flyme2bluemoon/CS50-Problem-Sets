select title from ratings inner join movies on ratings.movie_id = movies.id where movie_id in (select movie_id from stars where person_id = (select id from people where name = "Chadwick Boseman")) order by rating desc limit 5;