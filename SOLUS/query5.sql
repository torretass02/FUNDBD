/*
--Clientes que han realizado un PEDIDO en el año 2003.
--(Utilizamos distinct para eliminar las repeticiones)

SELECT DISTINCT o.customernumber 
FROM   orders o 
WHERE  o.orderdate >= '2003-01-01' 
       AND o.shippeddate <= '2003-12-31' 
       AND o.shippeddate IS NOT NULL 


--Clientes que han realizado un PAGO en el año 2003.

SELECT DISTINCT pt.customernumber 
FROM   payments pt 
WHERE  pt.paymentdate >= '2003-01-01' 
       AND pt.paymentdate <= '2003-12-31' 


--Unión de los clientes que han realizado un pedido
--con los que han pagado en 2003.

(SELECT DISTINCT o.customernumber 
 FROM   orders o 
 WHERE  o.orderdate >= '2003-01-01' 
        AND o.shippeddate <= '2003-12-31' 
        AND o.shippeddate IS NOT NULL) 
UNION 
(SELECT DISTINCT pt.customernumber 
 FROM   payments pt 
 WHERE  pt.paymentdate >= '2003-01-01' 
        AND pt.paymentdate <= '2003-12-31') 


--Hacemos join con customer para obtener 
--el id del empleado que vende al cliente.

SELECT c.customernumber, 
       c.salesrepemployeenumber 
FROM   customers c 
       JOIN ((SELECT DISTINCT o.customernumber 
              FROM   orders o 
              WHERE  o.orderdate >= '2003-01-01' 
                     AND o.shippeddate <= '2003-12-31' 
                     AND o.shippeddate IS NOT NULL) 
             UNION 
             (SELECT DISTINCT pt.customernumber 
              FROM   payments pt 
              WHERE  pt.paymentdate >= '2003-01-01' 
                     AND pt.paymentdate <= '2003-12-31'))AS tabla1 
         ON c.customernumber = tabla1.customernumber 
		

--A continuación, hacemos join con employee para 
--saber la oficina en la que trabaja cada uno de los empleados.

SELECT c.customernumber, 
       c.salesrepemployeenumber, 
       e.officecode 
FROM   customers c 
       JOIN ((SELECT DISTINCT o.customernumber 
              FROM   orders o 
              WHERE  o.orderdate >= '2003-01-01' 
                     AND o.shippeddate <= '2003-12-31' 
                     AND o.shippeddate IS NOT NULL) 
             UNION 
             (SELECT DISTINCT pt.customernumber 
              FROM   payments pt 
              WHERE  pt.paymentdate >= '2003-01-01' 
                     AND pt.paymentdate <= '2003-12-31'))AS tabla1 
         ON c.customernumber = tabla1.customernumber 
       JOIN employees e 
         ON e.employeenumber = c.salesrepemployeenumber 


--Hacemos join con offices para saber el país de cada una de las oficinas y mostramos  
--officecode y country. El siguiente paso es agrupar por country y officecode 
--para eliminar repeticiones.

SELECT e.officecode, 
       ofc.country 
FROM   customers c 
       JOIN ((SELECT DISTINCT o.customernumber 
              FROM   orders o 
              WHERE  o.orderdate >= '2003-01-01' 
                     AND o.shippeddate <= '2003-12-31' 
                     AND o.shippeddate IS NOT NULL) 
             UNION 
             (SELECT DISTINCT pt.customernumber 
              FROM   payments pt 
              WHERE  pt.paymentdate >= '2003-01-01' 
                     AND pt.paymentdate <= '2003-12-31'))AS tabla1 
         ON c.customernumber = tabla1.customernumber 
       JOIN employees e 
         ON e.employeenumber = c.salesrepemployeenumber 
       JOIN offices ofc 
         ON ofc.officecode = e.officecode 
GROUP  BY e.officecode, 
          ofc.country 


--Obtenemos las que NO HAN COMPRADO...
--(en las anteriores consultas hemos conseguido 
--las oficinas que han recibido algún pedido o realizado algún pago).

(SELECT o.officecode, 
        o.country 
 FROM   offices o) 
EXCEPT 
(SELECT e.officecode, 
        ofc.country 
 FROM   customers c 
        JOIN ((SELECT DISTINCT o.customernumber 
               FROM   orders o 
               WHERE  o.orderdate >= '2003-01-01' 
                      AND o.shippeddate <= '2003-12-31' 
                      AND o.shippeddate IS NOT NULL) 
              UNION 
              (SELECT DISTINCT pt.customernumber 
               FROM   payments pt 
               WHERE  pt.paymentdate >= '2003-01-01' 
                      AND pt.paymentdate <= '2003-12-31'))AS tabla1 
          ON c.customernumber = tabla1.customernumber 
        JOIN employees e 
          ON e.employeenumber = c.salesrepemployeenumber 
        JOIN offices ofc 
          ON ofc.officecode = e.officecode 
 GROUP  BY e.officecode, 
           ofc.country) 



*/
--Agrupamos las oficinas por país, contamos el número de oficinas
--y ordenamos de mayor a menor.

SELECT tabla2.country country, 
       Count(*)       numoffices 
FROM   ((SELECT o.officecode, 
                o.country 
         FROM   offices o) 
        EXCEPT 
        (SELECT e.officecode, 
                ofc.country 
         FROM   customers c 
                JOIN ((SELECT DISTINCT o.customernumber 
                       FROM   orders o 
                       WHERE  o.orderdate >= '2003-01-01' 
                              AND o.shippeddate <= '2003-12-31' 
                              AND o.shippeddate IS NOT NULL) 
                      UNION 
                      (SELECT DISTINCT pt.customernumber 
                       FROM   payments pt 
                       WHERE  pt.paymentdate >= '2003-01-01' 
                              AND pt.paymentdate <= '2003-12-31'))AS tabla1 
                  ON c.customernumber = tabla1.customernumber 
                JOIN employees e 
                  ON e.employeenumber = c.salesrepemployeenumber 
                JOIN offices ofc 
                  ON ofc.officecode = e.officecode 
         GROUP  BY e.officecode, 
                   ofc.country)) AS tabla2 
GROUP  BY tabla2.country 
ORDER  BY numoffices DESC
