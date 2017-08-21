BEGIN TRANSACTION;

.header ON
.mode column

/*a*/
SELECT count(roll_no) AS 'number of married students'
FROM student
WHERE married = 'yes';

/*b*/
SELECT count(hall_no) AS 'number of students in married hostels'
FROM hostel
WHERE type = 'married';

/*c*/
SELECT count(*) AS '#students'
FROM student;

SELECT count(*) AS '#faculty'
FROM staff_and_faculty
WHERE staff_or_facul = 'faculty';

SELECT count(*) AS '#staff'
FROM staff_and_faculty
WHERE staff_or_facul = 'staff';

SELECT(
	SELECT count(*)
	FROM (SELECT DISTINCT fam_id FROM student_family)
)+(
	SELECT count(*)
	FROM (SELECT DISTINCT fam_id FROM faculty_family)
) AS '#family';

SELECT(
	SELECT count(*)
	FROM student
)+(
	SELECT count(*)
	FROM staff_and_faculty
)+(
	SELECT count(*)
	FROM (SELECT DISTINCT fam_id FROM student_family)
)+(
	SELECT count(*)
	FROM (SELECT DISTINCT fam_id FROM faculty_family)
) AS '#TOTAL';

/*d*/ 
SELECT avg(count) AS '#family per faculty'
FROM(
	SELECT count(*) AS 'count'
	FROM staff_and_faculty INNER JOIN faculty_family ON staff_and_faculty.id = faculty_family.id
	WHERE staff_or_facul = 'faculty'
	GROUP BY faculty_family.id);

/*e*/
SELECT q.id,f.name,cnt AS '#deps'
FROM (
SELECT head_id AS 'id', count(head_id) AS 'cnt'
FROM department
GROUP BY head_id
HAVING count(head_id) > 1) AS 'q' INNER JOIN staff_and_faculty AS 'f' ON q.id = f.id;

/*f*/
SELECT 100.0 * (
	SELECT count(*) FROM student WHERE advisor1 != '' AND ug_or_pg = 'ug'
)/( SELECT count(*) FROM student WHERE ug_or_pg = 'ug') AS '%ug students having advisor';

/*g*/
SELECT count(*)
FROM staff_and_faculty AS 'f' INNER JOIN student AS 's' ON f.id = s.advisor2
WHERE advisor2 != '' AND s.dept != f.dept;  

COMMIT;