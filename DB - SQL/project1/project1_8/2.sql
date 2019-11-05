
select "COURSE_NAME"

from "COURSE" as CC, (select distinct A."COURSE_ID", A."STUDENT_ID"
from "COURSE_REGISTRATION" as A, "COURSE_REGISTRATION" as B, "COURSE" as C, "COURSE" as D
where A."STUDENT_ID" = B."STUDENT_ID" and A."COURSE_ID" != B."COURSE_ID" 
      and A."COURSE_ID" = C."COURSE_ID" and B."COURSE_ID" = D."COURSE_ID"
      and C."COURSE_ID_PREFIX"=D."COURSE_ID_PREFIX" and C."COURSE_ID_NO"=D."COURSE_ID_NO" ) as AA

where AA."COURSE_ID" = CC."COURSE_ID"
group by "COURSE_NAME"
order by count(CC."COURSE_ID") desc
limit 3;
