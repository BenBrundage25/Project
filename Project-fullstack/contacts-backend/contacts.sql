-- contacts.sql

CREATE TABLE IF NOT EXISTS contacts (
    id SERIAL PRIMARY KEY,
    f_name TEXT NOT NULL,
    l_name TEXT NOT NULL,
    phone BIGINT NOT NULL UNIQUE,
    address TEXT,
    email TEXT
);
