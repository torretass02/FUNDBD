/*

Debemos obtener una lista de los empleados que han reportado a los empleados que
hayan reportado al presidente, el cuál este último no reporta a nadie. 
Por lo cual debemos empezar por esa última información, identificándole en la tabla
como la persona que tiene el valor de reportsto como 'NULL'. 

Una vez le tenemos identificado, debemos buscar en la misma tabla los empleados que 
hayan reportado al presidente, por lo que buscamos en la columna reportsto el 
employeenumber del presidente. 

El último paso sería indicar quíenes reportaron a los mencionados anteriormente, así
que procedemos a hacer un join con la tabla creada antes, para obtener la información
que deseamos. Representamos este grupo de personas con su employeenumber y si lastname.

*/
SELECT e.employeenumber,
       e.lastname
FROM   employees e
       JOIN (SELECT e.employeenumber,
                    e.lastname
             FROM   employees e
             WHERE  e.reportsto = (SELECT e.employeenumber
                                   FROM   employees e
                                   WHERE  e.reportsto IS NULL)) AS t
         ON e.reportsto = t.employeenumber 