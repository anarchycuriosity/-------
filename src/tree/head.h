#include "CreateBiTree.h"
#include "createtree.h"
#include <map>
#include <vector>
#include <unordered_map>
#include <set>
void s1_convert_array(bnode *root, elemen_type *s1) // s1数组从1开始存
{
    int i = 1;
    struct node_pair
    {
        bnode * node_p;
        int ind;
    };
    int max_i = NODE_NUM + 1;
    std::queue<node_pair> q;
    q.push({root,1});
    // while (root != nullptr)
    while(!q.empty())
    {
        bnode *node = q.front().node_p;
        i = q.front().ind;
        s1[i] = node->data;
        if (node->lchild)
        {
            s1[2 * i] = node->lchild->data;
            q.push({node->lchild,2 * i});
            max_i = std::max(2*i,max_i);
        }
        else
        {
            s1[2 * i] = (elemen_type)'#';
        }
        if (node->rchild)
        {
            s1[2 * i + 1] = node->rchild->data;
            q.push({node->rchild,2 * i + 1});
            max_i = std::max(2 * i + 1,max_i);
        }
        else
        {
            s1[2 * i + 1] = (elemen_type)'#';
        }
        q.pop();
    }
    s1[max_i + 1] = '\0';//其实加不加无所谓
}
void print(elemen_type *arr)
{
    for (int i = 1;; i++)
    {
        if (arr[i] == '\0')
        {
            break;
        }
        std::cout << arr[i] << " ";
    }
}



void s2_find_relation(bnode* root, std::map<std::string, elemen_type>& relations, elemen_type tar,elemen_type s1[])
{


    // 2. 填充数组 (确保此函数按照层序索引填入，即 root 在 s1[1])
    s1_convert_array(root, s1);

    // 3. 查找逻辑
    for (int i = 1; i <= NODE_NUM; i++)
    {
        if (s1[i] == tar)
        {
            // 父节点逻辑
            if (i > 1)
            {
                relations["father"] = s1[i / 2];
            }

            // 左右孩子逻辑
            if (2 * i <= NODE_NUM)
            {
                relations["left_child"] = s1[2 * i];
            }
            if (2 * i + 1 <= NODE_NUM)
            {
                relations["right_child"] = s1[2 * i + 1];
            }

            // 兄弟逻辑
            if (i % 2 == 0) // i 是左孩子
            {
                if (i + 1 <= NODE_NUM)
                {
                    relations["right_bro"] = s1[i + 1];
                }
            }
            else if (i > 1) // i 是右孩子且不是根
            {
                relations["left_bro"] = s1[i - 1];
            }
            
            return; 
        }
    }
}

// 因为要找祖先，所以我们用后序搜索，找到直接就返回
// 递归不需要借助数据结构
bnode *s3_find_lca(bnode *root, elemen_type l, elemen_type r) // local_common_ancestor
{
    if (root == nullptr || root->data == l || root->data == r)
    {
        return root;
    }

    bnode *left = s3_find_lca(root->lchild, l, r);
    bnode *right = s3_find_lca(root->rchild, l, r);
    if (left != nullptr && right != nullptr)
    {
        return root; // 如果真的找到了，这里就是第一层递归，return直接结束了
    }
    // 但万一已经到了第一层递归，但是右边还是没找到东西，因为东西都在左边
    // 必须要返回，不然就没有返回值了
    return (left != nullptr) ? (left) : (right);
}
void s4_find_leaf_path(bnode *root, std::vector<elemen_type> &path) // 找到叶子节点的路径并输出
{
    if (root == nullptr)
    {
        return; // 此时的root不是叶子，它啥也不是
    }
    path.push_back(root->data);
    if (root->lchild == nullptr && root->rchild == nullptr)
    {
        std::cout << root->data << " : ";
        for (int i = path.size() - 1; i >= 0; i--)
        {
            std::cout << path[i] << " -> ";
        }
        std::cout << "\n";
    }
    else
    {
        s4_find_leaf_path(root->lchild, path);
        s4_find_leaf_path(root->rchild, path);
    }
    path.pop_back();
    // 这个弹出非常的有讲究
    // 当第一层深入递归之后，它所在的栈帧会暂停，递归回来，这个弹出才会被执行，我甚至一开始愚蠢的以为它不会被执行
    // 并不是只有写了return这层才会结束，return只是人为设计的为了提前返回，防止对空指针重复操作，和设计返回任务罢了
}
void s5_build_CS_list_get_degree(std::vector<std::pair<elemen_type,elemen_type>> &pc_vec)//pc指的是parent child    因为没有树相关函数，所以只能手动写
{
    //find parents and their children,so we can build tree
    //find root node through a child set
    //about map:key is value and value is its children's ptrs
    std::set<elemen_type> child_set;
    // std::unordered_map<elemen_type,std::vector<bnode>> node_map;     we can write like this 
    //because everytime we conduct on one ptr,its copy on other key's values will not be changed
    //original array is also not allowed,because value copy is always the thing happens
    for(auto &it : pc_vec)
    {

    }
}