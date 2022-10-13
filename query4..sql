SELECT e.officecode, 
       Sum(tabla2.quantity) quantity 
FROM   employees e 
       JOIN (SELECT c.salesrepemployeenumber employeeid, 
                    Sum(tabla1.quantity)     quantity 
             FROM   customers c 
                    JOIN (SELECT o.customernumber        customernumber, 
                                 Sum(od.quantityordered) quantity 
                          FROM   orders o 
                                 JOIN orderdetails od 
                                   ON od.ordernumber = o.ordernumber 
                          GROUP  BY customernumber 
                          ORDER  BY quantity DESC) AS tabla1 
                      ON c.customernumber = tabla1.customernumber 
             GROUP  BY employeeid 
             ORDER  BY quantity DESC) AS tabla2 
         ON e.employeenumber = tabla2.employeeid 
GROUP  BY e.officecode 
ORDER  BY quantity DESC 
LIMIT  1 