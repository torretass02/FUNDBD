/*

Queremos calcular el tiempo medio entre que se pide y se envia el pedido. Seleccionamos la tabla 
de productline y en el propio select hacemos la operacion de los orders (la resta del dia en el 
que se envia y el dia en el que se hace el pedido), llamando a este valor 'tiempo_medio'. 

Luego necesitamos hacer un join entre las tablas de orderdetails y poduct por la PK que es productcode.
Esto lo hacemos y creamos la nueva tabla 't' que proximamente unimos, con otro join, con la tabla orders
por la PK ordernumber para ya tener todos los datos que necesitamos. 

Por ultimo hacemos un 'control de errores' para que no salgan las fechas de envio que son NULL, 
para no incluir los pedidos que no han sido entregados, y los agrupamos por productline.

Con todo esto tenemos la solucion de la query2 para que decuelva los tiempos medios entre pedido y envío organizado
por el tipo de producto que es.

*/

SELECT t.productline,
       Avg(o.shippeddate - o.orderdate) tiempo_medio
FROM   orders o
       JOIN (SELECT ord.ordernumber,
                    ord.productcode,
                    p.productline
             FROM   orderdetails ord
                    JOIN products p
                      ON ord.productcode = p.productcode) AS t
         ON o.ordernumber = t.ordernumber
WHERE  o.shippeddate IS NOT NULL
GROUP  BY t.productline 
