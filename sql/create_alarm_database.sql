CREATE TABLE component_type (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	type_name TEXT
);

CREATE TABLE component (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	type_id INTEGER, 
	location TEXT,
	serialnumber TEXT,	
	FOREIGN KEY (type_id) REFERENCES component_type (id)
);

CREATE TABLE user (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	pin TEXT,
	rfid TEXT,
	passphrase TEXT
);

CREATE TABLE customer (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	name TEXT,
	address TEXT
);


CREATE TABLE user_customer ( 
	customer_id INTEGER,
	user_id INTEGER,
	FOREIGN KEY (customer_id) REFERENCES customer (id),
	FOREIGN KEY (user_id) REFERENCES user (id),
	PRIMARY KEY (customer_id, user_id)
);

CREATE TABLE component_customer ( 
	customer_id INTEGER,
	component_id INTEGER,
	FOREIGN KEY (customer_id) REFERENCES customer (id),
	FOREIGN KEY (component_id) REFERENCES component (id),
	PRIMARY KEY (customer_id, component_id)
);



PRAGMA foreign_keys;

SELECT * FROM component_type;
SELECT * FROM component;
SELECT * FROM user;
SELECT * FROM customer;
SELECT * FROM user_customer;
SELECT * FROM component_customer;
