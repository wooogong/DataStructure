#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

struct node
{
    node(char c, int freq): l(nullptr), r(nullptr), freq(freq), c(c){}
    node* l;
    node* r;
    char c;
    int freq;
};

struct btree
{
    btree():root(nullptr)
    {
        for(int i = 0; i < 100; i++) 
            buf[i] = 0;
    }
    ~btree(){del_tree(root);}
    node* root;
    char buf[100];

    void mk_code(node* n, int idx)
    {
        if(n == nullptr)
            return;

        if(n->c >= 'a' && n->c <= 'z')
        {
            cout<<n->c<<" "<<n->freq<<" : "<<buf<<endl;
            return;
        }

        buf[idx] = '0';
        mk_code(n->l, idx+1);
        buf[idx] = '1';
        mk_code(n->r, idx+1);
        buf[idx] = '\0';
    }

    void del_tree(node* n)
    {
        if(n == nullptr)
            return;

        del_tree(n->l);
        del_tree(n->r);

        delete n;
    }
};

struct heap
{
    heap():root(1), len(0)
    {
        for(int i = 0; i < 100; i++)
            buf[i] = nullptr;
    }
    ~heap(){del_tree();}
    int root;
    int len;
    node* buf[100];

    int getlen(void)
    {
        return len;
    }

    void push(char c, int freq)
    {
        buf[++len] = new node(c, freq);
        upheap(len);
    }

    void push(node* n)
    {
        buf[++len] = n;
        upheap(len);
    }

    void swap(int idx_a, int idx_b)
    {
        node* tmp = buf[idx_a];
        buf[idx_a] = buf[idx_b];
        buf[idx_b] = tmp;
    }

    void upheap(int n)
    {
        int p = n/2;
        if(p < 1) return;

        if(buf[p]->freq < buf[n]->freq)
            return;

        swap(p, n);
        upheap(p);
    }

    void downheap(int p)
    {
        int l = p*2+0;
        int r = p*2+1;

        if(l > len) return;
        if(r > len)
        {
            if(buf[l]->freq < buf[p]->freq)
                swap(l, p);
            return;
        }
        
        int low = buf[l]->freq < buf[r]->freq ? l: r;
        int big = low == l ? r : l;

        if(buf[low]->freq < buf[p]->freq)
        {
            swap(low, p);
            downheap(low);
        }
        else if(buf[big]->freq < buf[p]->freq)
        {
            swap(big, p);
            downheap(big);
        }
    }

    node* pop(void)
    {
        node* tmp = buf[root];
        buf[root] = buf[len--];
        buf[len+1] = nullptr;

        downheap(root);

        return tmp;
    }

    void del_tree(void)
    {
        for(int i = 0; i < sizeof(buf)/sizeof(buf[0]); i++)
            if(buf[i] != nullptr)
                delete buf[i];
    }

    void prt_tree(int n, int step)
    {
        if(n > len) return;

        for(int i = 0; i < step; i++)
            cout<<"  ";
        cout<<buf[n]->freq<<endl;

        prt_tree(n*2+0, step+1);
        prt_tree(n*2+1, step+1);
    }
};

int main(void)
{
    srand(time(NULL));

    heap h;

    for(int i = 0; i < 10; i++)
    {
        int freq = rand()%100;
        h.push('a'+i, freq);
        cout<<freq<<endl;
    }
    h.prt_tree(1, 0);

    while(h.getlen() > 1)
    {
        node* low = h.pop();
        node* big = h.pop();
        node* root = new node(-1, low->freq + big->freq);
        root->l = big;
        root->r = low;
        h.push(root);
        //h.prt_tree(1, 0);
        //cout<<endl;
        //cout<<n->c << " "<<n->freq<<endl;
    }

    node* root = h.pop();
    btree bt;

    bt.root = root;
    bt.mk_code(bt.root, 0);

    return 0;
}

