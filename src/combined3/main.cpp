#include "head.h"
int main()
{

    // 尽量不要一个个删吧，用for循环数到了再删
    //  while (true)
    //  {
    //      if (cir.count == m)
    //      {
    //          break;
    //      }
    //      // count++;
    //      // 删人
    //      // 要注意如果删掉的是头节点需要更改，因为print依赖头节点
    //      if (count == k - 1)
    //      {
    //          linkedList_ord::list_node *del = cur->next;
    //          // if (del != cir.head)
    //          // {
    //          //     cur->next = cur->next->next;
    //          //     delete del;
    //          //     cir.count--;
    //          // }
    //          // else
    //          // {
    //          //     cir.head = cur;
    //          cur->next = cur->next->next;
    //          delete del;
    //          cir.count--;
    //          // }
    //      }
    //      else
    //      {
    //          count++;
    //          cur = cur->next;
    //      }
    //      if (count == k)
    //      {
    //          count %= k;
    //      }
    //      // 不管删不删人都移动是错的
    //      // 否则原本应该报1的cur的下一个人会被删掉
    //      //  cur = cur->next;
    //  }
    //  cir.print();
    //  因为改成循环链表了所以不要用print输出

    // std::vector<int> test1 = {1, 2, 3, 4, 5};
    // Queue q(test1);
    // Stack st;
    // int sort_count = 0;
    // // get(q, st, pop, ins, sort_count);
    // get(q, st, sort_count);
    // std::cout << sort_count;
    int n, k, m;
    std::cin >> n >> k >> m; // n个人，报数k，剩下m个人
    std::vector<int> people(n, 0);
    for (int i = 1; i <= n; i++)
    {
        people[i - 1] = i;
    }
    linkedList_ord cir(people);

    // 太愚蠢了，不应该拉入哨兵节点
    linkedList_ord::list_node *del = cir.head;
    cir.head = cir.head->next;
    cir.end->next = cir.head;
    cir.loop_change = true;
    linkedList_ord::list_node *cur = cir.end; // 类似于引入虚拟头节点
    delete del;
    while (cir.count > m)
    {
        for (int i = 1; i < k; i++)
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
        // 下一轮开始前，cur不应该停留在这个被删节点的前驱节点
        // 它应该站在被删节点原本的位置
    }
    cur = cir.head;
    while (m--)
    {
        std::cout << cur->data << " ";
        cur = cur->next;
    }
}