//  есаев ¬. ». ћ8ќ-111Ѕ-20 Ћабораторна€ номер 8 второй семестр
#pragma once
#include<iostream>
#include "Cmp.h"
//#include"Node.h"
#include<vector>
#include"Tree.h"
#include<string>
#include<stack>

#define sbt SearchBinaryTree

//#include"tree_exception.h"
template<class T1, class T2>
class SearchBinaryTree : public Tree<T1, T2>
    
{
protected:
    class Node
    {
    public:
        Node()
        {
            right = nullptr;
            left = nullptr;

        }
        virtual ~Node(){}
        virtual void assign(const Node* nd)
        {
            this->key = nd->key;
            this->value = nd->value;
        }
    public:
        T1 key;
        T2 value;
        Node* right;
        Node* left;

    };

    class Errase_class;
    class Append_class;
    class Find_class;

    SearchBinaryTree(const Cmp<T1>* cmp, Append_class* _append, Errase_class* _errase, Find_class* _find)
    {
        append_obj = _append;
        errase_obj = _errase;
        find_obj = _find;

        this->cmp = cmp;
        top = nullptr;
    }

    
protected:
    Node* top;
    const Cmp<T1>* cmp;
    Append_class* append_obj;
    Errase_class* errase_obj;
    Find_class* find_obj;
    

public:
    SearchBinaryTree& operator+=(const std::pair<const T1& , const T2&>& kv)
    {
        append(kv);
        return *this;
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    virtual SearchBinaryTree& operator=(const SearchBinaryTree<T1, T2>& tree)
    {
        if(top != nullptr)
            clean(top);
        top = copy(this->top, tree.top);
        return *this;
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    virtual SearchBinaryTree& operator-=(const T1& key)
    {
        errase(key);
        return *this;
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    //virtual SearchBinaryTree& operator*=(const T1& key, const T2& value)
    //{
    //    //insert(new_node);
    //    return *this;
    //}
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    /*int clean()
    {
        if (top == nullptr)
            return 0;
        clean(top);
        top = nullptr;
        return 0;
    }*/
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    SearchBinaryTree(const SearchBinaryTree<T1, T2>& tree)
    {
        cmp = tree.cmp;
        this->copyConstructor();
        copy(tree.top, this->top);
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    SearchBinaryTree(const Cmp<T1>* cmp)
    {
        append_obj = new Append_class(this);
        errase_obj = new Errase_class(this);
        find_obj = new Find_class(this);
        this->cmp = cmp;
        top = nullptr;
    }
    virtual ~SearchBinaryTree()
    {
        delete append_obj;
        delete errase_obj;
        delete find_obj;

        if(top != nullptr)
            clean(top);
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    T2 operator[](const T1& key) 
    {
        return find(key);
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
public:
    virtual void prefix(void (*Foo)(T1& ,T2& , int& ))
    {
        _prefix(Foo, top);
        return;
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    virtual void infix(void (*Foo)(T1& key, T2& value, int&))
    {
        _infix(Foo, top);
        return;
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    virtual void postfix(void (*Foo)(T1& key, T2& value, int&))
    {
        _postfix(Foo, top);
        return;
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    void append(const std::pair<const T1&, const T2&>& node) override
    {
        (*append_obj)(node.first, node.second);
        return;
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    void errase(const T1& key) override
    {
        (*errase_obj)(key);
        return;
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    T2 find(const T1& key) override
    {
        return (*find_obj)(key);
    }
    
protected:
    SearchBinaryTree(){}
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    virtual void copyConstructor()
    {
        append_obj = new Append_class(this);
        errase_obj = new Errase_class(this);
        find_obj = new Find_class(this);
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
   
    //------------------------------------------------------------------------------------------------------
    // декорируемый метод получени€ значени€ по ключу
    //------------------------------------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------------------------------
    // декорируемый метод перегруженного оператора присваивани€
    //------------------------------------------------------------------------------------------------------
    
    
   
    
    //------------------------------------------------------------------------------------------------------
    // декорируемый перегруженным оператором += метод добавлени€ нового звена
    //------------------------------------------------------------------------------------------------------
protected:

    /*virtual Node& Top()
    {
        return top;
    }*/

    virtual Node* copy(Node* source_node, Node* dest_node)
    {
        if (source_node == nullptr)
            return dest_node;
        dest_node = new Node;
        dest_node->assign(source_node);
        dest_node->left = copy(source_node->left, dest_node->left);
        dest_node->right = copy(source_node->right, dest_node->right);
        return dest_node;
    }

    virtual void _prefix(void (*Foo)(T1&, T2&, int&), Node* cur_node, int deep = 0)
    {
        if (cur_node == nullptr)
            return;

        Foo((cur_node)->key, (cur_node)->value, deep);
        if ((cur_node)->left != nullptr)
        {
            _prefix(Foo, cur_node->left, deep + 1);
        }
        if ((cur_node)->right != nullptr)
            _prefix(Foo, cur_node->right, deep + 1);
        return;
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    virtual void _infix(void (*Foo)(T1& key, T2& value, int&), Node* cur_node, int deep = 0)
    {
        if (cur_node == nullptr)
            return;
        if ((cur_node)->left != nullptr)
            _infix(Foo, cur_node->left, deep + 1);

        Foo((cur_node)->key, (cur_node)->value, deep);

        if ((cur_node)->right != nullptr)
            _infix(Foo, cur_node->right, deep + 1);
        return;
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    virtual void _postfix(void (*Foo)(T1& key, T2& value, int&), Node* cur_node, int deep = 0)
    {
        if (cur_node == nullptr)
            return;

        if ((cur_node)->left != nullptr)
            _postfix(Foo, cur_node->left, deep + 1);

        if ((cur_node)->right != nullptr)
            _postfix(Foo, cur_node->right, deep + 1);

        Foo((cur_node)->key, (cur_node)->value, deep);

        return;
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    class Append_class
    {
    public:
        Append_class(SearchBinaryTree<T1, T2>* obj)
        {
            this->obj = obj;
        }
        virtual int operator()(const T1& key, const T2& value)
        {
            return _append(key, value);
        }
    protected:
        Append_class(){}
        SearchBinaryTree<T1, T2>* obj = nullptr;
        virtual int _append(const T1& key, const T2& value)
        {

            if (obj->top == nullptr)
            {
                obj->top = new Node;
                obj->top->key = key;
                obj->top->value = value;
                return 0;
            }
            std::stack<Node*> stack;

            //Node* tmp = obj->top;
            int dir = obj->downhill(stack, key);
            Node* tmp = stack.top();
            if (dir == 1)
            {
                tmp->right = new Node;
                tmp->right->value = value;
                tmp->right->key = key;
            }
            else if (dir == -1)
            {
                tmp->left = new Node;
                tmp->left->value = value;
                tmp->left->key = key;
            }
            else
                tmp->value = value;
        }
        
    };

    class Errase_class
    {
    public:
        Errase_class(SearchBinaryTree<T1, T2>* obj)
        {
            this->obj = obj;
        }
        virtual int operator ()(const T1& key)
        {
            return _errase(key);
        }
    protected:
        Errase_class(){}
        SearchBinaryTree<T1, T2>* obj = nullptr;
        virtual int _errase(const T1& key)
        {
            Node* tmp, * tmp_2, * tmp_3;
            tmp = obj->top;
            tmp_2 = obj->top;
            std::stack<Node*> stack;
            int a = 0;

            if (tmp == nullptr)
                throw typename sbt<T1, T2>::errase_error();
            if (obj->downhill(stack, key))
                throw typename sbt<T1, T2>::errase_error();
            tmp = stack.top();
            stack.pop();
            if (!stack.empty())
                tmp_2 = stack.top();
            else
                tmp_2 = tmp;
            stack.push(tmp);

            deleting(stack, tmp, tmp_2);
            
            delete stack.top();
            
        }
        void deleting(std::stack<Node*>& stack, Node* tmp, Node* tmp_2)
        {
            int a = 0;
            Node* tmp_3 = nullptr;
            if (tmp->right == nullptr && tmp->left == nullptr)
            {

                if (tmp_2->right == tmp)
                    tmp_2->right = nullptr;
                else if (tmp_2 == tmp)
                    obj->top = nullptr;
                else
                    tmp_2->left = nullptr;
            }
            else if ((tmp->right != nullptr) != (tmp->left != nullptr))
            {
                if (tmp->right != nullptr)
                    a = 1;
                else
                    a = -1;
                if (tmp == obj->top)
                    obj->top = obj->Link(a, tmp);
                else if (tmp_2->right == tmp)
                    tmp_2->right = obj->Link(a, tmp);
                else
                    tmp_2->left = obj->Link(a, tmp);
            }
            else if (tmp->right != nullptr && tmp->left != nullptr)
            {
                //stack.push(tmp);
                tmp_2 = tmp;
                tmp_3 = tmp_2;
                tmp = tmp->right;
                stack.push(tmp);
                while (tmp->left != nullptr)
                {
                    tmp_3 = tmp;
                    tmp = tmp->left;
                    stack.push(tmp);
                }
                if (tmp_3->right == tmp)
                    tmp_3->right = tmp->right;
                else
                    tmp_3->left = tmp->right;

                tmp_2->key = tmp->key;
                tmp_2->value = tmp->value;
            }
        }
    };

    
    class Find_class
    {
    public:
        Find_class(SearchBinaryTree<T1, T2>* obj)
        {
            this->obj = obj;
        }
        virtual T2 operator()(const T1& key)
        {
            return _find(key);
        }
    protected:
        Find_class(){}
        SearchBinaryTree<T1, T2>* obj = nullptr;
        virtual T2 _find(const T1& key)
        {
            Node* tmp = obj->top;
            while (1)
            {
                if (tmp == nullptr)
                    throw find_error();
                switch (obj->cmp->compare(key, tmp->key))
                {
                case 1:
                    tmp = tmp->right;
                    break;
                case -1:
                    tmp = tmp->left;
                    break;
                case 0:
                    return tmp->value;
                default:
                    break;
                }
            }
        }
    };
    

    

    //------------------------------------------------------------------------------------------------------
    // декорируемый оператором *= метод изменини€ значени€ звена
    //------------------------------------------------------------------------------------------------------
    /*int _insert(const Node& new_node)
    {
        Node* tmp = top;
        while (1)
        {
            switch (cmp->compare(new_node.key, tmp->key))
            {
            case 0:
                tmp->value = new_node.value;
                return 0;
                break;
            case 1:
                if (tmp->right == nullptr)
                    throw insert_error(new_node.key);
                tmp = tmp->right;
                break;
            case -1:
                if (tmp->left == nullptr)
                    throw insert_error(new_node.key);
                tmp = tmp->left;
            }
        }
    }*/
    //------------------------------------------------------------------------------------------------------
    // декорируемый оператором -= метод удалени€ элемениа по ключу
    //------------------------------------------------------------------------------------------------------
    //int _errase(const T1& key)
    //{
    //    Node* tmp = top;
    //    Node* tmp_2 = tmp;
    //   // if (!search(top, key))
    //       // throw std::exception("there is no element with this key");

    int downhill(std::stack<Node*>& stack, const T1& key)
    {
        Node* tmp = top;
        int dir = 0;
        stack.push(top);
        while (dir = cmp->compare(key, tmp->key))
        {
            switch (dir)
            {
            case 1:
                if (tmp->right == nullptr)
                    return 1;
                tmp = tmp->right;
                stack.push(tmp);
                break;
            case -1:
                if (tmp->left == nullptr)
                    return -1;
                tmp = tmp->left;
                stack.push(tmp);
                break;
            default:
                break;
            }
        }
        return 0;
    }

    //                }
    //            }
    //        }
    //        // если мы дощли до сюда значит у удал€емого узла есть либо только левое ответвелние, либо только правое.
    //        // ѕровер€ем с какой стороны мы пришли в удал€емый элемент и с какой стороны есть ответвление
    //        if (tmp->right != nullptr && (tmp_2->right == tmp || tmp_2 == tmp))
    //        {
    //            tmp_2->right = tmp->right;
    //            delete tmp;
    //            len--;
    //            return 0;
    //        }
    //        if (tmp->right != nullptr && (tmp_2->left == tmp || tmp_2 == tmp))
    //        {
    //            tmp_2->left = tmp->right;
    //            delete tmp;
    //            len--;
    //            return 0;
    //        }
    //        if(tmp->left != nullptr && (tmp_2->right == tmp || tmp_2 == tmp))
    //        {
    //            tmp_2->right = tmp->left;
    //            delete tmp;
    //            len--;
    //            return 0;
    //        }
    //        if (tmp->left != nullptr && (tmp_2->left == tmp || tmp_2 == tmp))
    //        {
    //            tmp_2->left = tmp->left;
    //            delete tmp;
    //            len--;
    //            return 0;
    //        }
    //    }
    //    
    //}
    //------------------------------------------------------------------------------------------------------
    // очищение дерева, используетс€ в деструкторе
    //------------------------------------------------------------------------------------------------------
    int clean(Node* cur_node)
    {
        
        if (cur_node->left != nullptr)
            clean(cur_node->left);
        if (cur_node->right != nullptr)
            clean(cur_node->right);
        delete cur_node;
        
        return 0;

    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    Node*& Link(int a, Node* node)
    {
        if (a == 1)
            return node->right;
        else if (a == -1)
            return node->left;
    }
    //------------------------------------------------------------------------------------------------------
    // классы исключений
    //------------------------------------------------------------------------------------------------------
public:
    class tree_exception :
        public std::exception
    {
    public:
        tree_exception(const std::string& descr)
        {
            description = descr;
        }
        tree_exception(){}
        const char* what() const noexcept
        {
            return description.c_str();
        }
        /*T1 getKey() const 
        {
            return key;
        }*/
    protected:
        //T1 key;
        std::string description;
    };

    class insert_error : public tree_exception
    {
    public:
        insert_error()
        {
           // this->key = key;
            tree_exception::description = "Insert error: the element with this key doesn't exist";
        }
    };

    class append_error : public tree_exception
    {
    public:
        append_error()
        {
            //this->key = key;
            tree_exception::description = "Append error: the element with this key already exist";
        }
    };

    class errase_error : public tree_exception
    {
    public:
        errase_error()
        {
            //this->key = key;
            tree_exception::description = "Errase error: the element with this key doesn't exist";
        }
    };

    class find_error : public tree_exception
    {
    public:
        find_error()
        {
            //this->key = key;
            tree_exception::description = "Get value error: the element with this key doesn't exist";
        }
    };

    
};

