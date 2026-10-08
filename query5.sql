SELECT o.country, COUNT(*) AS oficinas_sin_ventas
      FROM   offices o
WHERE NOT EXISTS (SELECT DISTINCT e.officecode
                           FROM   employees e
                                  JOIN customers c
                                    ON c.salesrepemployeenumber =
                                       e.employeenumber
                                  JOIN orders os
                                    ON c.customernumber = os.customernumber
                           WHERE  os.orderdate BETWEEN
                                  '2003-01-01' AND '2003-12-31')
GROUP  BY o.country
ORDER  BY oficinas_sin_ventas DESC;
