/*
--¿Quién es el director?
SELECT e.employeenumber presidentid 
FROM   employees e 
WHERE  e.reportsto IS NULL 



--¿Quién reporta al director?
SELECT e.employeenumber, 
       e.lastname 
FROM   employees e 
WHERE  e.reportsto = (SELECT e.employeenumber presidentid 
                      FROM   employees e 
                      WHERE  e.reportsto IS NULL) 
					  


--¿Quiénes son los empleados que reportan a los empleados que reportan al director?
*/

SELECT e.employeenumber, 
       e.lastname 
FROM   employees e 
       JOIN (SELECT e.employeenumber employeenumber, 
                    e.lastname 
             FROM   employees e 
             WHERE  e.reportsto = (SELECT e.employeenumber presidentid 
                                   FROM   employees e 
                                   WHERE  e.reportsto IS NULL)) AS t 
         ON e.reportsto = t.employeenumber 