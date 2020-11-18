select title from movies where id in (select johnny.movie_id from stars as johnny inner join stars as helena on johnny.movie_id=helena.movie_id where johnny.person_id = (select id from people where name = "Johnny Depp") and helena.person_id = (select id from people where name = "Helena Bonham Carter"));

-- select id from people where name = "Johnny Depp";
-- select id from people where name = "Helena Bonham Carter";

-- select movie_id from stars where person_id = (select id from people where name = "Johnny Depp") and person_id = (select id from people where name = "Helena Bonham Carter");

-- select title from movies where id in (select movie_id from stars where person_id = (select id from people where name = "Johnny Depp") and person_id = (select id from people where name = "Helena Bonham Carter"));

-- select movie_id from stars as johnny inner join stars as helena on johnny.movie_id=helena.movie_id where johnny.person_id = (select id from people where name = "Johnny Depp") and helena.person_id = (select id from people where name = "Helena Bonham Carter");