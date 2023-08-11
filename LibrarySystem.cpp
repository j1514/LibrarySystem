#include<iostream>
#include<cstring>
#include<windows.h>
#include<sql.h>
#include<sqlext.h>
#include <iomanip>
#include<sqltypes.h>
#undef UNICODE
#undef _UNICODE

using namespace std;

//全局变量
SQLRETURN ret = NULL;//返回信息
SQLHENV henv = NULL;//环境句柄
SQLHDBC hdbc = NULL;//连接句柄
SQLHSTMT hstmt = NULL;//语句句柄

//对申请的变量进行释放
void free()
{
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);//释放语句
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);//释放连接
    SQLFreeHandle(SQL_HANDLE_ENV, henv);//释放环境
}


//ODBC数据源:info
//sqlserver登录名:sa
//登录密码:rrrgd5221



//数据库连接函数
void connect()
{
    SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);//申请环境
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);//设置环境
    SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);//申请数据库连接
    ret = SQLConnect(hdbc, (SQLTCHAR*)("info"), SQL_NTS, (SQLTCHAR*)("sa"), SQL_NTS, (SQLTCHAR*)("rrrgd5221"), SQL_NTS);
    //向字符串添加 L 前缀的原因：以将其定义为正确终止的宽字符串。
    //不加L会报错C6276，查看具体信息：https://learn.microsoft.com/zh-cn/cpp/code-quality/c6276?view=msvc-170#%E6%A6%82%E8%A7%88
    if ((ret == SQL_SUCCESS) || (ret == SQL_SUCCESS_WITH_INFO))
    {
        //cout << "数据库连接成功!" << endl;
    }
    else
    {
        cout << "数据库连接失败！" << endl;
    }
}

//插入操作
void insert_book()
{
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
    string str1 = "use LibraryManagementSystem";//第一句要执行的SQL语句
    string str2 = "insert into books_info values ('";//第二句要执行的SQL语句
    cout << "请依次输入图书编号、图书名称、作者、出版社、数量" << endl;
    string Bno, Bname, Bauther, Bpress, Bsum;
    cin >> Bno >> Bname >>Bauther>>Bpress>> Bsum;
    string str3 = str2 + Bno + "','" + Bname + "','"+Bauther+"','"+Bpress+"'," + Bsum + ")";
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        cout << "书籍上架成功！" << endl;
    }
    else {
        cout << "书籍上架失败，请重启系统重试！" << endl;
    }
    free();
}

//公告更新
void banner_update(string num,string content)
{
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
    string str1 = "use LibraryManagementSystem";
    string str2 = "update banner_info set banner_con='"+content;
    string str3 = str2 + "'where banner_num='" + num+"'";
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
    {
        cout << "公告更新完毕！" << endl;
    }
    else
    {
        cout << "banner_update error!" << endl;
    }
    free();
}

//公告查询
void banner_reader()
{
    cout << "***************************************" << endl;
    cout << "****************公告栏*****************" << endl;
    char temp='1';
    for (int i = 0; i < 3; i++)
    {
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
        string str1 = "use LibraryManagementSystem";
        string str2 = "select banner_con from banner_info where banner_num='";
        string str3 = str2 + temp + "';";
        temp++;
        ret = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
        ret = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
        SQLFetch(hstmt);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
        {
            SQLCHAR str3[100];
            SQLLEN len_str3=0;
            SQLGetData(hstmt, 1, SQL_C_CHAR, str3, 100, &len_str3);
            cout << "*" << str3 << endl;
            free();
        }
        else
        {
            cout << "查询失败，请稍后重试！" << endl;
            break;
        }
    }
    cout << "***************************************" << endl;
    cout << "***************************************" << endl;
}

//新用户注册
void user_register(string Sno, string Spass)
{
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
    string str1 = "use LibraryManagementSystem";
    string str2 = "insert into users_login values ('";
    string str3 = str2 + Sno + "','" + Spass + "','B')";
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
    {
        cout << "您已注册成功，请登录！" << endl;
    }
    else
    {
        cout << "注册失败，请稍后重试或联系管理员！"<<endl;
    }
    free();
}

//用户注销
void user_logoff(string Sno)
{
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
    string str1 = "use LibraryManagementSystem";
    string str2 = "delete users_login where ID='";
    string str3 = str2 + Sno + "'";
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
    {
        cout << "该用户已经被注销！"<<endl;
    }
    else
    {
        cout << "注销失败，请重启系统重试！" << endl;
    }
    free();
}

//验证用户等级
string get_user_level(string Sno)
{
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
    string sql = "use LibraryManagementSystem";
    string str1 = "select USER_LEVEL from users_login where ID='";
    string str2 = str1 + Sno + "'";
    ret = SQLExecDirect(hstmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
    SQLFetch(hstmt);
    char str3[5];
    SQLLEN len = Sno.length(), len_str3 = 0;
    SQLGetData(hstmt, 1, SQL_C_CHAR, str3, len, &len_str3);
    string user_level = str3;
    return user_level;
}

//验证用户密码
string get_user_password(string Sno,string Spass)
{
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
    string sql = "use LibraryManagementSystem";
    string str1 = "select PASSWORDS from users_login where ID='";
    string str2 = str1 + Sno + "';";
    //string str2 = "select PASSWORDS from users_login";
    ret = SQLExecDirect(hstmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
    SQLFetch(hstmt);
    char str4[15];
    SQLLEN len = Spass.length() + 1, len_str4 = 0;
    SQLGetData(hstmt, 1, SQL_C_CHAR, str4, len, &len_str4);
    string passwords = str4;
    free();
    return passwords;
}

//验证用户名信息
int get_user_id(string Sno,string Spass)
{
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
    string sql = "use LibraryManagementSystem";
    string str1 = "select ID from users_login where ID='";
    string str2 = str1 + Sno + "'";
    ret = SQLExecDirect(hstmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
    SQLFetch(hstmt);
    char str3[15];
    SQLLEN len=Sno.length()+1, len_str3 = 0;
    SQLGetData(hstmt, 1, SQL_C_CHAR,str3, len,&len_str3);
    string id = str3;
    if (id==Sno)
    {
        free();
        string user_pass = get_user_password(Sno,Spass);
        if (user_pass == Spass)
        {
            //cout << "登陆成功,欢迎您的使用!" << endl;
            return 1;
        }
        else
        {
            free();
            cout << "密码错误，请重新输入！" << endl;
            return 0;
        }
    }
    else
    {
        cout << "不存在账号，请重新输入!" << endl;
        return 0;
    }
    free();
}

//获取图书数量
int get_books_amount(string bname)
{
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
    string sql = "use LibraryManagementSystem";
    string sql2 = "select book_nums from books_info where book_name='";
    string str = sql2 + bname + "'";
    ret = SQLExecDirect(hstmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str.c_str(), SQL_NTS);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
    {
        int a = 0;
        string str1;
        //SQLINTEGER len_str1;
        SQLLEN len_str1;
        while (SQLFetch(hstmt) != SQL_NO_DATA)
        {
            SQLGetData(hstmt, 1, SQL_C_CHAR, (SQLCHAR*)str1.c_str(), 10, &len_str1);   //获取第一列数据
            a = atoi(str1.c_str());
        }
        free();
        return a;
    }
    else
    {
        cout << "get_books_amount error，请联系管理员！" << endl;
        return 0;
    }
}

//删除操作
void delete_book()
{
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
    string str1 = "use LibraryManagementSystem";
    string str2 = "delete books_info where book_name='";
    cout << "请下输入架书籍名称：" << endl;
    string Bname;
    cin >> Bname;
    string str3 = str2 + Bname + "'";
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        cout << "书籍下架成功！" << endl;
    }
    else {
        cout << "书籍下架失败！" << endl;
    }
    free();
}

//借书
void borrow_book()
{
    cout << "请输入你的学号和姓名" << endl;
    string Sno,Sname;
    cin >> Sno >> Sname;
    cout << "请输入你想借的书籍名称" << endl;
    string Bname;
    cin >> Bname;
    if (get_books_amount(Bname) > 0)
    {
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
        string str1 = "use LibraryManagementSystem";
        string str2 = "update books_info set book_nums-=1 where book_name='";
        string str3 = str2 + Bname + "'";
        //string str4 = "select book_ins from books_info where book_name='"+Bname+"'";
        //string str5 = str4 + Bname + "' insert into books_lend values ('" + Sno  + "','" + str4 + "','" + Sname + "')";
        string str5 ="insert into books_lend values ('" + Sno + "','" + Bname + "','" + Sname + "')";
        ret = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
        ret = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
        ret = SQLExecDirect(hstmt, (SQLCHAR*)str5.c_str(), SQL_NTS);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
            cout << "借书成功！" << endl;
        else
            cout << "借书失败,请稍后重试！" << endl;
    }
    else
        cout << "此书图书馆库存不足，目前无法借阅，请谅解！" << endl;
    free();
}

//删除借书信息
void delete_lend(string Sno,string Bname)
{
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
    string str1 = "use LibraryManagementSystem";
    string str2 = "delete from books_lend where lend_user_id='";
    string str3 = str2 + Sno + "' and  lend_book_name='" + Bname + "'";
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
}

//还书
void return_book()
{
    cout << "请输入你的学号" << endl;
    string Sno;
    cin >> Sno;
    cout << "请输入你要还的书籍名称" << endl;
    string Bname;
    cin >> Bname;
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
    string str1 = "use LibraryManagementSystem";
    string str2 = "update books_info set book_nums+=1 where book_name='";
    string str3 = str2 + Bname + "'";
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
    delete_lend(Sno,Bname);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
        cout << "还书成功！" << endl;
    else
        cout << "还书失败！" << endl;
    free();
}

//退出系统
void system_out()
{
    cout << "***************************************" << endl;
    cout << "*****感谢您的使用，期待下次相遇！******" << endl;
    cout << "***************************************" << endl;
}

int main()
{
    //数据库连接
    connect();
    //菜单系统
    cout << "**************************************" << endl;
    cout << "******欢迎使用爱阅读图书管理系统******" << endl;
    cout << "**************************************" << endl;
    //用户标识符
    int user_identify = 0;
    while (1)
    {
        cout << "***************系统主页***************" << endl;
        cout << "1.个人用户登录        2.管理员登录" << endl;
        cout << "3.新用户注册          4.退出系统  " << endl;
        cout << "**************************************" << endl;
        cout << "请输入功能序号：" << endl;
        int menu_x,user_condition=0;
        cin >> menu_x;
        string Sno, Spass;
        if (menu_x == 1)
        {
            cout << "请输入您的账号和密码：" << endl;
            cin >> Sno >> Spass;
            user_condition = get_user_id(Sno, Spass);
            if (user_condition == 1)
            {
                string user_level_nor;
                user_level_nor = get_user_level(Sno);
                if (user_level_nor == "B")
                {
                    user_identify = 1;
                    cout << "登陆成功,欢迎您的使用!" << endl;
                    break;
                }
                else
                {
                    cout << "用户等级错误，请您重新选择登录项！" << endl;
                }
            }
            else
            {
                cout << "登陆失败，请稍后重试或联系管理员！" << endl;
            }
        }
        else if (menu_x == 2)
        {
            cout << "请输入您的账号和密码：" << endl;
            cin >> Sno >> Spass;
            user_condition = get_user_id(Sno, Spass);
            if (user_condition == 1)
            {
                string user_level_mana;
                user_level_mana = get_user_level(Sno);
                if (user_level_mana == "A")
                {
                    user_identify = 2;
                    cout << "登陆成功,欢迎您的使用!" << endl;
                    break;
                }
                else
                {
                    cout<< "用户等级错误，请您重新选择登录项！" << endl;
                }
            }
            else
            {
                cout << "登陆失败，请稍后重试或重启系统！" << endl;
            }
        }
        else if (menu_x == 3)
        {
            cout << "请输入您注册的账号和密码（允许使用特殊字符）：" << endl;
            cin >> Sno >> Spass;
            user_register(Sno, Spass);
        }
        else if (menu_x == 4)
        {
            system_out();
            break;
        }
        else
        {
            cout << "输入选项错误，请重新输入！" << endl;
        }
    }
    if (user_identify == 1)
    {
        while (1)
        {
            cout << "****************功能主页***************" << endl;
            cout << "1.查询图书数量          2.借阅图书" << endl;
            cout << "3.归还借阅图书          4.查看公告" << endl;
            cout << "5.退出系统" << endl;
            cout << "***************************************" << endl;
            cout << "请输入功能序号：" << endl;
            int menu_y;
            cin >> menu_y;
            if (menu_y == 1)
            {
                string Bname;
                cout << "请输入您要查询的书籍名称：" << endl;
                cin >> Bname;
                int book_amount_user;
                book_amount_user = get_books_amount(Bname);
                cout << Bname << "目前还有" << book_amount_user << "本！" << endl;
            }
            else if (menu_y == 2)
            {
                borrow_book();
            }
            else if (menu_y == 3)
            {
                return_book();
            }
            else if (menu_y == 4)
            {
                banner_reader();
            }
            else if (menu_y == 5)
            {
                system_out();
                break;
            }
            else
            {
                cout << "输入功能选项错误，请重新输入！" << endl;
            }
        }
    }
    else if (user_identify == 2)
    {
        while (1)
        {
            cout << "****************功能主页***************" << endl;
            cout << "1.查询图书数量             2.上架图书" << endl;
            cout << "3.下架图书                 4.注销用户" << endl;
            cout << "5.公告更新                 6.退出系统" << endl;
            cout << "***************************************" << endl;
            cout << "请输入功能序号：" << endl;
            int menu_z;
            cin >> menu_z;
            if (menu_z == 1)
            {
                string Bname;
                cout << "请输入您要查询的书籍名称：" << endl;
                cin >> Bname;
                int book_amount_manage;
                book_amount_manage = get_books_amount(Bname);
                cout<< Bname << "目前还有" << book_amount_manage << "本！" << endl;
            }
            else if (menu_z == 2)
            {
                insert_book();
            }
            else if (menu_z == 3)
            {
                delete_book();
            }
            else if (menu_z == 4)
            {
                string Sno;
                cout << "请输入需要注销的用户ID：" << endl;
                cin >> Sno;
                user_logoff(Sno);
            }
            else if (menu_z == 5)
            {
                cout << "请输入您一共需要更新几条公告：" << endl;
                int up_total;
                cin >> up_total;
                while (up_total--)
                {
                    string up_num;
                    cout << "请输入更新公告的序号：" << endl;
                    cin >> up_num;
                    cout << "请输入新的公告内容：" << endl;
                    string up_content;
                    cin >> up_content;
                    banner_update(up_num,up_content);
                }
            }
            else if (menu_z == 6)
            {
                system_out();
                break;
            }
            else
            {
                cout << "输入功能选项错误，请重新输入！" << endl;
            }
        }
    }
	return 0;
}
