--BEGINNER QUERIES

--1. Titles of all movies that were produced in the 30 years starting 1970. [886542]
SELECT title 
FROM title 
WHERE production_year 
BETWEEN 1970 AND 1999;
--2. Unique codes for the countries of origin for all movie companies. [235]
SELECT DISTINCT(country_code) 
FROM company_name;
--3. Unique Keywords. [236627]
SELECT COUNT(DISTINCT(keyword)) 
FROM keyword;
--4. Companies that do not have the word ’Group’ in their name. [358344]
SELECT COUNT(name) 
FROM company_name WHERE name NOT LIKE '%Group%';
--5. All info about persons that contain the word ’hamster’. [69]
SELECT info 
FROM person_info 
WHERE info LIKE '%hamster%'

--Intermediate Queries

--1. what are the 5 years with the most produced movies? Print only the years. [2016, 2015,2014, 2013, 2017]
SELECT production_year 
FROM title 
WHERE production_year IS NOT NULL
GROUP BY production_year 
ORDER BY COUNT(*) DESC 
LIMIT 5;
--2. What is the title of the newest movie? [’100 Years’]
SELECT title 
FROM title 
WHERE production_year = (SELECT MAX(production_year) from title);
--3. For the movie with the ID 4288112: report the names of the people that played in the movie, their roles, and the title of this movie. [1140]
--SELECT column_name, data_type FROM information_schema.columns WHERE table_name = 'cast_info';
SELECT a.name,b.role,c.title
FROM cast_info p
JOIN aka_name a ON a.id = p.person_id
JOIN role_type b ON b.id = p.role_id
JOIN title c ON c.id = p.movie_id
WHERE movie_id = 4288112;
--4. What are the names of movies that will be produced in the future? Do NOT hardcode the current year for the comparison, use a Postgres internal. [2]


--Complex Queries

--1. Report the unique names and corresponding type of the distributors or production companies, that worked on any movie [412801]
SELECT DISTINCT b.name, c.kind
FROM movie_companies a
JOIN company_name b ON a.company_id = b.id
JOIN company_type c ON a.company_type_id = c.id;
--2. Which unique keywords occur together with ’gaming’? [4197]
SELECT DISTINCT a.keyword
FROM keyword a
JOIN movie_keyword b ON a.id = b.keyword_id
WHERE b.movie_id IN (
    SELECT movie_id
    FROM movie_keyword c
    JOIN keyword d ON c.keyword_id = d.id
    WHERE d.keyword = 'gaming'
)
AND a.keyword <> 'gaming';
--3. For every valid year, calculate the smallest ”release date” and extract the country of origin. Report the year and the extracted string as Origin. [142]