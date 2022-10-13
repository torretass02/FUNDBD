/* Lo primero que hicimos fue obtener el productcode del producto con el nombre 
'1940 Ford Pickup Truck'. Con esa información se hace un join con 'orderdetails' para
obtener los ordernumber con el productcode mencionado anteriormente. 

Una vez hecho esto, prodecemos con otro join con la tabla 'orders' para obtener el
costumernumber de los clientes que compraron ese producto.
Como además del costumernumber debemos aportar el nombre de cada cliente, hacemos un
join con la tabla 'costumers' para obtener el costumername gracias al costumernumber.

Teniendo toda esta información, y faltando solo la cantidad abonada por cada cliente,
procedemos a hacer un join de toda la tabla anterior a la tabla 'payments', para saber
la cantidad pagada por cada cliente. 

Una vez reunida toda la información, solo queda agruparla. En este caso el prodecimiento
más rápido es agrupar las filas de la tabla por clientes y sumar la cantidad de todos
sus pedidos, ordenándo los clientes por cantidad pagada en orden descendente, 
obteniendo el resultado de la consulta número 1. 
*/
SELECT t.customernumber,
       t.customername,
       Sum(pay.amount) amount
FROM   payments pay
       JOIN (SELECT DISTINCT o.customernumber,
                             c.customername
             FROM   products p
                    JOIN orderdetails ord
                      ON p.productcode = ord.productcode
                    JOIN orders o
                      ON o.ordernumber = ord.ordernumber
                    JOIN customers c
                      ON c.customernumber = o.customernumber
             WHERE  p.productname = '1940 Ford Pickup Truck') AS t
         ON pay.customernumber = t.customernumber
GROUP  BY t.customernumber,
          t.customername
ORDER  BY amount DESC 