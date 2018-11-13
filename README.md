# SQLiteDemo
展示SQLite API的调用方法

程序分为两部分：Shell脚本和C代码，其中Shell脚本用于创建(删除)表和创建索引，C代码用于对表进行增删改查操作。


C代码中程序流程分为三步：打开数据库、操作数据库和关闭数据库：
1)打开数据库时需要指定数据库名，如果数据库不存在，则会创建一个同名的数据库文件；
2)操作数据库是执行具体的对数据表的增删改查操作，对于查询操作，还需要编写回调函数处理数据库返回的数据；
3)类似文件的打开和关闭一样，在操作完数据库之后，一定要关闭数据库。


SQLite提供了三个C语言的API函数：sqlite3_open、sqlite3_exec和sqlite3_close：
1)sqlite3_open第一个参数是具体的数据库文件名，第二个参数是指向SQLite数据库文件的连接；
2)sqlite3_exec共有五个参数，我们主要关注第二和第三个参数，第二个参数是拼装好的SQL语句，第三个参数是回调函数名(仅查询操作需要)；
3)sqlite3_close仅一个参数，用于关闭之前创建的数据库连接。
