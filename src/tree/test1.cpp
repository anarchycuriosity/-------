#include "head.h"
#include <crtdbg.h>
#include <direct.h>
#include <string>
int main()
{
    // char cwd[1024];
    // if (_getcwd(cwd, sizeof(cwd)) != nullptr) 
    // {
    //     std::cout << "Current working dir: " << cwd << std::endl;
    // }
    //当前是在bin文件夹所以需要返回一个然后去到src文件夹
    // FILE * fp;
    // fp = fopen("../src/Btree_model/BTdata/bt10.btr","r");
    // if(fp == nullptr)
    // {
    //     std::cout << "fail";
    // }
    // else
    // {
    //     std::cout << "success";
    // }
    char cwd[1024];
     _getcwd(cwd,sizeof(cwd));
    std::string usual_path = std::string(cwd) + "/../src/tree/BTdata/";
    std::string fp_s1_1 = usual_path + "bt8.btr";
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
            elemen_type s1[1024];
            s1_convert_array(root,s1);
            print(s1);
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