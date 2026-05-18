#include "head.h"
#include <crtdbg.h>
#include <direct.h>
#include <string>
#include <stack>
int count_degree(cs_node * t)
{
    if(t == nullptr)
    {
        return 0;
    }
    return 1 + count_degree(t->next_sibling);
}
void recurse(cs_node * t,int &max_degree)//use & ,since it's global value,always updated
{
    if(t == nullptr)
    {
        return;
    }
    //the degree of current node is its left child and its sibling
    //we need to call another function to recurse instead of one
    //max_degree is a global value,though its update happens through recursing deep
    //it is "updated" through,but not straightly decided by its sub
    int currrent_degree = count_degree(t->first_child);
    max_degree = std::max(currrent_degree,max_degree);
    recurse(t->first_child,max_degree);
}
int main()
{

    char cwd[1024];
     _getcwd(cwd,sizeof(cwd));
    std::string usual_path = std::string(cwd) + "/../src/tree/tData/";
    std::string fp_s1_1 = usual_path + "tree11.tre";//操作这个最多到的下标是61
    char tmp[1024];//储存着临时的文件路径
    std::strncpy(tmp, fp_s1_1.c_str(), sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0'; // 确保安全截断

    // char str_line[NODE_NUM][2];
    // int n_arr_len;//得到数组的长度，也就是节点数
    p_tree root;
    // int cur_row = 0;
    if(create_tree_from_file(tmp,root))
    {
        std::cout << "create_tree: success\n";
        cs_node *t;
        create_cs_tree(t,root);
        int max_degree = 0;
        recurse(t,max_degree);
        std::cout << max_degree;
        
    }
    else
    {
        std::cout << "creat_tree: error";
    }


}