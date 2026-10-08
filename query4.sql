SELECT o1.officecode,
       Sum(o2.quantityordered)
FROM   orderdetails o2
       NATURAL JOIN orders o3
       NATURAL JOIN customers c1
       JOIN (employees e1
             NATURAL JOIN offices o1)
         ON c1.salesrepemployeenumber = e1.employeenumber
WHERE  o3.status LIKE 'Shipped'
        OR o3.status LIKE 'Resolved'
GROUP  BY o1.officecode
ORDER  BY Sum(o2.quantityordered) DESC
LIMIT  1; 
