#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

struct node
{
    node(int v):prev(nullptr), next(nullptr), v(v){}
    node(node* n):prev(n->prev), next(n->next), v(n->v){}
    node* prev;
    node* next;
    int v;
};

struct dll
{
    dll():head(new node(-1)), tail(new node(-100)){
        head->next = tail;
        tail->prev = head;
    }
    ~dll(){del_list();}

    node* head;
    node* tail;

    node* create_node(int v)
    {
        return new node(v);
    }

    void append_node(node* n)
    {
        if(head->next == tail)
        {
            head->next = n;
            n->prev = head;
            n->next = tail;
            tail->prev = n;
            return;
        }

        node* cur = head->next;

        if(cur->v > n->v)
        {
            n->next = cur;
            cur->prev = n;
            head->next = n;
            n->prev = head;
            return;
        }

        while(cur != tail)
        {
            if(cur->v > n->v)
            {
                node* prev = cur->prev;

                n->prev = prev;
                n->next = cur;
                prev->next = n;
                cur->prev = n;
                return;
            }
            cur = cur->next;
        }

        node* prev = tail->prev;

        prev->next = n;
        n->prev = prev;
        n->next = tail;
        tail->prev = n;
    }

    node* find_node(int v)
    {
        node* cur =  head->next;

        while(cur != tail)
        {
            if(cur->v == v)
                return cur;
            cur = cur->next;
        }

        return nullptr;
    }

    void del_node(node* n)
    {
        if(n == nullptr)
            return;

        node* cur = head->next;

        while(cur != tail)
        {
            if(cur == n)
            {
                node* prev = n->prev;
                node* next = n->next;

                prev->next = next;
                next->prev = prev;
                delete n;
                return;
            }
            cur = cur->next;
        }
    }

    void del_list(void)
    {
        while(head->next != tail)
        {
            del_node(head->next);
        }

        delete head;
        delete tail;
        head = tail = nullptr;
    }

    void prt_node(node* n)
    {
        if(n == tail)
            return;

        cout<<n->v<<" ";

        prt_node(n->next);
    }
};


int main(void)
{
    srand(time(NULL));

    dll dl;

    for(int i = 0; i < 10; i++)
    {
        int tmp  = rand()%100;
        cout<<tmp<<" ";
        dl.append_node(dl.create_node(tmp));
    }
    cout<<endl;

    dl.prt_node(dl.head->next);
    cout<<endl;

    dl.del_node(dl.head->next);
    dl.prt_node(dl.head->next);
    cout<<endl;

    dl.del_node(dl.head->next->next);
    dl.prt_node(dl.head->next);
    cout<<endl;

    dl.del_node(dl.tail->prev);
    dl.prt_node(dl.head->next);
    cout<<endl;

    return 0;
}
