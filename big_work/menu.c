#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

#define DISHES_PATH "C:\\Users\\Breez3\\Desktop\\C\\big_work\\dishes_paths.txt"
#define INTRO_SIZE 256
#define MAXSIZE 256
#define DISH_PATH_SIZE 256
#define COMMENT_INDEX 256
#define COMMENT_SIZE 256
// #define COMMENT_END 0

static char dish_path[DISH_PATH_SIZE];

/* 显示某个菜品的所有评论 */
void display_all_comments (dish_chunk *present_chunk)
{
    comment_chunk *comment_head;
    comment_chunk *present_comment_chunk;

    comment_head = present_chunk->comment;
    present_comment_chunk = comment_head;
    printf ("用户评论:\n");

    do
    {
        printf ("%d. %s\n", present_comment_chunk->index, present_comment_chunk->comment);
        present_comment_chunk = present_comment_chunk->next;
    }
    while (present_comment_chunk != NULL);
}

/* 从菜单列表中读取每样菜品所对应文件的地址 */
char* load_dish_path (FILE *fp)
{
    char *ret;
    // fscanf (fp, "%s", dish_path);
    ret = fgets (dish_path, DISH_PATH_SIZE, fp);
    if (ret != NULL && ret[strlen(ret) - 1] == '\n') {
        ret[strlen(ret) - 1] = '\0';
    }
    // ret = dish_path;
    return ret;
}

/* 载入菜品相关评论 */
comment_chunk* load_dish_comment (FILE *dish_fp)
{
    int index = 1;
    char comment_buf[COMMENT_SIZE];
    comment_chunk *head;
    comment_chunk *present_chunk;
    int ret = 0;
    int first_flag = 1;

    do
    {
        ret = fscanf (dish_fp, "%s", comment_buf);
        
        if (ret != EOF)
        {
            if (first_flag == 1)
            {
                head = (comment_chunk*) malloc (sizeof (comment_chunk));
                present_chunk = head;
                first_flag = 0;
            }
            else
            {
                present_chunk->next = (comment_chunk*) malloc (sizeof (comment_chunk));
                present_chunk = present_chunk->next;
            }
            
            strcpy (present_chunk->comment, comment_buf);
            present_chunk->index = index;
            index++;
        }
    }
    while (ret != EOF);

    present_chunk->next = NULL;
    
    return head;
}

/* 加载菜单信息 */
dish_chunk* load_dishes ()
{
    dish_chunk *head = NULL;
    dish_chunk *present_chunk;
    FILE *dishes_paths_fp;
    int dish_index = 1;
    int first_flag = 1;     // 记录是否为第一次进入

    const char *dish_path;   
    FILE *dish_fp;
    char dish_name[DISH_NAME_SIZE];
    char dish_price[12];
    char dish_intro[DISH_INTRO_SIZE];
    char** comment_ptr;
    size_t path_length;
    
    dishes_paths_fp = fopen (DISHES_PATH, "r");

    do
    {
        dish_path = load_dish_path (dishes_paths_fp);
        
        if (dish_path != NULL)
        {
            if (first_flag == 1)
            {
                head = (dish_chunk*) malloc (sizeof (dish_chunk));
                present_chunk = head;
                first_flag = 0;
            }
            else
            {
                present_chunk->next = (dish_chunk*) malloc (sizeof (dish_chunk));
                present_chunk = present_chunk->next;
            }
            
            dish_fp = fopen (dish_path, "r");
            present_chunk->trolley_flag = 0;
            present_chunk->index = dish_index;
            dish_index++;
            fscanf (dish_fp, "%s", dish_name);
            strcpy (present_chunk->dish_name, dish_name);
            fscanf (dish_fp, "%s", dish_price);
            strcpy (present_chunk->price, dish_price);
            fscanf (dish_fp, "%s", dish_intro);
            strcpy (present_chunk->dish_intro, dish_intro);
            present_chunk->comment = load_dish_comment (dish_fp);
            fclose (dish_fp);
        }
    }
    while (dish_path != NULL);

    present_chunk->next = NULL;
    fclose (dishes_paths_fp);

    return head;
}

/* 显示菜单中的所有菜品名称 */
void show_todays_menu (dish_chunk *ptr)
{
    dish_chunk *present_chunk;
    
    present_chunk = ptr;
    
    do
    {
        printf ("    %d. %s %s 元/份\n", present_chunk->index, present_chunk->dish_name, present_chunk->price);
        present_chunk = present_chunk->next;
    }
    while (present_chunk != NULL);
}

/* 显示某个菜品的详细信息 */
void show_dish_info (dish_chunk *head, int index)
{
    dish_chunk *present_chunk;

    present_chunk = head;
    while (present_chunk->index != index) {
        present_chunk = present_chunk->next;
    }
    system ("cls");
    printf ("*%s*\n\n", present_chunk->dish_name);
    printf ("简介：\n%s\n\n", present_chunk->dish_intro);
    display_all_comments (present_chunk);
}

/* 添加菜品至购物车 */
dish_chunk* add_to_shop_trolley (int dish_index, dish_chunk *ptr)
{
    dish_chunk *present_chunk;

    present_chunk = ptr;

    while (present_chunk != NULL)
    {
        if (present_chunk->index == dish_index) 
        {
            present_chunk->trolley_flag = 1;
            break;
        } 
        else 
        {
            present_chunk = present_chunk->next;
        }
    }

    return ptr;
}

/* 从购物车中删除菜品 */
dish_chunk* remove_frome_shop_trolley (int dish_index, dish_chunk *ptr)
{
    dish_chunk *present_chunk;

    present_chunk = ptr;

    while (present_chunk != NULL)
    {
        if (present_chunk->index == dish_index) 
        {
            present_chunk->trolley_flag = 0;
            break;
        } 
        else 
        {
            present_chunk = present_chunk->next;
        }
    }

    return ptr;   
}

/* 显示购物车内所有菜品 */
void show_shop_troley (dish_chunk *ptr)
{
    dish_chunk *present_chunk;
    int index = 1;

    present_chunk = ptr;
    printf ("\n购物车内商品：\n");
    
    while (present_chunk != NULL)
    {
        if (present_chunk->trolley_flag == 1)
        {
            printf ("%d. %s %s 元/份\n", index, present_chunk->dish_name, present_chunk->price);
            index++;
            present_chunk = present_chunk->next;
        }
        else
        {
            present_chunk = present_chunk->next;
            continue;
        }
    }

    printf ("\n");    
}

/* 计算并显示购物车内物品的总价 */
double calculate_total_price (dish_chunk *ptr)
{
    dish_chunk *present_chunk;
    double sum = 0;

    present_chunk = ptr;

    while (present_chunk != NULL)
    {
        if (present_chunk->trolley_flag == 1)
        {
            sum += atof (present_chunk->price);
            present_chunk = present_chunk->next;
        } 
        else
        {
            present_chunk = present_chunk->next;
        }
    }

    printf ("购物车内菜品总价为：%.2lf 元\n", sum);

    return sum;
}

/* 管理员删除指定评论 */
void* Delete_comment (dish_chunk *ptr, int dish_index)
{
    comment_chunk *comment_head;
    comment_chunk *present_comment_chunk;
    comment_chunk *bkw_comment_chunk;
    dish_chunk *present_dish_chunk = ptr;
    int comment_delete_index;
    printf ("输入评论序号 > ");
    scanf ("%d", &comment_delete_index);
    while (present_dish_chunk != NULL)
    {
        if (present_dish_chunk->index == dish_index)
        {
            comment_head = present_dish_chunk->comment;
            present_comment_chunk = comment_head;
            bkw_comment_chunk = comment_head;
            while (comment_head != NULL)
            {
                if (present_comment_chunk->index == comment_delete_index)
                {
                    bkw_comment_chunk->next = present_comment_chunk->next;
                    return;
                }
                bkw_comment_chunk = present_comment_chunk;
                present_comment_chunk = present_comment_chunk->next;
            }
        }
        present_dish_chunk = present_dish_chunk->next;
    }
}

/* 显示用户菜单 */
void menu (dish_chunk *ptr)
{
    int choice;
    int choice2;    // 在菜品信息界面中输入的选项
    int choice3;
    int dish_index;
    int delet_dish_index;

    while (1)
    {
        system ("cls");
        printf ("\t*今日菜单*\n");
        show_todays_menu (ptr);
        printf ("\n1) 查看菜品详情\n");
        printf ("2) 下单支付\n");
        printf ("输入选项 > ");
        scanf ("%d", &choice);
        fflush (stdin);
        
        if (choice == 1) 
        {
            printf ("输入菜品序号 > ");
            scanf ("%d", &dish_index);
            show_dish_info (ptr, dish_index);
            printf ("\n1) 添加至购物车");
            printf ("\n2) 返回");
            printf ("\n输入选项 > ");
            scanf ("%d", &choice2);
            
            if (choice2 == 1) {
                add_to_shop_trolley (dish_index, ptr);
            } else {
                continue;
            }
        } 
        else if (choice == 2) 
        {
            show_shop_troley (ptr);
            calculate_total_price (ptr);
            printf ("\n1) 删除菜品\n");
            printf ("2) 返回\n");
            printf ("输入选项 > ");
            scanf ("%d", &choice3);

            if (choice3 == 1)
            {
                printf ("输入删除的菜品序号 > ");
                scanf ("%d", &delet_dish_index);
                remove_frome_shop_trolley (delet_dish_index, ptr);
            }
            else
            {
                continue;
            }
        } 
        else 
        {
            printf ("无效选项");
        }
    }

}

/* 显示管理员菜单 */
void admin_menu (dish_chunk *ptr)
{
    int choice;
    int choice2;    // 在菜品信息界面中输入的选项
    int choice3;
    char choice4;
    int dish_index;
    int delet_dish_index;

    while (1)
    {
        system ("cls");
        printf ("\t*今日菜单*\n");
        show_todays_menu (ptr);
        printf ("\n1) 查看菜品详情\n");
        printf ("2) 更新菜单\n");
        printf ("输入选项 > ");
        scanf ("%d", &choice);
        fflush (stdin);
        
        if (choice == 1) 
        {
            printf ("输入菜品序号 > ");
            scanf ("%d", &dish_index);
            show_dish_info (ptr, dish_index);
            printf ("\n1) 删除评论");
            printf ("\n2) 返回");
            printf ("\n输入选项 > ");
            scanf ("%d", &choice2);
            
            if (choice2 == 1) {
                Delete_comment (ptr, dish_index);
            } else {
                continue;
            }
        } 
        else if (choice == 2) 
        {
            printf ("是否确定更新菜单？(y/n)");
            scanf("%c", &choice4);
            
            if (choice4 == 'y' || choice4 == 'Y')
            {
                fflush (stdin);
                ptr = load_dishes ();
            }
            else
            {
                continue;
            }
        } 
        else 
        {
            printf ("无效选项");
        }
    }    
}