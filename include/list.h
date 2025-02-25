// Last update: 2025-2-16 BY 谭铭辉
/*
 * 链表宏说明:
 *
 * 宏 List(Type) 生成了一个通用的单向链表实现，其中：
 *   - Type##Node 为链表结点类型，包含一个数据域 (data) 和指向下一个结点的指针 (next)。
 *   - Type##List 为链表类型，实际上是指向包含头指针、尾指针和链表长度 (size) 的结构体的指针。
 *
 * 提供的函数（当 Type 被实际数据类型替换后）包括：
 *
 * 1. Type##List##_Init()
 *    - 描述：初始化一个新的链表实例。
 *    - 返回：如果内存分配成功，返回新链表；否则返回 NULL。
 *
 * 2. Type##List##_Insert_Head(list, data)
 *    - 描述：在链表头部插入一个新节点，节点中存放 data 数据。
 *    - 返回：成功时返回 SUCCESS；如果内存分配失败，则返回 MEMORY_ERROR。
 *
 * 3. Type##List##_Insert_Tail(list, data)
 *    - 描述：在链表尾部插入一个新节点，节点中存放 data 数据。
 *    - 返回：成功时返回 SUCCESS；如果内存分配失败，则返回 MEMORY_ERROR。
 *
 * 4. Type##List##_Get(list, index)
 *    - 描述：获取指定索引处的链表节点（索引从 0 开始）。
 *    - 参数：index - 目标节点的序号。
 *    - 返回：如果索引在有效范围内，返回对应节点的指针；否则返回 NULL。
 *
 * 5. Type##List##_Delete(list, index)
 *    - 描述：删除链表中指定序号的节点。
 *    - 效果：释放目标节点的内存，并更新链表的头指针或尾指针（如有必要）。
 *
 * 6. Type##List##_Size(list)
 *    - 描述：返回链表当前包含的节点个数。
 *
 * 7. Type##List##_Clear(list)
 *    - 描述：清空链表，删除所有节点但不销毁链表结构本身。
 *    - 效果：遍历链表释放每个节点的内存，并重置头指针为 NULL。
 *
 * 8. Type##List##_Destroy(list)
 *    - 描述：销毁链表，先清空所有节点，然后释放链表结构内存。
 *
 * 9. Type##List##_Sort(list, cmp)
 *    - 描述：使用提供的比较函数对链表进行排序。
 *    - 参数：cmp - 比较函数，接受两个 const Type* 参数，返回值为正值、零或负值，
 *                      分别表示第一个数据大于、等于或小于第二个数据。
 *    - 说明：排序算法采用简单的冒泡排序实现。
 *
 * 10. Type##List##_Find(list, data, cmp)
 *     - 描述：在链表中查找与给定 data 匹配的节点，并返回其索引。
 *     - 参数：
 *           data - 需要查找的数据项；
 *           cmp  - 比较函数，与排序函数中相同。
 *     - 返回：如果找到匹配的节点，返回其索引（从 0 开始）；否则返回 -1。
 *
 * 11. Type##List##_Copy(list)
 *     - 描述：复制整个链表，生成一个新的链表，其中节点数据为原链表数据（浅拷贝）。
 *     - 返回：新创建的链表。
 *
 * 12. Type##List##_Modify(list, index, data)
 *     - 描述：修改链表中指定索引节点的数据为新的 data 数据。
 *
 */

#ifndef _LIST_H_
#define _LIST_H_
// TYPE提供链表数据类型的非指针，CMP提供比较默认函数(推荐满足-1,0,1)三种取值
#include <stdlib.h>
#include "prehead.h"

#define List(Type)                                                                                   \
    /*结点*/                                                                                         \
    typedef struct Type##Node                                                                        \
    {                                                                                                \
        Type data;                                                                                   \
        struct Type##Node *next;                                                                     \
    } Type##Node;                                                                                    \
    /*链表*/                                                                                         \
    typedef struct Type##List                                                                        \
    {                                                                                                \
        Type##Node *head;                                                                            \
        Type##Node *tail;                                                                            \
        int size;                                                                                    \
    } *Type##List;                                                                                   \
    static inline Type##List Type##List##_Init()                                                     \
    {                                                                                                \
        Type##List list = (Type##List)malloc(sizeof(struct Type##List));                             \
        if (list)                                                                                    \
        {                                                                                            \
            list->size = 0;                                                                          \
            list->head = NULL;                                                                       \
            list->tail = NULL;                                                                       \
        }                                                                                            \
        return list;                                                                                 \
    }                                                                                                \
    /*头插法插入数据*/                                                                               \
    static inline int Type##List##_Insert_Head(Type##List list, Type data)                           \
    {                                                                                                \
        Type##Node *newNode = (Type##Node *)malloc(sizeof(Type##Node));                              \
        if (!newNode)                                                                                \
            return MEMORY_ERROR;                                                                     \
        newNode->data = data;                                                                        \
        newNode->next = list->head;                                                                  \
        list->head = newNode;                                                                        \
        if (list->size == 0)                                                                         \
            list->tail = newNode;                                                                    \
        list->size++;                                                                                \
        return SUCCESS;                                                                              \
    }                                                                                                \
    /*尾插法插入数据*/                                                                               \
    static inline int Type##List##_Insert_Tail(Type##List list, Type data)                           \
    {                                                                                                \
        Type##Node *newNode = (Type##Node *)malloc(sizeof(Type##Node));                              \
        if (!newNode)                                                                                \
            return MEMORY_ERROR;                                                                     \
        newNode->data = data;                                                                        \
        newNode->next = NULL;                                                                        \
        if (!list->tail)                                                                             \
        {                                                                                            \
            list->head = newNode;                                                                    \
            list->tail = newNode;                                                                    \
        }                                                                                            \
        else                                                                                         \
        {                                                                                            \
            list->tail->next = newNode;                                                              \
            list->tail = newNode;                                                                    \
        }                                                                                            \
        list->size++;                                                                                \
        return SUCCESS;                                                                              \
    }                                                                                                \
    /*查找返回对应序号的对应数据*/                                                                   \
    static inline Type##Node *Type##List##_Get(Type##List list, int index)                           \
    {                                                                                                \
        Type##Node *cur = list->head;                                                                \
        while (index-- && cur)                                                                       \
            cur = cur->next;                                                                         \
        return cur;                                                                                  \
    }                                                                                                \
    /*删除对应序号的数据*/                                                                           \
    static inline void Type##List##_Delete(Type##List list, int index)                               \
    {                                                                                                \
        if (index < 0 || index >= list->size)                                                        \
            return;                                                                                  \
        Type##Node *cur = list->head;                                                                \
        Type##Node *prev = NULL;                                                                     \
        while (index--)                                                                              \
        {                                                                                            \
            prev = cur;                                                                              \
            cur = cur->next;                                                                         \
        }                                                                                            \
        if (prev)                                                                                    \
            prev->next = cur->next;                                                                  \
        else                                                                                         \
            list->head = cur->next;                                                                  \
        if (cur == list->tail)                                                                       \
            list->tail = prev;                                                                       \
        free(cur);                                                                                   \
        list->size--;                                                                                \
    }                                                                                                \
    /*返回链表长度*/                                                                                 \
    static inline int Type##List##_Size(Type##List list)                                             \
    {                                                                                                \
        return list->size;                                                                           \
    }                                                                                                \
    /*清空链表*/                                                                                     \
    static inline void Type##List##_Clear(Type##List list)                                           \
    {                                                                                                \
        Type##Node *cur = list->head;                                                                \
        while (cur)                                                                                  \
        {                                                                                            \
            Type##Node *next = cur->next;                                                            \
            free(cur);                                                                               \
            cur = next;                                                                              \
        }                                                                                            \
        list->head = NULL;                                                                           \
    }                                                                                                \
    /*销毁链表*/                                                                                     \
    static inline void Type##List##_Destroy(Type##List list)                                         \
    {                                                                                                \
        Type##List_Clear(list);                                                                      \
        free(list);                                                                                  \
    }                                                                                                \
    /*排序链表*/                                                                                     \
    static void Type##List##_Sort(Type##List list, int (*cmp)(const Type *, const Type *))           \
    {                                                                                                \
        Type##Node *cur = list->head;                                                                \
        while (cur)                                                                                  \
        {                                                                                            \
            Type##Node *next = cur->next;                                                            \
            while (next)                                                                             \
            {                                                                                        \
                if (cmp(&cur->data, &next->data) > 0)                                                \
                {                                                                                    \
                    Type temp = cur->data;                                                           \
                    cur->data = next->data;                                                          \
                    next->data = temp;                                                               \
                }                                                                                    \
                next = next->next;                                                                   \
            }                                                                                        \
            cur = cur->next;                                                                         \
        }                                                                                            \
    }                                                                                                \
    /*查找返回对应data的序号，cmp为比较函数*/                                                        \
    static int Type##List##_Find(Type##List list, Type data, int (*cmp)(const Type *, const Type *)) \
    {                                                                                                \
        Type##Node *cur = list->head;                                                                \
        int index = 0;                                                                               \
        while (cur)                                                                                  \
        {                                                                                            \
            if (cmp(&cur->data, &data) == 0)                                                         \
                return index;                                                                        \
            cur = cur->next;                                                                         \
            index++;                                                                                 \
        }                                                                                            \
        return -1;                                                                                   \
    }                                                                                                \
    /*复制链表*/                                                                                     \
    static Type##List Type##List##_Copy(Type##List list)                                             \
    {                                                                                                \
        Type##List newList = Type##List##_Init();                                                    \
        Type##Node *cur = list->head;                                                                \
        while (cur)                                                                                  \
        {                                                                                            \
            Type##List##_Insert_Tail(newList, cur->data);                                            \
            cur = cur->next;                                                                         \
        }                                                                                            \
        return newList;                                                                              \
    }                                                                                                \
    /*修改对应序号的数据*/                                                                           \
    static inline void Type##List##_Modify(Type##List list, int index, Type data)                    \
    {                                                                                                \
        Type##Node *cur = list->head;                                                                \
        while (index--)                                                                              \
            cur = cur->next;                                                                         \
        cur->data = data;                                                                            \
    }
#endif
