SELECT title, rating from movies join ratings on movies.id = ratings.movie_id
where id in
(select movie_id from stars where person_id =
(SELECT id from people where name="Chadwick Boseman"))
order by rating DESC
limit 5