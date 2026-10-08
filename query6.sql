WITH productoscomprados AS
(
       SELECT *
       FROM   orders natural
       JOIN   orderdetails natural
       JOIN   products), paresdeproductos(codigouno, codigodos) AS
(
       SELECT p1.productcode,
              p2.productcode
       FROM   productoscomprados p1
       JOIN   productoscomprados p2
       ON     p1.ordernumber = p2.ordernumber
       WHERE  p1.productcode != p2.productcode), paresdeproductosfiltrados(codigouno, codigodos, count) AS
(
                SELECT DISTINCT *,
                                Count(*)
                FROM            paresdeproductos
                GROUP BY        codigouno,
                                codigodos
                HAVING          Count(*) > 1), paresfiltradisimos(codigouno, codigodos, count) AS
(
                SELECT DISTINCT Least(codigouno, codigodos),
                                Greatest(codigouno, codigodos),
						count
                FROM            paresdeproductosfiltrados)
select *
FROM   paresfiltradisimos;
