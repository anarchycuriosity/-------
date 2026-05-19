#include "head.h"
#include <crtdbg.h>
#include <direct.h>
#include <string>
#include <stack>
// void recurse(cs_node* t)
// {
//     if (t == nullptr)
//     {
//         return;
//     }

//     // 1. 打印当前节点
//     std::cout << t->data;

//     // 2. 如果有孩子，说明有下一层，用括号包裹起来
//     if (t->first_child != nullptr)
//     {
//         std::cout << "(";
//         recurse(t->first_child); // 递归处理子树（会处理子树的所有兄弟）
//         std::cout << ")";        // 子树处理完毕，闭合右括号
//     }

//     // 3. 如果有右兄弟，说明同级还有节点，用逗号分隔，并继续递归处理右兄弟
//     if (t->next_sibling != nullptr)
//     {
//         std::cout << ",";
//         recurse(t->next_sibling); // 递归处理同级的下一个兄弟
//     }
// }
void recurse(cs_node * t)//use & ,since it's global value,always updated
{
    //before enter the lchild,cout (
    //if there is no lchild but next_cibling,just cout ,
    //if the node is a total end ,no l no next,cout ,)
    std::cout << t->data;
    if(t->first_child != nullptr)
    {
        std::cout << "(";
        recurse(t->first_child);
        std::cout << ")";//递归的对称性，谁开的括号必须由谁来闭合
    }
    //混乱的if语句和return会导致某些功能冲突和蒸发
    // if(t->first_child == nullptr && t->next_sibling == nullptr)
    // {
    //     std::cout << "),";
    //     return;
    // }
    // if(t->first_child != nullptr && t->next_sibling != nullptr)有l有n就横着找是错的，万一无l有n就炸了
    // {
    //     std::cout << ",";
    //     recurse(t->next_sibling);
    // }
    if(t->next_sibling !=nullptr)
    {
        std::cout << ",";
        recurse(t->next_sibling);
    }

}

int main()
{

    char cwd[1024];
     _getcwd(cwd,sizeof(cwd));
    std::string usual_path = std::string(cwd) + "/../src/tree/tData/";
    std::string fp_s1_1 = usual_path + "F20.tre";//操作这个最多到的下标是61
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
        while(t != nullptr)
        {
            std::cout << t->data << "(";
            recurse(t->first_child);
            t = t->next_sibling;
            std::cout << ",                 ";
        }
        
    }
    else
    {
        std::cout << "creat_tree: error";
    }


}