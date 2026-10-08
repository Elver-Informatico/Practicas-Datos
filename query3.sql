SELECT e3.employeenumber,
      e3.lastname
FROM   employees e1
      JOIN employees e2
        ON e2.reportsto = e1.employeenumber
      JOIN employees e3
        ON e3.reportsto = e2.employeenumber
WHERE  e1.reportsto IS NULL;
