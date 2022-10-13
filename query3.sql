
select e.employeenumber, e.lastname 
from employees e 
  join (select e.employeenumber, e.lastname 
    from employees e 
    where e.reportsto = (select e.employeenumber 
      from   employees e 
      where  e.reportsto IS null)) as t 
    on e.reportsto = t.employeenumber 