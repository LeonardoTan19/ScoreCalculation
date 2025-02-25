// Last update: 2025-2-16 BY 谭铭辉
#ifndef _LIST_H_
#define _LIST_H_
// TYPE提供链表数据类型的非指针，CMP提供比较默认函数(推荐满足-1,0,1)三种取值
#include <stdlib.h>
#include "prehead.h"
#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) ({ \
    const typeof( ((type *)0)->member ) *__mptr = (ptr); \
    (type *)( (char *)__mptr - offsetof(type,member) ); })

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
    /*遍历链表并对每个结点进行func操作*/                                                             \
    static inline void Type##List##_ForEach(Type##List list, void (*func)(Type))                     \
    {                                                                                                \
        Type##Node *cur = list->head;                                                                \
        while (cur)                                                                                  \
        {                                                                                            \
            func(cur->data);                                                                         \
            cur = cur->next;                                                                         \
        }                                                                                            \
    }                                                                                                \
    /*交换两个结点*/                                                                                 \
    static inline void Type##List##_Swap(Type##List list, int index1, int index2)                    \
    {                                                                                                \
        Type##Node *cur1 = list->head;                                                               \
        Type##Node *cur2 = list->head;                                                               \
        while (index1--)                                                                             \
            cur1 = cur1->next;                                                                       \
        while (index2--)                                                                             \
            cur2 = cur2->next;                                                                       \
        Type temp = cur1->data;                                                                      \
        cur1->data = cur2->data;                                                                     \
        cur2->data = temp;                                                                           \
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
    /*反转链表*/                                                                                     \
    static void Type##List##_Reverse(Type##List list)                                                \
    {                                                                                                \
        Type##Node *cur = list->head;                                                                \
        Type##Node *pre = NULL;                                                                      \
        while (cur)                                                                                  \
        {                                                                                            \
            Type##Node *next = cur->next;                                                            \
            cur->next = pre;                                                                         \
            pre = cur;                                                                               \
            cur = next;                                                                              \
        }                                                                                            \
        list->head = pre;                                                                            \
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
