#pragma once
#include"Tree.h"
//#include"CmpForInt.h"
#include"tree_exception.h"
#include"SearchBinaryTree.h"

#define avl_cast dynamic_cast<AVL_Node*>


template <class T1, class T2>
class AVL :
    public sbt<T1, T2>
{
private:
    class AVL_Node : public sbt<T1, T2>::Node
    {   
    public:
        AVL_Node()
        {
            BF = 0;
        }
        void assign(const typename sbt<T1, T2>::Node* nd) override
        {
            const AVL_Node* tmp = dynamic_cast<const AVL_Node*>(nd);
            this->key = tmp->key;
            this->value = tmp->value;
            this->BF = tmp->BF;
        }
    public:
        
        int BF;
    
    };

public:
    AVL(const Cmp<T1>* cmp) :sbt<T1, T2>(cmp, new Append_class(this), new Errase_class(this), new Find_class(this))
    {
       
    }
    AVL(const AVL<T1, T2>& tree) : sbt<T1, T2>(tree)
    {
        
    }
    ~AVL()
    {
        
    }
    std::vector<T2> getVector()
    {
        if (this->top == nullptr)
            return std::vector<T2>();
        std::stack<typename sbt<T1, T2>::Node*> nodeStack;
        std::vector<T2> resVec;
        nodeStack.push(this->top);

        while (!nodeStack.empty())
        {
            typename sbt<T1, T2>::Node* cur = nodeStack.top();
            nodeStack.pop();
            resVec.push_back(cur->value);
            if (cur->left != nullptr)
            {
                nodeStack.push(cur->left);
            }
            if (cur->right != nullptr)
            {
                nodeStack.push(cur->right);
            }
        }
        return resVec;
    }
    
private:
    void copyConstructor() override
    {
        this->append_obj = new Append_class(this);
        this->errase_obj = new Errase_class(this);
        this->find_obj = new Find_class(this);
    }
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    

    
    class Append_class : public sbt<T1, T2>::Append_class
    {
    public:
        Append_class(AVL<T1, T2>* obj)
        {
            this->obj = obj;
        }
        int operator()(const T1& key, const T2& value) override
        {
            return _append(key, value);
        }
    protected:
        AVL<T1, T2>* obj;
        int _append(const T1& key, const T2& value) override
        {
            std::stack<typename sbt<T1, T2>::Node*> stack;
            AVL_Node* S;// контроль узла для балансировки
            AVL_Node* P; // продвижение
           
            AVL_Node* T; // родительский узел для S
            int a;


            if (obj->top == nullptr)
            {
                obj->top = new AVL_Node;
                obj->top->value = value;
                obj->top->key = key;
                return 0;
            }

            
            int dir = obj->downhill(stack, key);
            P = dynamic_cast<AVL_Node*>(stack.top());
            //stack.pop();
            if (dir == 1)
            {
                P->right = new AVL_Node;
                P->right->value = value;
                P->right->key = key;
            }
            else if (dir == -1)
            {
                P->left = new AVL_Node;
                P->left->value = value;
                P->left->key = key;
            }
            else
                P->value = value;
            
            //stack.push(P);
           // P = S;
            do
            {
                if (stack.empty())
                    break;
                P = dynamic_cast<AVL_Node*>(stack.top());
                stack.pop();
                if (obj->cmp->compare(key, P->key) == -1)
                    P->BF -= 1;
                
                else if (obj->cmp->compare(key, P->key) == 1)
                    P->BF += 1;

            } while (abs(P->BF) == 1);
            
            if (stack.empty())
                T = P;
            else
                T = dynamic_cast<AVL_Node*>(stack.top());
            /*if (abs(S->BF) == 1)
                obj->deepness++;*/

            if (P == dynamic_cast<AVL_Node*>(T->right))
                T->right = obj->balance(P);
            else if (P == dynamic_cast<AVL_Node*>(T->left))
                T->left = obj->balance(P);
            else
                obj->top = obj->balance(P);

            return 0;
        }
    };
    
    class Errase_class : public sbt<T1, T2>::Errase_class
    {
    public:
        Errase_class(AVL<T1, T2>* obj) : sbt<T1, T2>::Errase_class(obj)
        {
            this->obj = obj;
        }
        int operator()(const T1& key) override
        {
            return _errase(key);
        }
    protected:
        AVL<T1, T2>* obj;
        int _errase(const T1& key) override
        {
            AVL_Node* tmp, * tmp_2, * tmp_3;
            T1 deleted_key = key;
            AVL_Node* S, * R, * P, * T;
            tmp = dynamic_cast<AVL_Node*>(obj->top);
            tmp_2 = tmp;
            tmp_3 = nullptr;
            T = tmp;
            S = tmp;
            P = tmp;
            std::stack<typename sbt<T1, T2>::Node*> stack;

            int a = 0;
            int cur_bf = 0;

            if (tmp == nullptr)
                throw typename sbt<T1, T2>::errase_error();
           
            if (obj->downhill(stack, key))
                throw typename sbt<T1, T2>::errase_error();
            tmp = dynamic_cast<AVL_Node*>(stack.top());
            stack.pop();
            if (!stack.empty())
                tmp_2  = dynamic_cast<AVL_Node*>(stack.top());
            else
                tmp_2 = tmp;
            stack.push(tmp);

           
            this->deleting(stack, tmp, tmp_2);
            deleted_key = stack.top()->key;
            delete stack.top();
            stack.pop();

            do
            {
                if (stack.empty())
                    break;
                P = dynamic_cast<AVL_Node*>(stack.top());
                stack.pop();
                cur_bf = P->BF;
                
                if (obj->cmp->compare(deleted_key, P->key) == 0)
                    P->BF -= 1;

                else if (obj->cmp->compare(key, P->key) == -1)
                    P->BF += 1;

                else if (obj->cmp->compare(key, P->key) == 1)
                    P->BF -= 1;
                if (abs(P->BF) == 2)
                {
                    if (P->BF == 2)
                    {
                        if (avl_cast(P->right)->BF == 0)
                            cur_bf = 0; // просто чтоб выйти из цикла, семантики не несёт
                    }
                    else
                    {
                        if (avl_cast(P->left)->BF == 0)
                            cur_bf = 0; // просто чтоб выйти из цикла, семантики не несёт
                    }
                    if (!stack.empty())
                    {
                        T = dynamic_cast<AVL_Node*>(stack.top());
                        if (T->right == P)
                            T->right = obj->balance(P);
                        else
                            T->left = obj->balance(P);
                    }
                    else
                        obj->top = obj->balance(P);
                }

            } while (abs(cur_bf) == 1);
            
            

            return 0;
        }
    };

    class Find_class : public sbt<T1, T2>::Find_class
    {
    public:
        Find_class(AVL<T1, T2>* obj)
        {
            this->obj = obj;
        }
        T2 operator()(const T1& key) override
        {
            return _find(key);
        }
    protected:
        AVL<T1, T2>* obj;
        T2 _find(const T1& key) override
        {

            AVL_Node* tmp = dynamic_cast<AVL_Node*>(obj->top);
            while (1)
            {
                if (tmp == nullptr)
                    throw sbt<T1, T2>::find_error();
                switch (obj->cmp->compare(key, tmp->key))
                {
                case 1:
                    tmp = avl_cast(tmp->right);
                    break;
                case -1:
                    tmp = avl_cast(tmp->left);
                    break;
                case 0:
                    return tmp->value;
                default:
                    break;
                }
            }
        }
    };
    
    

    AVL_Node* balance(AVL_Node* S)
    {
        AVL_Node* R;
        AVL_Node* P;
        P = nullptr;
        int a;

        if (S->BF == -2)
            a = -1;
        else if (S->BF == 2)
            a = 1;
        else
            return S;

        R = avl_cast(this->Link(a, S));
        if (R->BF != -a)
        {
            P = R;
            this->Link(a, S) = this->Link(-a, R);
            this->Link(-a, R) = S;
            if (R->BF == 0)
            {
                S->BF = a;
                R->BF = -a;
            }
            else
            {
                S->BF = 0;
                R->BF = 0;
            }
        }
        else if (R->BF == -a)
        {
            P = avl_cast(this->Link(-a, R));
            this->Link(-a, R) = this->Link(a, P);
            this->Link(a, P) = R;
            this->Link(a, S) = this->Link(-a, P);
            this->Link(-a, P) = S;
            if (P->BF == a)
            {
                P->BF = 0;
                S->BF = -a;
                R->BF = 0;
            }
            else if (P->BF == 0)
            {
                S->BF = 0;
                R->BF = 0;
            }
            else if (P->BF == -a)
            {
                P->BF = 0;
                S->BF = 0;
                R->BF = a;
            }
        }
        return P;
    }
};



