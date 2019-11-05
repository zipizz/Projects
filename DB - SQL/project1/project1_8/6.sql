with CTE as
(select T."NAME",T."STUDENT_ID",T."MAJOR_ID",sum(T."CREDIT") as "SUM_CREDIT",sum(T."CREDIT"*S."GRADE")/sum(T."CREDIT") as "AVG_GRADE"
from ("STUDENTS" natural join "COURSE_REGISTRATION" natural join "COURSE") as T inner join "GRADE" as S
on (T."STUDENT_ID",T."COURSE_ID") = (S."STUDENT_ID",S."COURSE_ID")
where T."GRADE"=4
group by T."STUDENT_ID"
having sum(T."CREDIT") >= 40)
select left(A."NAME",1)||repeat('*',length(A."NAME")-1) as "NAME"
,A."STUDENT_ID",A."MAJOR_NAME",A."COLLEGE_NAME"
from (CTE natural join "COLLEGE") as A
where A."AVG_GRADE" = (
select max("AVG_GRADE")
from CTE
) or A."AVG_GRADE" = (
select min("AVG_GRADE")
from CTE);