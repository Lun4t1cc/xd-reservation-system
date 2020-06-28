extern void menu ();
extern int update_dishes ();

#define DISH_NAME_SIZE 64
#define COMMENT_SIZE 256
#define DISH_INTRO_SIZE 256

typedef struct Comment_chunk
{
    int index;
    char comment[COMMENT_SIZE];
    struct Comment_chunk *next;
}
comment_chunk;

typedef struct Dish
{
    int index;
    char price[12];
    char dish_name[DISH_NAME_SIZE];
    char dish_intro[DISH_INTRO_SIZE];
    int trolley_flag;   // 作为菜品是否位于购物车中的标志
    comment_chunk *comment;
    struct Dish *next;
}
dish_chunk;

extern dish_chunk* load_dishes ();
extern void display_all_comments (dish_chunk *present_chunk);
void admin_menu (dish_chunk *ptr);
