#include <stdio.h>
#include <conio.h>
#include "login.h"
#include "menu.h"

dish_chunk *ptr;    // 用于接收指向第一个 dish_chunk 的指针

int main ()
{
    int ch[2];
    extern int choice;
    int is_admin_choice;
    int i = 0;

    is_admin_choice = homepage ();
    login (is_admin_choice, ptr);
    ptr = load_dishes ();
    // menu (ptr);
    // printf ("%s\n", ptr->dish_name);
    // printf ("%s\n", ptr->dish_intro);
    // printf ("%s\n", ptr->comment->comment);/
    // display_all_comments (ptr);
    // printf ("fuck");
    // scanf ("%d", &ch[0]);
    // printf ("1");
    // scanf ("%d", &choice);
    // printf ("%d", choice);
    // ch[0] = getch ();
    // ch[1] = getch ();
    // printf ("%c%c", ch[0], ch[1]);
    system ("pause");

    return 0;
}