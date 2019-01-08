create database SchoolMap;
use SchoolMap;
create table MapPath(
	origin varchar(50) not null,
    destination varchar(50) not null,
    length double not null,
    primary key(origin, destination)
);

insert into MapPath values('学23', '西南门', 5);
insert into MapPath values('西南门', '学23', 5);

insert into MapPath values('西南门', '新西门', 10);
insert into MapPath values('新西门', '西南门', 10);

insert into MapPath values('十一教', '新西门', 30);
insert into MapPath values('新西门', '十一教', 30);

insert into MapPath values('西南门', '十教', 20);
insert into MapPath values('十教', '西南门', 20);

insert into MapPath values('学23', '东南门', 25);
insert into MapPath values('东南门', '学23', 25);

insert into MapPath values('十教', '十一教', 5);
insert into MapPath values('十一教', '十教', 5);

insert into MapPath values('十教', '东南门', 2);
insert into MapPath values('东南门', '十教', 2);

insert into MapPath values('十教', '图书馆', 1);
insert into MapPath values('图书馆', '十教', 1);

insert into MapPath values('十一教', '十二教', 3);
insert into MapPath values('十二教', '十一教', 3);

insert into MapPath values('十二教', '图书馆', 1);
insert into MapPath values('图书馆', '十二教', 1);

insert into MapPath values('图书馆', '东南门', 1);
insert into MapPath values('东南门', '图书馆', 1);

alter table MapPath add column information varchar(1024);

update MapPath set information='睡觉的地方' where origin = '学23';
update MapPath set information='卖饭的地方' where origin = '西南门';
update MapPath set information='放假必经之路' where origin = '新西门';
update MapPath set information='上课的地方' where origin = '十一教';
update MapPath set information='上课的地方' where origin = '十教';
update MapPath set information='图书馆前面的门' where origin = '东南门';
update MapPath set information='借书的地方' where origin = '图书馆';
update MapPath set information='信息学院所在的位置' where origin = '十二教';

select * from MapPath;



