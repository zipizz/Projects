select "DAY_OF_WEEK",
case 
when "NO"=0 then '8:00 ~ 8:50'
when "NO"=1 then '9:00 ~ 9:50'
when "NO"=2 then '10:00 ~ 10:50'
when "NO"=3 then '11:00 ~ 11:50'
when "NO"=4 then '12:00 ~ 12:50'
when "NO"=5 then '13:00 ~ 13:50'
when "NO"=6 then '14:00 ~ 14:50'
when "NO"=7 then '15:00 ~ 15:50'
when "NO"=8 then '16:00 ~ 16:50'
when "NO"=9 then '17:00 ~ 17:50'
when "NO"=10 then '18:00 ~ 18:50' end
from "DAY_OF_WEEK","TIMETABLE"
where ("DAY_OF_WEEK","NO") not in ( 
select distinct "DAY_OF_WEEK","NO"
from "COURSE_REGISTRATION" natural join "COURSE" natural join "COURSE_TO_TIME"
where ("STUDENT_ID"='2018111111' or "STUDENT_ID"='2017222222')
and "YEAR"=2018 and "SEMESTER"=2
) and not ("DAY_OF_WEEK" = 'SAT' or "DAY_OF_WEEK" = 'SUN')
order by "NO";