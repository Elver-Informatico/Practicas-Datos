SELECT productline,
       Avg(shippeddate - orderdate)
FROM   orders
       natural JOIN orderdetails
       natural JOIN products
GROUP  BY productline; 
