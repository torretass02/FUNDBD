/*

Estamos buscando los pedidos que se han realizado en 2003. Para ahi sacar la oficina que no ha vendido nada.
Empezamos buscando que clientes han hecho un pedido y un pago. Los unimos para ver con que datos
estamos trabajando. A partir de ahi hacemos un join con employee para ver el id del empleado
que ha vendido esos productos al cliente, con esa informacion de los empleados podemos sacar la oficina desde la que han vendido.

Ahora tenemos que encontrar los paises donde se han hecho las menores ventas para poder definir el pais que no ha vendido nada
*/
SELECT tabla2.country country,
       Count(*)numoffices
FROM   ((SELECT o.officecode,
                o.country
         FROM   offices o)
        EXCEPT
        (SELECT e.officecode,
                ofc.country
         FROM   customers cx
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