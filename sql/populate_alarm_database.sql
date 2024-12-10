INSERT INTO component_type (type_name)
VALUES 
	('Movement Sensor'),
	('Magnetic Alarm Sensor'),
	('Pin Keypad');

INSERT INTO component  (type_id, location, serialnumber)
VALUES
	(1, 'Wuthering Heights', 'UK1234567890'),
	(2, 'Thrushcross Grange 2', 'UK1234566666');

INSERT INTO customer (name, address)
VALUES
	('Jane Eyre', 'Thrushcross Grange')
	('Jospeh Conrad', 'Congo River Upper Station');


INSERT INTO user (pin, rfid, passphrase)
VALUES
	('1234', '55555', 'Naming Nuts')
	('1234', '66666', 'The Horror');


INSERT INTO user_customer (user_id, customer_id)
VALUES
	(1, 1)
	(2, 2);

INSERT INTO component_customer (customer_id, component_id)
VALUES
	(1, 1),
	(1, 2);


PRAGMA foreign_keys;

SELECT * FROM component_type;
SELECT * FROM component;
SELECT * FROM user;
SELECT * FROM customer;
SELECT * FROM user_customer;
SELECT * FROM component_customer;
