select t.customernumber, t.customername, Sum(pay.amount) amount 
from payments pay 
  join (select distinct o.customernumber, c.customername
    from products p 
      join orderdetails ord 
        on p.productcode = ord.productcode 
      join orders o 
        on o.ordernumber = ord.ordernumber 
      join customers c 
        on c.customernumber = o.customernumber 
    where p.productname = '1940 Ford Pickup Truck') as t
    on pay.customernumber = t.customernumber 
group by t.customernumber, 
          t.customername 
order by amount desc 