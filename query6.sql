/*
--Join de orderdetails con orderdetails con el fin de obtener 
--las parejas de productos. Ordenamos por número de 
--carros de la compra en los que sale la pareja...
--PERO SE REPITEN LAS PAREJAS!! (id1,id2)-(id2,id1).

select od1.productcode id1, 
       od2.productcode id2, 
       Count(*)        numcarros 
from   orderdetails od1 
       join orderdetails od2 
         on od1.ordernumber = od2.ordernumber 
where  od1.productcode <> od2.productcode --no es pareja, por ej: (abc,abc)  
group  by id1, 
          id2 
order  by numcarros desc 


--El enunciado nos pide que mostremos aquellas parejas que aparezcan 
--en más de un carro, eso quiere decir que añadimos 
--la condición having numcarros>1.

select od1.productcode id1, 
       od2.productcode id2, 
       Count(*)        numcarros 
from   orderdetails od1 
       join orderdetails od2 
         on od1.ordernumber = od2.ordernumber 
where  od1.productcode <> od2.productcode 
group  by id1, 
          id2 
having Count(*) > 1   
order  by numcarros desc 


--Ahora eliminamos las parejas que están repetidas con 
--la siguiente condición: (od1.productcode<od2.productcode).
--Por ej: ¿¿¿(S(5)0_1341,S(7)00_1691)----(S700_1691,S50_1341)??? 
--compara por cadena ¿S5<S7?=TRUE ¿S7<S5?=FALSE
--Finalmente se quedará con (S50_1341,S700_1691) como ocurre en la ejecución.
*/
select od1.productcode id1, 
       od2.productcode id2, 
       Count(*)        numcarros 
from   orderdetails od1 
       join orderdetails od2 
         on od1.ordernumber = od2.ordernumber 
where  od1.productcode <> od2.productcode 
       and od1.productcode < od2.productcode 
group  by id1, 
          id2 
having Count(*) > 1   
order  by numcarros desc 