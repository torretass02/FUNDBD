select t.productline, Avg(o.shippeddate - o.orderdate) tiempo_medio 
from orders o 
  join (select ord.ordernumber, ord.productcode, p.productline 
    from   orderdetails ord 
      join products p 
        on ord.productcode = p.productcode) as t 
    on o.ordernumber = t.ordernumber 
where o.shippeddate is not null 
group by t.productline 