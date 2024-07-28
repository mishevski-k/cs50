create table if not exists portfolios (
    id integer primary key autoincrement not null,
    user_id integer not null references users(id),
    symbol text not null,
    shares integer
);

create table if not exists transactions (
    id integer primary key autoincrement not null,
    user_id integer not null references users(id),
    symbol text not null,
    transaction_type text not null,
    shares integer not null,
    price float not null,
    timestamp datetime not null
);