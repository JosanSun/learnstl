#ifndef __STD_VECTOR_H
#define __STD_VECTOR_H

#include "memory.h"

namespace clib
{
    namespace collections
    {
        using namespace type;

        namespace vector_config
        {
            // ���ռ�
            static const size_t FULL_SIZE = 0x100000;
            // �����ڴ��
            static memory::memory_pool<FULL_SIZE> mem;

            // Ĭ��������
            static const size_t DEF_SIZE = 0x10;
            // Ĭ�ϵ�������
            static const size_t ACC_SIZE = 0x10;
        }

        // �������䳤���飩
        template<class T>
        class vector
        {
            using data_t = T;

            size_t capacity; // ���пռ�
            size_t used; // ���ÿռ�
            size_t acc; // ÿ�ε�����С

            data_t *data; // ����

            void extend()
            {
                capacity += acc;
                // ע�⣺��������ʱ��ԭ������ʧЧ��
                data = vector_config::mem.realloc(data, capacity);
            }

        public:

            vector()
                : capacity(vector_config::DEF_SIZE)
                , used(0)
                , acc(vector_config::ACC_SIZE)
            {
                data = vector_config::mem.alloc_array<data_t>(capacity);
            }

            // �����Ԫ����ĩβ
            void push(T&& obj)
            {
                if (used >= capacity)
                {
                    extend();
                }
                data[used++] = obj; // T���͵ĸ�ֵ����
            }

            // ����ĩβ��Ԫ��
            T&& pop()
            {
                if (used == 0)
                    throw "Empty vector";
                return std::forward<T>(data[--used]); // ������ֵ����
            }

            // ��ȡԪ��
            T&& get(size_t index) const
            {
                if (index >= used)
                    throw "Invalid index";
                return std::forward<T>(data[index]); // ������ֵ����
            }

            // ��ȡ��ĩβԪ��
            T&& top() const
            {
                return get(used - 1);
            }

            // �õ���С
            size_t size() const
            {
                return used;
            }
        };
    }
}

#endif
