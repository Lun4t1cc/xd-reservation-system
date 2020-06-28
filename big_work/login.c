#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "menu.h"
#include "login.h"


#define PATH_SIZE 128
#define ACCOUNTS_PASSWDS_PATH "C:\\Users\\Breez3\\Desktop\\C\\big_work\\account_passwd.txt"
#define ADMIN_PASSWDS_PATH "C:\\Users\\Breez3\\Desktop\\C\\big_work\\admin_account.txt"
#define LOGIN_FAILURE -1
#define LOGIN_SUCCESS 1

int choice;

/* 显示菜单 */
int homepage ()
{
    system ("cls");
    printf ("### XD Reservation System ###\n\n");
    printf ("\t1) 师生登录\n");
    printf ("\t2) 管理员登录\n\n");
    printf ("输入选项 > ");
    scanf ("%d", &choice);
    return choice;
}

/* 接收密码 */
void receivePasswd (char *passwd)
{
    for (int i = 0; i < 12; i++)
    {
        passwd[i] = getch ();
        
        if ((passwd[i] == '\r') || (passwd[i] == '\n'))
        {
            passwd[i] = '\0';
            break;
        }     
    }
}

/* 匹配账号密码 */
int matchAccountPasswd (char *account, char *passwd, int is_admin)
{
    FILE *fp;   /* 账号密码文件的句柄 */
    char tmp_account[12];
    char tmp_passwd[12];
    int match_account;
    int match_passwd;

    if (is_admin == 0)
    {
        fp = fopen (ACCOUNTS_PASSWDS_PATH, "r");
        fscanf (fp, "%s > %s", tmp_account, tmp_passwd);
        match_account = strcmp(account, tmp_account);
        match_passwd = strcmp(passwd, tmp_passwd);
        
        if (!(match_account && match_passwd))
        {
            system ("cls");
            printf ("# 登录成功\n");
            return LOGIN_SUCCESS;
        }
        else
        {
            system ("cls");
            printf ("# 登录失败\n");
            printf ("# 即将退出\n");
            system ("pause");
            exit(LOGIN_FAILURE);
        }
    }
    else if (is_admin == 1)
    {
        fp = fopen (ADMIN_PASSWDS_PATH, "r");
        fscanf (fp, "%s > %s", tmp_account, tmp_passwd);
        match_account = strcmp(account, tmp_account);
        match_passwd = strcmp(passwd, tmp_passwd);
        
        if (!(match_account && match_passwd))
        {
            system ("cls");
            printf ("# 登录成功\n");
            return LOGIN_SUCCESS;
        }
        else
        {
            system ("cls");
            printf ("# 登录失败\n");
            printf ("# 即将退出\n");
            system ("pause");
            exit(LOGIN_FAILURE);
        }
    }
}

/* 师生登录 */
int teacher_student_login ()
{
    char account[12];
    char passwd[12];
    int is_login_success;   
    printf ("输入学号 > ");
    scanf ("%s", account);
    printf ("输入密码 > ");
    receivePasswd (passwd);
    is_login_success = matchAccountPasswd (account, passwd, 0);
    // printf("\n%s", passwd);
}

/* 管理员登录 */
int administrator_login ()
{
    char account[12];
    char passwd[12];
    int is_login_success;
    printf ("输入学号 > ");
    scanf ("%s", account);
    printf ("输入密码 > ");
    receivePasswd (passwd);
    is_login_success = matchAccountPasswd (account, passwd, 1);
}

/* 登录 */
void login (int choice, dish_chunk *ptr)
{
    int login_state = 0;
    if (choice == 1) {
        login_state = teacher_student_login ();
        if (login_state == LOGIN_SUCCESS)
            menu ();
    } 
    else if (choice == 2)
    {
        login_state = administrator_login ();
        if (login_state == LOGIN_SUCCESS)
            admin_menu (ptr);
    }
    login_state = 0;
}

