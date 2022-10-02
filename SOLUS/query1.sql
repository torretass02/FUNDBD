
/*
--Obtenemos el id de “1940 Ford Pickup Truck”

SELECT p.productcode 
FROM   products p 
WHERE  p.productname = '1940 Ford Pickup Truck' 



--Join con orderdetails para obtener los ordernumber que contengan a S18_1097

SELECT od.ordernumber ordernumber, 
       p.productcode  productcode 
FROM   products p 
       JOIN orderdetails od 
         ON p.productcode = od.productcode 
WHERE  p.productname = '1940 Ford Pickup Truck' 



--Hacemos un join con orders para obtener los identificadores 
--de los cliente que realizan el pedido de “1940 Ford Pickup Truck”.
--Cliente aparece una sola vez (utilizamos 'distinct').

SELECT DISTINCT o.customernumber customernumber 
FROM   products p 
       JOIN orderdetails od 
         ON p.productcode = od.productcode 
       JOIN orders o 
         ON o.ordernumber = od.ordernumber 
WHERE  p.productname = '1940 Ford Pickup Truck' 




--Join con customers para obtener los nombres de los clientes.

SELECT DISTINCT o.customernumber customernumber, 
                c.customername   customername 
FROM   products p 
       JOIN orderdetails od 
         ON p.productcode = od.productcode 
       JOIN orders o 
         ON o.ordernumber = od.ordernumber 
       JOIN customers c 
         ON c.customernumber = o.customernumber 
WHERE  p.productname = '1940 Ford Pickup Truck' 




--Unimos la tabla de la consulta anterior con payments 
--para saber los pagos que hace cada cliente. 

SELECT tabla1.customernumber, 
       tabla1.customername, 
       pt.amount 
FROM   payments pt 
       JOIN (SELECT DISTINCT o.customernumber customernumber, 
                             c.customername   customername 
             FROM   products p 
                    JOIN orderdetails od 
                      ON p.productcode = od.productcode 
                    JOIN orders o 
                      ON o.ordernumber = od.ordernumber 
                    JOIN customers c 
                      ON c.customernumber = o.customernumber 
             WHERE  p.productname = '1940 Ford Pickup Truck') AS tabla1 
         ON pt.customernumber = tabla1.customernumber 
		 


*/

--Por último, agrupamos por cliente y hacemos suma del dinero total abonado por cada cliente

SELECT tabla1.customernumber, 
       tabla1.customername, 
       Sum(pt.amount) amount 
FROM   payments pt 
       JOIN (SELECT DISTINCT o.customernumber customernumber, 
                             c.customername   customername 
             FROM   products p 
                    JOIN orderdetails od 
                      ON p.productcode = od.productcode 
                    JOIN orders o 
                      ON o.ordernumber = od.ordernumber 
                    JOIN customers c 
                      ON c.customernumber = o.customernumber 
             WHERE  p.productname = '1940 Ford Pickup Truck') AS tabla1 
         ON pt.customernumber = tabla1.customernumber 
GROUP  BY tabla1.customernumber, 
          tabla1.customername 
ORDER  BY amount DESC 