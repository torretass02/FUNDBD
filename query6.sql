/*

Se pide un listado de todas las parejas de productos que aparezcan en más de un 
carro de la compra, por lo que lo primero que deberemos hacer será obtener esas parejas.
La forma de obtenerlas es hacer un join de 'orderdetails' con la misma tabla
'orderdetails', agrupándolos por el número de pedido, pero siendo por supuesto
productos distintos, y sumando la cantidad de "carros" en los que aparecen juntos 
ambos productos, cantidad ordenada de menor a mayor. 

La línea HAVING Count(*) > 1 la ponemos por la premisa dada en el enunciado de que
cada pareja de productos debe estar en MÁS de un carro cada una.

El último paso (el que más nos costó) fue eliminar las parejas que estaban repetidas,
ya que el orden de las parejas no se estaba teniendo en cuenta. Decidimos entonces hacer
que el primer producto de cada pareja tuviese que tener obligatoriamente un productcode
mayor que el otro producto, de forma que eliminasemos la otra variante de cada pareja.

*/
SELECT ord_1.productcode code_1,
       ord_2.productcode code_2,
       Count(*)        numcarros
FROM   orderdetails ord_1
       JOIN orderdetails ord_2
         ON ord_1.ordernumber = ord_2.ordernumber
WHERE  ord_1.productcode <> ord_2.productcode
       AND ord_1.productcode > ord_2.productcode
GROUP  BY code_1,
          code_2
HAVING Count(*) > 1
ORDER  BY numcarros ASC 