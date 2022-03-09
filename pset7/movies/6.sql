SELECT avg(rating) FROM movies 
JOIN ratings ON ratings.movie_id=movies.id
WHERE YEAR=2012