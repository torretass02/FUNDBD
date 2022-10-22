/*

Empezamos viendo los clientes que han hecho un pedido en 2003, unimos esos datos con la gente
que ha pagado en 2003. Después de esto necesitamos hacer un Join con cliente para conseguir que
agente ha ayudado con la compra, así saber el id del empleado y poder en el próximo paso unirlo 
con Employee para ver la sucursal en la que están.

Después del join ya podemos ver en que sucursal se hizo la compra. Hacemos join con offices para
saber el país de cada una de las oficinas, el siguiente paso es agrupar por country y officecode 
para eliminar repeticiones y poder sacar los datos en limpio. 

Aquí ya tenemos todos los datos que necesitamos porque ya sabemos que países han vendido y que países 
no han vendido. Ordenamos la tabla de forma descendiente y mostramos la solución.

*/
SELECT taux.country country,
       Count(*)numoffices
FROM   ((SELECT o.officecode,
                o.country
         FROM   offices o)
        EXCEPT
        (SELECT e.officecode,
                of.country
         FROM   customers c
                JOIN ((SELECT DISTINCT o.customernumber
                       FROM   orders o
                       WHERE  o.orderdate >= '2003-01-01'
                              AND o.shippeddate <= '2003-12-31'
                              AND o.shippeddate IS NOT NULL)
                      UNION
                      (SELECT DISTINCT pay.customernumber
                       FROM   payments pay
                       WHERE  pay.paymentdate >= '2003-01-01'
                              AND pay.paymentdate <= '2003-12-31'))AS t
                  ON c.customernumber = t.customernumber
                JOIN employees e
                  ON e.employeenumber = c.salesrepemployeenumber
                JOIN offices of
                  ON of.officecode = e.officecode
         GROUP  BY e.officecode,
                   of.country)) AS taux
GROUP  BY taux.country
ORDER  BY numoffices DESC 