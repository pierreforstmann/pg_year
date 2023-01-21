--
-- test.sql
--
create extension pg_year;
--
create table t(c year);
--
insert into t values(1900);
insert into t values(2156);
insert into t values(1901);
insert into t values(2000);
insert into t values(2155);
delete from t where c = 1901 or c = 2155;
select c + 1 from t;
select c - 1 from t;
select from t  where c = 2000;
select from t  where c > 2000; 
select from t  where c >= 2000; 
select from t  where c < 2000;
select from t  where c <= 2000; 
select from t  where c <> 2000; 
--
create index b on t(c);
create index h on t using hash (c);
