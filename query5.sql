/*
--Clientes que han realizado un PEDIDO en el año 2003.
--(Utilizamos distinct para eliminar las repeticiones)

select distinct o.customernumber 
from   orders o 
where  o.orderdate >= '2003-01-01' 
       and o.shippeddate <= '2003-12-31' 
       and o.shippeddate IS NOT NULL 


--Clientes que han realizado un PAGO en el año 2003.

select distinct pt.customernumber 
from   payments pt 
where  pt.paymentdate >= '2003-01-01' 
       and pt.paymentdate <= '2003-12-31' 


--Unión de los clientes que han realizado un pedido
--con los que han pagado en 2003.

(select distinct o.customernumber 
 from   orders o 
 where  o.orderdate >= '2003-01-01' 
        and o.shippeddate <= '2003-12-31' 
        and o.shippeddate IS NOT NULL) 
union 
(select distinct pt.customernumber 
 from   payments pt 
 where  pt.paymentdate >= '2003-01-01' 
        and pt.paymentdate <= '2003-12-31') 


--Hacemos join con customer para obtener 
--el id del empleado que vende al cliente.

select c.customernumber, 
       c.salesrepemployeenumber 
from   customers c 
       join ((select distinct o.customernumber 
              from   orders o 
              where  o.orderdate >= '2003-01-01' 
                     and o.shippeddate <= '2003-12-31' 
                     and o.shippeddate IS NOT NULL) 
             union 
             (select distinct pt.customernumber 
              from   payments pt 
              where  pt.paymentdate >= '2003-01-01' 
                     and pt.paymentdate <= '2003-12-31'))as tabla1 
         on c.customernumber = tabla1.customernumber 
		

--A continuación, hacemos join con employee para 
--saber la oficina en la que trabaja cada uno de los empleados.

select c.customernumber, 
       c.salesrepemployeenumber, 
       e.officecode 
from   customers c 
       join ((select distinct o.customernumber 
              from   orders o 
              where  o.orderdate >= '2003-01-01' 
                     and o.shippeddate <= '2003-12-31' 
                     and o.shippeddate IS NOT NULL) 
             union 
             (select distinct pt.customernumber 
              from   payments pt 
              where  pt.paymentdate >= '2003-01-01' 
                     and pt.paymentdate <= '2003-12-31'))as tabla1 
         on c.customernumber = tabla1.customernumber 
       join employees e 
         on e.employeenumber = c.salesrepemployeenumber 


--Hacemos join con offices para saber el país de cada una de las oficinas y mostramos  
--officecode y country. El siguiente paso es agrupar por country y officecode 
--para eliminar repeticiones.

select e.officecode, 
       ofc.country 
from   customers c 
       join ((select distinct o.customernumber 
              from   orders o 
              where  o.orderdate >= '2003-01-01' 
                     and o.shippeddate <= '2003-12-31' 
                     and o.shippeddate IS NOT NULL) 
             union 
             (select distinct pt.customernumber 
              from   payments pt 
              where  pt.paymentdate >= '2003-01-01' 
                     and pt.paymentdate <= '2003-12-31'))as tabla1 
         on c.customernumber = tabla1.customernumber 
       join employees e 
         on e.employeenumber = c.salesrepemployeenumber 
       join offices ofc 
         on ofc.officecode = e.officecode 
group  by e.officecode, 
          ofc.country 


--Obtenemos las que NO HAN COMPRADO...
--(en las anteriores consultas hemos conseguido 
--las oficinas que han recibido algún pedido o realizado algún pago).

(select o.officecode, 
        o.country 
 from   offices o) 
except 
(select e.officecode, 
        ofc.country 
 from   customers c 
        join ((select distinct o.customernumber 
               from   orders o 
               where  o.orderdate >= '2003-01-01' 
                      and o.shippeddate <= '2003-12-31' 
                      and o.shippeddate IS NOT NULL) 
              union 
              (select distinct pt.customernumber 
               from   payments pt 
               where  pt.paymentdate >= '2003-01-01' 
                      and pt.paymentdate <= '2003-12-31'))as tabla1 
          on c.customernumber = tabla1.customernumber 
        join employees e 
          on e.employeenumber = c.salesrepemployeenumber 
        join offices ofc 
          on ofc.officecode = e.officecode 
 group  by e.officecode, 
           ofc.country) 



*/
--Agrupamos las oficinas por país, contamos el número de oficinas
--y ordenamos de mayor a menor.

select tabla2.country country, 
       Count(*)       numoffices 
from   ((select o.officecode, 
                o.country 
         from   offices o) 
        except 
        (select e.officecode, 
                ofc.country 
         from   customers c 
                join ((select distinct o.customernumber 
                       from   orders o 
                       where  o.orderdate >= '2003-01-01' 
                              and o.shippeddate <= '2003-12-31' 
                              and o.shippeddate IS NOT NULL) 
                      union 
                      (select distinct pt.customernumber 
                       from   payments pt 
                       where  pt.paymentdate >= '2003-01-01' 
                              and pt.paymentdate <= '2003-12-31'))as tabla1 
                  on c.customernumber = tabla1.customernumber 
                join employees e 
                  on e.employeenumber = c.salesrepemployeenumber 
                join offices ofc 
                  on ofc.officecode = e.officecode 
         group  by e.officecode, 
                   ofc.country)) as tabla2 
group  by tabla2.country 
order  by numoffices desc
