DROP TABLE IF EXISTS users;

-- TODO fix varchar lengths
create table users (
    id int NOT NULL PRIMARY KEY,
    username varchar (50) NOT NULL,
    uuid varchar (50) NOT NULL
--     possible profile image url (to fetch from the internet)
);
