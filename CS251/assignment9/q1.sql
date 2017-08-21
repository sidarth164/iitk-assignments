BEGIN TRANSACTION;

CREATE TABLE IF NOT EXISTS student(
roll_no INT PRIMARY KEY,
name TEXT,
gender TEXT,
hall INT NOT NULL,
phone_no INT,
married TEXT,
dept TEXT,
advisor1 TEXT CHECK((ug_or_pg = 'pg' AND advisor1 !='') OR (ug_or_pg = 'ug')),
advisor2 TEXT,
ug_or_pg TEXT,
FOREIGN KEY(hall) REFERENCES hostel(hall_no),
FOREIGN KEY(dept) REFERENCES department(id),
FOREIGN KEY(advisor1) REFERENCES staff_and_faculty(id),
FOREIGN KEY(advisor2) REFERENCES staff_and_faculty(id)
);

CREATE TABLE IF NOT EXISTS staff_and_faculty(
id INT PRIMARY KEY,
name TEXT,
address TEXT NOT NULL,
phone_no INT,
dept TEXT,
staff_or_facul TEXT,
FOREIGN KEY(dept) REFERENCES department(id)
);

CREATE TABLE IF NOT EXISTS student_family(
fam_id INT NOT NULL,
name TEXT,
address TEXT NOT NULL,
phone_no INT,
relation TEXT,
rollno INT,
FOREIGN KEY(rollno) REFERENCES student(roll_no)
);

CREATE TABLE IF NOT EXISTS faculty_family(
fam_id INT NOT NULL,
name TEXT,
address TEXT NOT NULL,
phone_no INT,
relation TEXT,
id INT,
FOREIGN KEY(id) REFERENCES staff_and_faculty(id)
);

CREATE TABLE IF NOT EXISTS department(
id TEXT PRIMARY KEY,
name TEXT,
head_id INT,
FOREIGN KEY(head_id) REFERENCES staff_and_faculty(id)
);

CREATE TABLE IF NOT EXISTS hostel(
hall_no INT PRIMARY KEY,
type TEXT,
ug_or_pg TEXT
);

.mode csv
.import student.csv student
.import stfac.csv staff_and_faculty
.import stufam.csv student_family
.import stfacfam.csv faculty_family
.import department.csv department
.import hall.csv hostel

COMMIT;