create table books_info
(book_ins char(20) primary key,
book_name char(20) not null,
book_auther char(10),
book_press char(15),
book_nums int not null
);
insert into books_info values('ins123456','计算机','20');

use LibraryManagementSystem;
select ID from users_login where USER_LEVEL='A';
select * from books_info;

create table books_lend
(lend_user_id char(15) primary key,
lend_book_id char(20) not null,
lend_user_name char(20),
);
insert into books_lend values('A19210467','ind123','任国鼎');


insert into users_login values('A19210477','1234abcd','A');
insert into users_login values('A19210111','aabb','B');
insert into users_login values('A19210222','ccdd','B');
insert into users_login values('A19210333','1122','B');
insert into users_login values('A19210444','3344','B');
insert into users_login values('A19210555','5566','B');


insert into books_info values('INS10001','数据结构（C语言版）','严魏敏','清华大学出版社','120');
insert into books_info values('INS10002','线性代数','同济大学数学系','机械工业出版社','300');
insert into books_info values('INS10003','软件工程导论','付强','中国农业大学出版社','100');
insert into books_info values('INS10004','概率论与数理统计','浙大数学系','浙江大学出版社','200');
insert into books_info values('INS20004','数据库原理及应用','高萌','机械工业出版社','50');
insert into books_info values('INS30000','论语译注','杨伯峻','中华书局','20');

create table banner_info
(banner_num int primary key,
banner_con char(100)
);

create table users_login
(ID char(15) primary key,
PASSWORDS char(10) not null,
USER_LEVEL char not null
);

insert into banner_info values ('1','欢迎');
insert into banner_info values ('2','欢迎');
insert into banner_info values ('3','欢迎');

update banner_info set banner_con='test' where banner_num='1';

select * from banner_info;

insert into users_login values('A19210666','6666','B');

delete from books_lend where lend_user_id='A19210111' AND lend_book_name='计算机';

insert into books_lend values('A19210111','计算机','');


