select productcode, productname 
from products 
where productname like ? 
order by productcode asc 