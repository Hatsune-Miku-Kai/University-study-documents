/*第一题
SELECT * FROM jwxt.s;
select sno,sn,age from s where age>=18&&age<=20 and sex='女'
*/


/*第二题
SELECT * FROM jwxt.c;
select s.sno,s.sn from s,sc,c
where s.sno=sc.sno and c.cno=sc.cno and c.cn='高等数学'
group by s.sno,c.cn
*/


/*第三题
SELECT * FROM jwxt.c;
select s.sno, s.sn, sc.score from s,sc,c
where s.sno=sc.sno and c.cno=sc.cno and c.cn='数据库'
group by s.sno
*/


/*第四题
select s.sno, s.sn from s,sc,c
where s.sno=sc.sno and c.cno=sc.cno and (c.cn='数据库' or c.cn='操作系统')
group by s.sno
*/


/*第五题
select sno from sc where sc.cno='c1' and sno in(select sno from sc where cno='c3');
*/


/*第六题
select sno from s
where not exists(select * from c where not exists( select * from sc where sc.cno=c.cno and s.sno=sc.sno ))
*/


/*第七题
select sc.sno from sc where 
cno in (select cno from sc where sno='s1')
group by sno;
*/


/*第八题
select s.sn,s.dept from s where 
not exists(select * from sc,c where sc.cno=c.cno and s.sno=sc.sno )
*/

