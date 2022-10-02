--VERSIÓN 1

/*
--Primero hacemos join de Orderdetails con Products para saber 
--el productline de cada producto de un order.

SELECT od.ordernumber, 
       od.productcode, 
       p.productline 
FROM   orderdetails od 
       JOIN products p 
         ON od.productcode = p.productcode 
		 
		 
		 
		 
--Hacemos join de la consulta anterior con orders para obtener la fecha en la que se realiza el pedido
--y la que se envía (no debe ser null el campo shippeddate).

SELECT tabla1.ordernumber, 
       tabla1.productcode, 
       tabla1.productline, 
       o.orderdate, 
       o.shippeddate 
FROM   orders o 
       JOIN (SELECT od.ordernumber ordernumber, 
                    od.productcode productcode, 
                    p.productline  productline 
             FROM   orderdetails od 
                    JOIN products p 
                      ON od.productcode = p.productcode) AS tabla1 
         ON o.ordernumber = tabla1.ordernumber 
WHERE  o.shippeddate IS NOT NULL 



--Calculamos la diferencia de días entre las fechas.

SELECT tabla1.ordernumber, 
       tabla1.productcode, 
       tabla1.productline, 
       ( o.shippeddate - o.orderdate ) diferenciadias 
FROM   orders o 
       JOIN (SELECT od.ordernumber ordernumber, 
                    od.productcode productcode, 
                    p.productline  productline 
             FROM   orderdetails od 
                    JOIN products p 
                      ON od.productcode = p.productcode) AS tabla1 
         ON o.ordernumber = tabla1.ordernumber 
WHERE  o.shippeddate IS NOT NULL 


*/
--Ahora agrupamos por productline, eso quiere decir que no necesitamos ni ordernumber ni productcode.
--Y hacemos el average entre la diferencia de días con 2 decimales.


SELECT tabla1.productline, 
       Round(Avg(o.shippeddate - o.orderdate), 2) tiempomedio 
FROM   orders o 
       JOIN (SELECT od.ordernumber ordernumber, 
                    od.productcode productcode, 
                    p.productline  productline 
             FROM   orderdetails od 
                    JOIN products p 
                      ON od.productcode = p.productcode) AS tabla1 
         ON o.ordernumber = tabla1.ordernumber 
WHERE  o.shippeddate IS NOT NULL 
GROUP  BY tabla1.productline



--VERSIÓN 2
/* 


--Primero hacemos join de Orderdetails con Products para 
--saber el productline de cada producto de un order.

SELECT od.ordernumber, 
       od.productcode, 
       p.productline 
FROM   orderdetails od 
       JOIN products p 
         ON od.productcode = p.productcode 
		 




--Hacemos join de la consulta anterior con orders para obtener la fecha en la que se realiza el pedido
--y la que se envía (no debe ser null el campo shippeddate).

SELECT tabla1.ordernumber, 
       tabla1.productcode, 
       tabla1.productline, 
       o.orderdate, 
       o.shippeddate 
FROM   orders o 
       JOIN (SELECT od.ordernumber ordernumber, 
                    od.productcode productcode, 
                    p.productline  productline 
             FROM   orderdetails od 
                    JOIN products p 
                      ON od.productcode = p.productcode) AS tabla1 
         ON o.ordernumber = tabla1.ordernumber 
WHERE  o.shippeddate IS NOT NULL 




--Calculamos la diferencia de días entre las fechas.

SELECT tabla1.ordernumber, 
       tabla1.productcode, 
       tabla1.productline, 
       ( o.shippeddate - o.orderdate ) diferenciadias 
FROM   orders o 
       JOIN (SELECT od.ordernumber ordernumber, 
                    od.productcode productcode, 
                    p.productline  productline 
             FROM   orderdetails od 
                    JOIN products p 
                      ON od.productcode = p.productcode) AS tabla1 
         ON o.ordernumber = tabla1.ordernumber 
WHERE  o.shippeddate IS NOT NULL 





--groupby por productline-ordernumber-diferenciadias para eliminar repeticiones 
--por pedido del mismo tipo de producto

SELECT tabla1.ordernumber, 
       tabla1.productline, 
       ( o.shippeddate - o.orderdate ) diferenciadias 
FROM   orders o 
       JOIN (SELECT od.ordernumber ordernumber, 
                    od.productcode productcode, 
                    p.productline  productline 
             FROM   orderdetails od 
                    JOIN products p 
                      ON od.productcode = p.productcode) AS tabla1 
         ON o.ordernumber = tabla1.ordernumber 
WHERE  o.shippeddate IS NOT NULL 
GROUP  BY tabla1.ordernumber, 
          tabla1.productline, 
          diferenciadias 


		
		--por ej, para ordernumber=10103 se han solicitado varios productos tipo vintage cars,
		--classic cars y trucks and buses y queremos mostrar solo una vez x cada tipo
				
		SELECT tabla1.ordernumber, 
			tabla1.productline, 
			( o.shippeddate - o.orderdate ) diferenciadias 
		FROM   orders o 
			JOIN (SELECT od.ordernumber ordernumber, 
							od.productcode productcode, 
							p.productline  productline 
					FROM   orderdetails od 
							JOIN products p 
							ON od.productcode = p.productcode) AS tabla1 
				ON o.ordernumber = tabla1.ordernumber 
		WHERE  o.shippeddate IS NOT NULL 
			AND tabla1.ordernumber = 10103 
		GROUP  BY tabla1.ordernumber, 
				tabla1.productline, 
				diferenciadias 




--Ahora agrupamos por productline, eso quiere decir que no necesitamos ni ordernumber ni productcode.
--Y hacemos el average entre la diferencia de días con 2 decimales.

SELECT tabla2.productline, 
       Round(Avg(tabla2.diferenciadias), 2) tiempomedio 
FROM   (SELECT tabla1.ordernumber, 
               tabla1.productline, 
               ( o.shippeddate - o.orderdate ) diferenciadias 
        FROM   orders o 
               JOIN (SELECT od.ordernumber ordernumber, 
                            od.productcode productcode, 
                            p.productline  productline 
                     FROM   orderdetails od 
                            JOIN products p 
                              ON od.productcode = p.productcode) AS tabla1 
                 ON o.ordernumber = tabla1.ordernumber 
        WHERE  o.shippeddate IS NOT NULL 
        GROUP  BY tabla1.ordernumber, 
                  tabla1.productline, 
                  diferenciadias) AS tabla2 
GROUP  BY tabla2.productline 

*/