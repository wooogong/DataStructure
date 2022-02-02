#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

struct node
{
    node(int v):v(v), p(nullptr), c(nullptr), s(nullptr){}
    node(node* n):v(n->v),p(n->p), c(n->c), s(n->s){}
    node* p;
    node* c;
    node* s;
    int v;
};

struct tree
{
    tree(int v){root = create_node(v);}
    ~tree(){del_subtree(root);}

    node* root;
    node* create_node(int v)
    {
        return new node(v);
    }

    void add_child(node* p, node* c)
    {
        if(p == nullptr)
            return;

        c->p = p;

        if(p->c == nullptr)
        {
            p->c = c;
            return;
        }

        node* cur = p->c;

        while(cur->s != nullptr)
            cur = cur->s;
        cur->s = c;
    }

    node* find_node(node* n, int v)
    {
        if(n == nullptr)
            return nullptr;

        if(n->v == v)
            return n;

        node* target = find_node(n->c, v);
        if(target != nullptr)
        {
            return target;
        }

        return find_node(n->s, v);
    }

    void sw_node(node* n_1, node* n_2)
    {
        if(n_1 == n_2->p)
        {
            int v = n_1->v;
            n_1->v = n_2->v;
            n_2->v = v;
        }
        else if(n_2 == n_1->p)
        {
            int v = n_2->v;
            n_2->v = n_1->v;
            n_1->v = v;
        }
        else if(n_1->p == n_2->p)
            sw_node_1(n_1, n_2);
        else if(n_1->p != n_2->p)
            sw_node_2(n_1, n_2);
    }

    void sw_node_2(node* n_1, node* n_2)
    {
        node* p_1 = n_1->p;
        node* p_2 = n_2->p;

        if(p_1->c == n_1 && p_2->c == n_2)
        {
            node tmp1(n_1);
            node tmp2(n_2);

            p_1->c = n_2;
            p_2->c = n_1;

            n_1->s = tmp2.s;
            n_2->s = tmp1.s;

            n_1->p = tmp2.p;
            n_2->p = tmp1.p;
        }
        else if(p_1->c == n_1)
        {
            node tmp(n_2);
            p_1->c = n_2;

            node* c2 = n_2->p->c;
            while(c2->s != n_2)
                c2 = c2->s;

            n_2->s = n_1->s;
            n_2->p = n_1->p;
            n_1->s = tmp.s;
            n_1->p = tmp.p;
            c2->s = n_1;
        }
        else if(p_2->c == n_2)
        {
            node tmp(n_1);
            p_2->c = n_1;

            node* c1 = n_1->p->c;

            while(c1->s != n_1)
                c1 = c1->s;
            
            n_1->s = n_2->s;
            n_1->p = n_2->p;
            n_2->s = tmp.s;
            n_2->p = tmp.p;
            c1->s = n_2;
        }
        else
        {
            node* c1 = p_1->c;
            node* c2 = p_2->c;

            while(c1->s != n_1)
                c1 = c1->s;

            while(c2->s != n_2)
                c2 = c2->s;
            c1->s = n_2;
            c2->s = n_1;

            node tmp(n_1);
            n_1->s = n_2->s;
            n_1->p = n_2->p;
            n_2->s = tmp.s;
            n_2->p = tmp.p;
        }
    }

    void sw_node_1(node* n_1, node* n_2)
    {
        node* p = n_1->p;

        if(n_1->s == n_2)
        {
            if(p->c == n_1)
            {
                p->c = n_2;
                n_1->s = n_2->s;
                n_2->s = n_1;
            }
            else
            {
                node* c = p->c;

                while(c->s != n_1)
                    c = c->s;
                c->s = n_2;
                n_1->s = n_2->s;
                n_2->s = n_1;
            }
        }
        else if(n_2->s == n_1)
        {
            if(p->c == n_2)
            {
                p->c = n_1;
                n_2->s = n_1->s;
                n_1->s = n_2;
            }
            else
            {
                node* c = p->c;

                while(c->s != n_2)
                    c = c->s;
                c->s = n_1;
                n_2->s = n_1->s;
                n_1->s = n_2;
            }
        }
        else
        {
            if(p->c == n_1)
            {
                node tmp(n_1);
                n_1->s = n_2->s;
                n_2->s = tmp.s;
                p->c = n_2;
            }
            else if(p->c == n_2)
            {
                node tmp(n_2);
                n_2->s = n_1->s;
                n_1->s = tmp.s;
                p->c = n_1;
            }
            else
            {
                node* s1 = p->c;
                node* s2 = p->c;

                while(s1->s != n_1)
                    s1 = s1->s;

                while(s2->s != n_2)
                    s2 = s2->s;

                node tmp(n_1);
                s2->s = n_1;
                s1->s = n_2;
                n_1->s = n_2->s;
                n_2->s = tmp.s;
            }
        }
    }
    
    void del_subtree(node* n)
    {
        if(n == nullptr)
            return;

        del_subtree(n->c);
        del_subtree(n->s);

        if(n == root)
        {
            delete n;
            return;
        }

        node* p = n->p;

        if(p->c == n)
        {
            p->c = nullptr;
            delete n;
            return;
        }

        node* cur = p->c;

        while(cur->s != n)
            cur = cur->s;

        cur->s = nullptr;
        delete n;
    }

    void del_node(node* n)
    {
        if(n == nullptr)
            return;

        del_subtree(n->c);

        if(n == root)
        {
            delete n;
            return;
        }

        node* p = n->p;

        if(p->c == n)
        {
            p->c = n->s;
            delete n;
            return;
        }

        node* c = p->c;

        while(c->s != n)
            c = c->s;
        
        c->s = n->s;
        
        delete n;
    }


    void prt_tree(node* n, int step)
    {
        if(n == nullptr)
            return;

        for(int i = 0; i < step; i++)
            cout<<"  ";
        cout<<n->v<<endl;

        prt_tree(n->c, step + 1);
        prt_tree(n->s, step + 0);
    }
};

int main(void)
{
    tree t(-1);
    t.prt_tree(t.root, 0);

    t.add_child(t.find_node(t.root, -1), t.create_node(1));
    t.add_child(t.find_node(t.root, -1), t.create_node(2));
    t.add_child(t.find_node(t.root, -1), t.create_node(3));
    t.add_child(t.find_node(t.root, -1), t.create_node(4));
    t.prt_tree(t.root, 0);

    t.add_child(t.find_node(t.root, 1), t.create_node(13));
    t.add_child(t.find_node(t.root, 1), t.create_node(14));
    t.add_child(t.find_node(t.root, 1), t.create_node(15));
    t.add_child(t.find_node(t.root, 1), t.create_node(16));
    t.prt_tree(t.root, 0);
    
    t.add_child(t.find_node(t.root, 2), t.create_node(23));
    t.add_child(t.find_node(t.root, 2), t.create_node(24));
    t.add_child(t.find_node(t.root, 2), t.create_node(25));
    t.add_child(t.find_node(t.root, 2), t.create_node(26));
    t.prt_tree(t.root, 0);

    t.add_child(t.find_node(t.root, 23), t.create_node(234));
    t.add_child(t.find_node(t.root, 23), t.create_node(235));
    t.add_child(t.find_node(t.root, 23), t.create_node(236));
    t.prt_tree(t.root, 0);

    t.sw_node(t.find_node(t.root, 23), t.find_node(t.root, 24));
    t.prt_tree(t.root, 0);
    
    t.sw_node(t.find_node(t.root, 24), t.find_node(t.root, 2));
    t.prt_tree(t.root, 0);
    
    t.sw_node(t.find_node(t.root, 234), t.find_node(t.root, 25));
    t.prt_tree(t.root, 0);
    

    t.del_subtree(t.find_node(t.root, 1));
    t.prt_tree(t.root, 0);

    return 0;
}
