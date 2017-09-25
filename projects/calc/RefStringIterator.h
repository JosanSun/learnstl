#pragma once

#include "RefStringBase.h"
#include <memory>

using namespace std;
using namespace cc_ref_string_base;

namespace cc_ref_string_iterator
{
    class IRefStringIterator;
    class IRefStringFindIterator;
    class RefString;
    class RefStringIterator;
    class RefStringIteratorBase;
    class RefStringIteratorDecorator;

    class LookAheadOneIterator;

    /**
    * �����ִ��ĵ�����
    * <p><i>����ǰ��</i></p>
    * @author bajdcc
    */
    class IRefStringIterator : public Object
    {
    public:
        /**
        * @return ��ǰλ��
        */
        virtual int index() = 0;

        /**
        * @return ��ǰ�ַ�
        */
        virtual char current() = 0;

        /**
        * @return ��ǰ��һ���ַ�
        */
        virtual char ahead() = 0;

        /**
        * @return �Ƿ���Լ���
        */
        virtual bool available() = 0;

        /**
        * ָ���ƶ�����һ�ַ�
        */
        virtual void next() = 0;

        ///////////////////////////////////////////////

        /**
        * �ṩ��ǰ��һ���ַ��Ĺ���
        * @return ������
        */
        virtual shared_ptr<LookAheadOneIterator> lookAhead() = 0;
    };

    /**
    * ���������࣬ʵ��װ�η���
    * @author bajdcc
    */
    class RefStringIteratorDecorator : public IRefStringIterator, public enable_shared_from_this<RefStringIteratorDecorator>
    {
    public:
        RefStringIteratorDecorator();

        shared_ptr<LookAheadOneIterator> lookAhead() override;
    };

    /**
    * �������͵��ַ���
    * @author bajdcc
    */
    class RefString : public Object, public enable_shared_from_this<RefString>
    {
    private:
        string ref;
        int start, end;

    public:
        RefString(string ref);

        int getStart() const;
        void setStart(int start);
        int getEnd() const;
        void setEnd(int end);
        void normalize();
        char charAt(int index) const;
        int length() const;

        shared_ptr<IRefStringIterator> iterator();
        shared_ptr<IRefStringIterator> reverse();
        string toString() override;
    };

    /**
    * ���׵�����
    * @author bajdcc
    */
    class RefStringIterator : public RefStringIteratorDecorator
    {
    private:
        int ptr{0};
        shared_ptr<RefString> ref;
        int length;

    public:
        RefStringIterator(shared_ptr<RefString> ref);

        int index() override;
        char current() override;
        char ahead() override;
        bool available() override;
        void next() override;
    };

    /**
    * ���������࣬ӵ���ⲿװ����
    * @author bajdcc
    */
    class RefStringIteratorBase : public RefStringIteratorDecorator
    {
    protected:
        shared_ptr<IRefStringIterator> iter;

    public:
        RefStringIteratorBase(shared_ptr<IRefStringIterator> iterator);
    };

    /**
    * �ַ����ĵ�����
    * <p>��ǰ��һλ</p>
    * @author bajdcc
    */
    class LookAheadOneIterator : public RefStringIteratorBase
    {
    private:
        char chCurrent;
        char chNext;
        int idx;

    public:
        LookAheadOneIterator(shared_ptr<IRefStringIterator> iterator);

        int index() override;
        char current() override;
        char ahead() override;
        void next() override;
        bool available() override;
    };
}
