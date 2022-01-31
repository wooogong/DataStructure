#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

struct node
{
    node(int v):next(nullptr), v(v){}
    node(node* n):next(n->next), v(n->v){}
    node* next;
    int v;
};

struct sll
{
    sll():head(nullptr){}
    ~sll(){del_list(head);}

    node* head;

    node* create_node(int v)
    {
        return new node(v);
    };

    void append_node(node* n)
    {
        if(head == nullptr)
        {
            head = n;
            return;
        }

        node* prev = head;
        node* next = prev->next;

        if(head->v > n->v)
        {
            n->next = head;
            head= n;
            return;
        }

        while(next != nullptr)
        {
            if(next->v > n->v)
            {
                n->next = next;
                prev->next = n;
                return;
            }
            prev = next;
            next = next->next;
        }

        prev->next = n;
    }

    node* find_node(int v)
    {
        node* n = head;

        while(n != nullptr)
        {
            if(n->v == v)
                return n;
            n = n->next;
        }

        return nullptr;
    }

    void del_node(node* n)
    {
        if(n == nullptr) return;

        if(n == head)
        {
            head= n->next;
            delete n;
            return;
        }

        node* prev = head;
        node* next = prev->next;

        while(next != nullptr)
        {
            if(next == n)
            {
                prev->next = next->next;
                delete n;
                return;
            }

            prev = next;
            next = next->next;
        }
    }

    void del_sublist(node* n)
    {
        if(n == nullptr) return;

        del_sublist(n->next);

        delete n;
    }

    void del_list(node* n)
    {
        if(n == head)
        {
            del_sublist(head);
            head = nullptr;
            return;
        }

        node* prev = head;
        node* next = head->next;

        while(next != nullptr)
        {
            if(next == n)
            {
                del_node(n);
                prev->next = nullptr;
            }

            prev = next;
            next = next->next;
        }
    }

    void prt_node(node* n)
    {
        if(n == nullptr)
            return;
        cout<<n->v<<" ";
        prt_node(n->next);
    }
};

int main(void)
{
    srand(time(NULL));

    sll sl;

    for(int i = 0; i < 10; i++)
    {
        int tmp = rand()%100;
        cout<<tmp<<" ";
        sl.append_node(sl.create_node(tmp));
    }

    cout<<endl;

    sl.prt_node(sl.head);

    cout<<endl;

    return 0;
}
