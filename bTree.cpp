#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

struct node
{
    node(int v):p(nullptr), l(nullptr), r(nullptr),v(v){}
    node(node* n):p(n->p),l(n->l), r(n->r),v(n->v){}

    node* p;
    node* l;
    node* r;
    int v;
};

struct btree
{
    btree():root(nullptr){}
    ~btree(){del_tree(root);}

    node* root;
    node* create_node(int v)
    {
        return new node(v);
    }

    node* add_node(node* p, int v)
    {
        if(root == nullptr)
        {
            root = create_node(v);
            return root;
        }

        if(p == nullptr) 
            return create_node(v);

        if(p->v < v)
            p->r = add_node(p->r, v);
        else
            p->l = add_node(p->l, v);
        return p;
    }

    node* find_minNode(node* n)
    {
        if(n->l == nullptr)
            return n;

        return find_minNode(n->l);
    }

    node* del_case1(node* n)
    {
        delete n;
        return nullptr;
    }

    node* del_case2(node* n)
    {
        node* tmp = n->l;
        delete n;
        return tmp;
    }

    node* del_case3(node* n)
    {
        node* tmp = n->r;
        delete n;
        return tmp;
    }

    node* del_case4(node* n)
    {
        node* minNode = find_minNode(n->r);
        node* subp = n->r;

        while(subp->l != minNode)
            subp = subp->l;
        subp->l = minNode->r;

        if(minNode != n->r)
            minNode->r = n->r;
        minNode->l = n->l;

        delete n;

        return minNode;
    }

    void del_node(int v)
    {
        node* n= root;
        node* p;
        while(n->v != v)
        {
            p = n;
            if(n->v < v)
                n = n->r;
            else
                n = n->l;
        }
        
        if(n->l == nullptr && n->r == nullptr)
        {
            if(n == root)
                root = del_case1(n);
            if(p->l == n)
                p->l = del_case1(n);
            else
                p->r = del_case1(n);
        }
        else if(n->r == nullptr)
        {
            if(n == root)
                root = del_case2(n);
            else if(p->l == n)
                p->l == del_case2(n);
            else
                p->r = del_case2(n);
        }
        else if(n->l == nullptr)
        {
            if(n == root)
                root = del_case3(n);
            else if(p->l == n)
                p->l == del_case3(n);
            else
                p->r = del_case3(n);
        }
        else
        {
            if(n == root)
                root = del_case4(n);
            else if(p->l == n)
                p->l = del_case4(n);
            else
                p->r = del_case4(n);
        }
    }

    void prt_tree(node* n, int step)
    {
        if(n == nullptr) return;

        for(int i = 0; i < step; i++)
            cout<<"  ";
        cout<<n->v<<endl;

        prt_tree(n->l, step+1);
        prt_tree(n->r, step+1);
    }

    void del_tree(node* n)
    {
        if(n == nullptr) return;

        del_tree(n->l);
        del_tree(n->r);

        delete n;
    }
};
int main(void)
{
    btree bt;

    bt.add_node(bt.root, 10);
    bt.add_node(bt.root, 5);
    bt.add_node(bt.root, 15);
    bt.add_node(bt.root, 12);
    bt.add_node(bt.root, 13);
    bt.add_node(bt.root, 4);
    bt.add_node(bt.root, 7);

    bt.prt_tree(bt.root, 0);

    bt.del_node(10);
    bt.prt_tree(bt.root, 0);
    bt.add_node(bt.root, 17);
    bt.prt_tree(bt.root, 0);
    bt.add_node(bt.root, 16);
    bt.prt_tree(bt.root, 0);
    bt.del_node(15);
    bt.prt_tree(bt.root, 0);
    return 0;
}
