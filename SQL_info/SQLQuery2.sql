create table books_info
(book_ins char(20) primary key,
book_name char(20) not null,
book_auther char(10),
book_press char(15),
book_nums int not null
);
insert into books_info values('ins123456','�����','20');

use LibraryManagementSystem;
select ID from users_login where USER_LEVEL='A';
select * from books_info;

create table books_lend
(lend_user_id char(15) primary key,
lend_book_id char(20) not null,
lend_user_name char(20),
);
insert into books_lend values('A19210467','ind123','�ι���');


insert into users_login values('A19210477','1234abcd','A');
insert into users_login values('A19210111','aabb','B');
insert into users_login values('A19210222','ccdd','B');
insert into users_login values('A19210333','1122','B');
insert into users_login values('A19210444','3344','B');
insert into users_login values('A19210555','5566','B');


insert into books_info values('INS10001','���ݽṹ��C���԰棩','��κ��','�廪��ѧ������','120');
insert into books_info values('INS10002','���Դ���','ͬ�ô�ѧ��ѧϵ','��е��ҵ������','300');
insert into books_info values('INS10003','������̵���','��ǿ','�й�ũҵ��ѧ������','100');
insert into books_info values('INS10004','������������ͳ��','�����ѧϵ','�㽭��ѧ������','200');
insert into books_info values('INS20004','���ݿ�ԭ��Ӧ��','����','��е��ҵ������','50');
insert into books_info values('INS30000','������ע','���','�л����','20');

create table banner_info
(banner_num int primary key,
banner_con char(100)
);

create table users_login
(ID char(15) primary key,
PASSWORDS char(10) not null,
USER_LEVEL char not null
);

insert into banner_info values ('1','��ӭ');
insert into banner_info values ('2','��ӭ');
insert into banner_info values ('3','��ӭ');

update banner_info set banner_con='test' where banner_num='1';

select * from banner_info;

insert into users_login values('A19210666','6666','B');

delete from books_lend where lend_user_id='A19210111' AND lend_book_name='�����';

insert into books_lend values('A19210111','�����','');


