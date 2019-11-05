

select "YEAR", "MAJOR_NAME", count("YEAR") as cnt

from "COLLEGE" as A, "COURSE" as B

where A."MAJOR_ID" = B."COURSE_ID_PREFIX" and B."COURSE_ID_PREFIX" != 'XYZ'

group by "YEAR", "MAJOR_NAME"

order by "YEAR", cnt desc;