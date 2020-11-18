select name from people where id in (select person_id from stars where movie_id in (select movie_id from stars where person_id = (select id from people where name = "Kevin Bacon" and birth = 1958))) and name != "Kevin Bacon";

-- select id from people where name = "Kevin Bacon" and birth = 1958;

-- select movie_id from stars where person_id = (select id from people where name = "Kevin Bacon" and birth = 1958);

-- select person_id from stars where movie_id in (select movie_id from stars where person_id = (select id from people where name = "Kevin Bacon" and birth = 1958));

-- select name from people where id in (select person_id from stars where movie_id in (select movie_id from stars where person_id = (select id from people where name = "Kevin Bacon" and birth = 1958))) and name != "Kevin Bacon";