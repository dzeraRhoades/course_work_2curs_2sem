#pragma once
template<typename T1, typename T2>
class Node
{
public:
    Node()
    {
        right = nullptr;
        left = nullptr;
        
    }
public:
        T1 key;
        T2 value;
        Node* right;
        Node* left;
        
};



