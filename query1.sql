SELECT c.customernumber,
      c.customername,
      Sum(p.amount)
FROM   customers c
      JOIN payments p
        ON c.customernumber = p.customernumber
WHERE  c.customernumber IN (SELECT o.customernumber
                           FROM   orders o
                                  JOIN orderdetails od
                                    ON o.ordernumber = od.ordernumber
                                  JOIN products p
                                    ON od.productcode = p.productcode
                           WHERE  p.productname = '1940 Ford Pickup Truck')
GROUP  BY c.customernumber,
         c.customername
ORDER  BY Sum(p.amount) DESC;
