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
    std::string usual_path = std::string(cwd) + "/../src/tree/BTdata/";
    std::string fp_s1_1 = usual_path + "bt261.btr";//操作这个最多到的下标是61
    char tmp[1024];//储存着临时的文件路径
    std::strncpy(tmp, fp_s1_1.c_str(), sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0'; // 确保安全截断

    char str_line[NODE_NUM][3];
    int n_arr_len;//得到数组的长度，也就是节点数
    bnode *root = new bnode;
    int cur_row = 0;
    if(read_file_to_array(tmp,str_line,n_arr_len))
    {
        if(create_bi_tree_from_file(root,str_line,n_arr_len,cur_row))
        {
            recurse(root);
        }
        else
        {
            std::cout << "creat_bi:fail";
        }
    }
    else
    {
        std::cout << "read_file:fail";
    }


}