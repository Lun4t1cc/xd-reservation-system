#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISH_NAME_SIZE 64
#define INTRO_SIZE 256
#define COMMENT_SIZE 256
#define MAXSIZE 256
#define DISH_PATH_SIZE 256
#define DISH_INTRO_SIZE 256
#define COMMENT_INDEX 256
#define COMMENT_SIZE 256
// #define COMMENT_END 0

static char dish_path[DISH_PATH_SIZE];

/* 从菜单列表中读取每样菜品所对应文件的地址 */
char* load_dish_path (FILE *fp)
{
    char *ret;

    // fscanf (fp, "%s", dish_path);
    ret = fgets (dish_path, DISH_PATH_SIZE, fp);
    // ret = dish_path;

    return ret;
}

/* 读取菜品相关评论 */
char** load_dish_comment (FILE *dish_fp)
{
    int index = 0;
    static char comment_list[COMMENT_INDEX][COMMENT_SIZE];
    int ret = 0;

    do
    {
        ret = fscanf (dish_fp, "%s", comment_list[index]);
        index++;
    }
    while (ret != EOF);
    
    return comment_list;
}

/* 更新菜单 */
int update_dishes ()
{
    const char *path_ptr;   
    FILE *dishes_paths_fp;
    FILE *dish_fp;
    char dish_name[DISH_NAME_SIZE];
    char dish_intro[DISH_INTRO_SIZE];
    char** comment_ptr;
    size_t path_length;

    dishes_paths_fp = fopen ("C:\\Users\\Breez3\\Desktop\\C\\big_work\\dishes_paths.txt", "r");
    // dishes_paths_fp = fopen ("./dishes_paths.txt", "r");
    
    do
    {
        path_ptr = load_dish_path (dishes_paths_fp);
        // path_length = strlen (path_ptr);
        // path_ptr[path_length - 1] = '\0';
        
        if (path_ptr != NULL)
        {
            dish_fp = fopen (path_ptr, "r");

            if (dish_fp == NULL) 
            {
                fprintf (stderr, "%d", errno);
                break;
            }

            fscanf (dish_fp, "%s", dish_name);
            fscanf (dish_fp, "%s", dish_intro);
            comment_ptr = load_dish_comment (dish_fp);
            printf ("%s\n", dish_name);
            printf ("%s\n", dish_intro);
            printf ("%s\n", comment_ptr);
            
            // printf ("%s", dish_name);
            fclose (dish_fp);
        }
    }
    while (path_ptr != NULL);

    fclose (dishes_paths_fp);

    return 0;
}

int main ()
{
    update_dishes ();

    return 0;    
}

