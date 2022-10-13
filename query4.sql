select e.officecode, Sum(tabla2.quantity) quantity 
from employees e 
  join (select c.salesrepemployeenumber employeeid, Sum(tabla1.quantity) quantity 
    from customers c 
      join (select o.customernumber customernumber, Sum(od.quantityordered) quantity 
        from   orders o 
          join orderdetails od 
            on od.ordernumber = o.ordernumber 
        group by customernumber 
        order by quantity desc) as tabla1 
        on c.customernumber = tabla1.customernumber 
    group by employeeid 
    order by quantity desc) as tabla2 
    on e.employeenumber = tabla2.employeeid 
group by e.officecode 
order by quantity desc 
limit  1 