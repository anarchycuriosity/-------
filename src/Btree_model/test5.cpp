#include "head.h"
#include <crtdbg.h>
#include <direct.h>
#include <string>
#include <stack>
//remember the path walked
std::stack<elemen_type> path;
void print_st(std::stack<elemen_type> st)
{
    while(!st.empty())
    {
        std::cout << st.top() << " ";
        st.pop();
    }
    std::cout << "\n";
}
void recurse(bnode * cur)
{
    //have to ensure data exist
    if(cur == nullptr)
    {
        return;
    }
    path.push(cur->data);
    if(cur->lchild == nullptr && cur->rchild == nullptr)
    {
        print_st(path);
        path.pop();
        return;
    }
    recurse(cur->lchild);
    recurse(cur->rchild);
    path.pop();
    //return; if lchild and rchild already searched,it automatically return
}
int main()
{

    char cwd[1024];
     _getcwd(cwd,sizeof(cwd));
    std::string usual_path = std::string(cwd) + "/../src/Btree_model/tData/";
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
        std::cout << "create_tree: success";
    }
    else
    {
        std::cout << "creat_tree: error";
    }


}