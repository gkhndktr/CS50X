select title from movies where id in(select movie_id from stars where person_id IN (SELECT id from people where name ="Johnny Depp"))
INTERSECT
select title from movies where id in(select movie_id from stars where person_id IN (SELECT id from people where name ="Helena Bonham Carter"))
