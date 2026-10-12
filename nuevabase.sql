CREATE TABLE public.speaksTo (
	employeenumber integer NOT NULL,
	customernumber integer NOT NULL
);

CREATE TABLE public.workHistory (
	employeenumber integer NOT NULL,
	officecode character varying(10) NOT NULL,
	dateofentry DATE NOT NULL
);

CREATE TABLE public.customers (
    customernumber integer NOT NULL,
    customername character varying(50) NOT NULL,
    contactlastname character varying(50) NOT NULL,
    contactfirstname character varying(50) NOT NULL,
    phone character varying(50) NOT NULL,
    addressline1 character varying(50) NOT NULL,
    addressline2 character varying(50) DEFAULT NULL::character varying,
    city character varying(50) NOT NULL,
    state character varying(50) DEFAULT NULL::character varying,
    postalcode character varying(15) DEFAULT NULL::character varying,
    country character varying(50) NOT NULL,
    creditlimit numeric(10,2) DEFAULT NULL::numeric
);


CREATE TABLE public.employees (
    employeenumber integer NOT NULL,
    lastname character varying(50) NOT NULL,
    firstname character varying(50) NOT NULL,
    extension character varying(10) NOT NULL,
    email character varying(100) NOT NULL,
    reportsto integer,
    jobtitle character varying(50) NOT NULL
);

CREATE TABLE public.offices (
    officecode character varying(10) NOT NULL,
    city character varying(50) NOT NULL,
    phone character varying(50) NOT NULL,
    addressline1 character varying(50) NOT NULL,
    addressline2 character varying(50) DEFAULT NULL::character varying,
    state character varying(50) DEFAULT NULL::character varying,
    country character varying(50) NOT NULL,
    postalcode character varying(15) NOT NULL,
    territory character varying(10) NOT NULL
);

CREATE TABLE public.orderdetails (
    ordernumber integer NOT NULL,
    productcode character varying(15) NOT NULL,
    quantityordered integer NOT NULL,
    priceeach numeric(10,2) NOT NULL,
    orderlinenumber smallint NOT NULL
);

CREATE TABLE public.orders (
    ordernumber integer NOT NULL,
    orderdate date NOT NULL,
    requireddate date NOT NULL,
    shippeddate date,
    status character varying(15) NOT NULL,
    comments text,
    customernumber integer NOT NULL
);

CREATE TABLE public.payments (
    ordernumber integer NOT NULL,
    customernumber integer NOT NULL,
    checknumber character varying(50) NOT NULL,
    paymentdate date NOT NULL,
    amount numeric(10,2) NOT NULL
);


CREATE TABLE public.productlines (
    productline character varying(50) NOT NULL,
    textdescription character varying(4000) DEFAULT NULL::character varying,
    htmldescription character varying(4000),
    image character varying
);


CREATE TABLE public.products (
    productcode character varying(15) NOT NULL,
    productname character varying(70) NOT NULL,
    productline character varying(50) NOT NULL,
    productscale character varying(10) NOT NULL,
    productvendor character varying(50) NOT NULL,
    productdescription text NOT NULL,
    quantityinstock smallint NOT NULL,
    buyprice numeric(10,2) NOT NULL,
    msrp numeric(10,2) NOT NULL
);

ALTER TABLE ONLY public.speaksTo
    ADD CONSTRAINT speaksTo_pkey PRIMARY KEY (employeenumber, customernumber);

ALTER TABLE ONLY public.workHistory
    ADD CONSTRAINT workHistory_pkey PRIMARY KEY (employeenumber, officecode);

ALTER TABLE ONLY public.customers
    ADD CONSTRAINT customers_pkey PRIMARY KEY (customernumber);


--
-- Name: employees employees_pkey; Type: CONSTRAINT; Schema: public; Owner: alumnodb
--

ALTER TABLE ONLY public.employees
    ADD CONSTRAINT employees_pkey PRIMARY KEY (employeenumber);


--
-- Name: offices offices_pkey; Type: CONSTRAINT; Schema: public; Owner: alumnodb
--

ALTER TABLE ONLY public.offices
    ADD CONSTRAINT offices_pkey PRIMARY KEY (officecode);


--
-- Name: orderdetails orderdetails_pkey; Type: CONSTRAINT; Schema: public; Owner: alumnodb
--

ALTER TABLE ONLY public.orderdetails
    ADD CONSTRAINT orderdetails_pkey PRIMARY KEY (ordernumber, productcode);


--
-- Name: orders orders_pkey; Type: CONSTRAINT; Schema: public; Owner: alumnodb
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_pkey PRIMARY KEY (ordernumber);


--
-- Name: payments payments_pkey; Type: CONSTRAINT; Schema: public; Owner: alumnodb
--

ALTER TABLE ONLY public.payments
    ADD CONSTRAINT payments_pkey PRIMARY KEY (ordernumber, customernumber, checknumber);


--
-- Name: productlines productlines_pkey; Type: CONSTRAINT; Schema: public; Owner: alumnodb
--

ALTER TABLE ONLY public.productlines
    ADD CONSTRAINT productlines_pkey PRIMARY KEY (productline);


--
-- Name: products products_pkey; Type: CONSTRAINT; Schema: public; Owner: alumnodb
--

ALTER TABLE ONLY public.products
    ADD CONSTRAINT products_pkey PRIMARY KEY (productcode);


--
-- Name: employees employees_ibfk_1; Type: FK CONSTRAINT; Schema: public; Owner: alumnodb
--

ALTER TABLE ONLY public.employees
    ADD CONSTRAINT employees_ibfk_1 FOREIGN KEY (reportsto) REFERENCES public.employees(employeenumber);


--
-- Name: employees employees_ibfk_2; Type: FK CONSTRAINT; Schema: public; Owner: alumnodb
--

--
-- Name: orderdetails orderdetails_ibfk_1; Type: FK CONSTRAINT; Schema: public; Owner: alumnodb
--

ALTER TABLE ONLY public.orderdetails
    ADD CONSTRAINT orderdetails_ibfk_1 FOREIGN KEY (ordernumber) REFERENCES public.orders(ordernumber);


--
-- Name: orderdetails orderdetails_ibfk_2; Type: FK CONSTRAINT; Schema: public; Owner: alumnodb
--

ALTER TABLE ONLY public.orderdetails
    ADD CONSTRAINT orderdetails_ibfk_2 FOREIGN KEY (productcode) REFERENCES public.products(productcode);


--
-- Name: orders orders_ibfk_1; Type: FK CONSTRAINT; Schema: public; Owner: alumnodb
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_ibfk_1 FOREIGN KEY (customernumber) REFERENCES public.customers(customernumber);


--
-- Name: payments payments_ibfk_1; Type: FK CONSTRAINT; Schema: public; Owner: alumnodb
--

ALTER TABLE ONLY public.payments
    ADD CONSTRAINT payments_ibfk_1 FOREIGN KEY (customernumber) REFERENCES public.customers(customernumber);


--
-- Name: products products_ibfk_1; Type: FK CONSTRAINT; Schema: public; Owner: alumnodb
--

ALTER TABLE ONLY public.products
    ADD CONSTRAINT products_ibfk_1 FOREIGN KEY (productline) REFERENCES public.productlines(productline);

ALTER TABLE ONLY public.speaksTo
    ADD CONSTRAINT fk1 FOREIGN KEY (employeenumber) REFERENCES public.employees(employeenumber);

ALTER TABLE ONLY public.speaksTo
    ADD CONSTRAINT fk2 FOREIGN KEY (customernumber) REFERENCES public.customers(customernumber);


ALTER TABLE ONLY public.workHistory
    ADD CONSTRAINT fk1 FOREIGN KEY (employeenumber) REFERENCES public.employees(employeenumber);

ALTER TABLE ONLY public.workHistory
    ADD CONSTRAINT fk2 FOREIGN KEY (officecode) REFERENCES public.offices(officecode);
