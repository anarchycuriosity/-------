#include "head.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    // 任务 1: 括号匹配测试

    std::cout << "### 任务 1: 括号匹配判断 ###" << std::endl;

    std::vector<std::string> bracket_tests =
        {
            "{[](){}}",
            "{[(})]",
            "((()))",
            "()[]{}",
            "(["};

    for (int i = 0; i < bracket_tests.size(); ++i)
    {
        bool result = judge_brackets(bracket_tests[i]);
        std::cout << "测试用例 " << i + 1 << " [" << bracket_tests[i] << "]: "
                  << (result ? "匹配成功" : "匹配失败") << std::endl;
    }

    std::cout << "\n\n"
              << std::endl;

    // 任务 2: 出栈序列数量计算

    std::cout << "### 任务 2: 所有可能的出栈序列数量 ###" << std::endl;

    // 实验要求测试 n = 5 的情况
    std::vector<int> n_values = {3, 5};

    for (int n : n_values)
    {
        std::vector<int> sequence;
        for (int i = 1; i <= n; ++i)
        {
            sequence.push_back(i);
        }

        Queue q(sequence);
        Stack st;
        int sort_count = 0;

        // 递归模拟所有可能的入栈与出栈路径
        get(q, st, sort_count);

        std::cout << "当输入序列为 1 到 " << n << " 时, 可能的出栈序列总数为: "
                  << sort_count << std::endl;
    }

    std::cout << "\n\n"
              << std::endl;

    // 任务 3: 约瑟夫环问题

    std::cout << "### 任务 3: 约瑟夫环问题 (Josephus Ring) ###" << std::endl;

    struct josephus_params
    {
        int n; // 总人数
        int k; // 报数数值
        int m; // 剩余人数
    };

    std::vector<josephus_params> joe_tests =
        {
            {9, 2, 1}, // 预期输出: 3 [cite: 26, 27]
            {6, 5, 1}, // 预期输出: 1 [cite: 28, 29]
            {11, 3, 2} // 预期输出: 2 7 [cite: 30, 31]
        };

    for (int i = 0; i < joe_tests.size(); ++i)
    {
        int n = joe_tests[i].n;
        int k = joe_tests[i].k;
        int m = joe_tests[i].m;

        std::vector<int> people(n);
        for (int j = 1; j <= n; ++j)
        {
            people[j - 1] = j;
        }

        linkedList_ord cir(people);

        // 转换逻辑：移除单链表的哨兵头节点，构建循环链表
        linkedList_ord::list_node *old_head = cir.head;
        cir.head = cir.head->next;
        cir.end->next = cir.head;
        cir.loop_change = true;
        linkedList_ord::list_node *cur = cir.end;
        delete old_head;

        std::cout << "测试用例 " << i + 1 << " (n=" << n << ", k=" << k << ", m=" << m << "): ";

        while (cir.count > m)
        {
            for (int step = 1; step < k; ++step)
            {
                cur = cur->next;
            }
            linkedList_ord::list_node *del = cur->next;
            if (del == cir.head)
            {
                cir.head = cur->next->next;
            }
            cur->next = cur->next->next;
            delete del;
            cir.count--;
        }

        // 输出最终幸存者的编号
        linkedList_ord::list_node *print_cur = cir.head;
        for (int count = 0; count < m; ++count)
        {
            std::cout << print_cur->data << " ";
            print_cur = print_cur->next;
        }
        std::cout << std::endl;
    }

    return 0;
}