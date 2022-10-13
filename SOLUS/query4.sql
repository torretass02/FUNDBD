
/*
--Obtener de orderdetails las unidades x producto en cada order realizado.

SELECT od.ordernumber, 
       od.productcode, 
       od.quantityordered 
FROM   orderdetails od 




--Join con orders para obtener el customer de cada uno de los pedidos.

SELECT od.ordernumber     ordernumber, 
       od.productcode     productcode, 
       od.quantityordered quantity, 
       o.customernumber   customernumber 
FROM   orders o 
       JOIN orderdetails od 
         ON od.ordernumber = o.ordernumber 
	


	
--Agrupación por cliente sumando la cantidad de unidades pedidas 
--por cada uno de ellos (ordenado de mayor a menor).

SELECT o.customernumber        customernumber, 
       Sum(od.quantityordered) quantity 
FROM   orders o 
       JOIN orderdetails od 
         ON od.ordernumber = o.ordernumber 
GROUP  BY customernumber 
ORDER  BY quantity DESC 




--La tabla resultante de la consulta anterior la unimos con 
--cliente para obtener el id del empleado.

SELECT c.salesrepemployeenumber employeeid, 
       tabla1.customernumber, 
       tabla1.quantity 
FROM   customers c 
       JOIN (SELECT o.customernumber        customernumber, 
                    Sum(od.quantityordered) quantity 
             FROM   orders o 
                    JOIN orderdetails od 
                      ON od.ordernumber = o.ordernumber 
             GROUP  BY customernumber 
             ORDER  BY quantity DESC) AS tabla1 
         ON c.customernumber = tabla1.customernumber 
	


	
		 
--El resultado de la última consulta lo agrupamos por empleado y sumamos 
--el total de unidades por empleado (ordenado de mayor a menor).

SELECT c.salesrepemployeenumber employeeid, 
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
ORDER  BY quantity DESC 




--Hacemos join de la consulta anterior con employee para obtener el officecode.

SELECT e.officecode, 
       tabla2.employeeid, 
       tabla2.quantity 
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
	



	
--Agrupamos por officecode y sumamos las unidades totales que han vendido 
--todos los clientes pertenecientes a esa oficina.
--Ordenamos de mayor a menor la tabla con la restricción de 
--que muestre la oficina que más unidades vendió.
*/

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