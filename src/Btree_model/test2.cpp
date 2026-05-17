#include "head.h"
#include <crtdbg.h>
#include <direct.h>
#include <string>
int main()
{

    char cwd[1024];
     _getcwd(cwd,sizeof(cwd));
    std::string usual_path = std::string(cwd) + "/../src/Btree_model/BTdata/";
    std::string fp_s1_1 = usual_path + "bt21.btr";
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
            std::map<std::string,elemen_type> relations;
            elemen_type tar;
            tar = 'h';//注意区分目标大小写
                // 1. 初始化数组，防止随机值干扰,使用s1会产生的数组
            elemen_type s1[NODE_NUM + 1];
            std::fill(s1, s1 + NODE_NUM + 1, '#');
            s2_find_relation(root,relations, tar,s1);
            print(s1);
            std::cout << "\n";
            if(relations.empty())
            {
                std::cout << "none";
            }
            std::cout << tar;
            for(auto it : relations)
            {
                std::cout << it.first << " : " << it.second;
                std::cout << std::endl;
            }
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