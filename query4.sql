/*

Debemos identificar la oficina que más productos haya vendido. Por ello, empezamos
recopilando el numero de productos vendidos en cada pedido, mediante la tabla
'orderdetails'. Para poder unir el resto de tablas y llegar a la oficina que deseamos,
debemos hacer varios joins. 

El primero de todos será con la tabla 'orders', para obtener el costumernumber de los
clientes de todos los pedidos realizados. Posteriormente para compactar mejor nuestros
datos, los agrupamos por cliente, sumando la cantidad total de productos adquiridos
por cada uno. 

El siguiente join se hará con la tabla 'employees', para obtener el employeenumber
del empleado que atiende a cada cliente. Teniendo toda esta información, agrupamos
todos nuestros datos por empleado, sumando el total de productos vendidos por cada uno.

El último join lo hacemos con la tabla anteriormente creada, y la tabla 'offices', para
que, por medio del officecode, podamos obtener el número de productos total por cada
oficina. Por ello, ordenamos el número de ventas de mayor a menor, y nos quedamos solo
con la primera oficina, obteniendo la oficina con el mayor número de ventas.

*/
SELECT e.officecode,
       Sum(taux.total) total_products
FROM   employees e
       JOIN (SELECT c.salesrepemployeenumber e_num,
                    Sum(t.total)     total
             FROM   customers c
                    JOIN (SELECT o.customernumber,
                                 Sum(ord.quantityordered) total
                          FROM   orders o
                                 JOIN orderdetails ord
                                   ON ord.ordernumber = o.ordernumber
                          GROUP  BY customernumber
                          ORDER  BY total DESC) AS t
                      ON c.customernumber = t.customernumber
             GROUP  BY e_num
             ORDER  BY total DESC) AS taux
         ON e.employeenumber = taux.e_num
GROUP  BY e.officecode
ORDER  BY total_products DESC
LIMIT  1 