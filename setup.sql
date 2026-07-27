CREATE TABLE ProduceDeliveries (
    FarmerNumber INTEGER PRIMARY KEY,
    FarmerName TEXT NOT NULL,
    SubCounty TEXT,
    ProduceType TEXT NOT NULL,
    QuantityDelivered INTEGER NOT NULL,
    PricePerUnit REAL NOT NULL,
    DeliveryDate TEXT,
    PaymentStatus TEXT NOT NULL,
    NetPayment REAL
);

INSERT INTO ProduceDeliveries
(FarmerNumber, FarmerName, SubCounty, ProduceType,
 QuantityDelivered, PricePerUnit, DeliveryDate, PaymentStatus)
VALUES
(101, 'Mwangi Kamau', 'Kieni', 'Milk', 120, 55, '2026-07-22', 'Pending'),
(102, 'Wanjiku Njeri', 'Mathira', 'Coffee', 85, 120, '2026-07-22', 'Paid'),
(103, 'Peter Maina', 'Tetu', 'Potatoes', 300, 40, '2026-07-22', 'Pending'),
(104, 'Akinyi Otieno', 'Mukurweini', 'Maize', 250, 65, '2026-07-22', 'Pending'),
(105, 'Mutiso Musyoka', 'Othaya', 'Milk', 150, 55, '2026-07-22', 'Paid'),
(106, 'Chebet Kiptoo', 'Nyeri Town', 'Vegetables', 95, 80, '2026-07-22', 'Pending');