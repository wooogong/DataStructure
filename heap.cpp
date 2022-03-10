#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

struct heap
{
    heap(int size):root(1), len(0), buf(new int[size]){}

    void swap(int idx_a, int idx_b)
    {
        int tmp = buf[idx_a];
        buf[idx_a] = buf[idx_b];
        buf[idx_b] = tmp;
    }

    void push(int v)
    {
        buf[++len] = v;
        upheap(len);
    }

    void upheap(int n)
    {
        int p = n/2;

        if(p < 1) return ;

        if(buf[p] < buf[n])
            return;
        swap(p, n);
        upheap(p);
    }

    void downheap(int n)
    {
        int l = n*2+0;
        int r = n*2+1;

        if(l > len) return;

        if(r > len)
        {
            if(buf[l] < buf[n])
                swap(l, n);
            downheap(l);
            return;
        }

        if(r <= len)
        {
            int lower = buf[r] < buf[l] ? r : l;
            int bigger = buf[r] < buf[l] ? l : r;

            if(buf[lower] > buf[n]) return ;

            if(buf[lower] < buf[n]) 
            {
                swap(lower, n);
                downheap(lower);
            }
            else if(buf[bigger] < buf[n])
            {
                swap(bigger, n);
                downheap(bigger);
            }
        }
    }

    int pop(void)
    {
        if(len == 0) return -10000;

        int tmp = buf[root];
        buf[root] = buf[len--];

        downheap(root);

        return tmp;
    }

    void prt_heap(int n, int step)
    {
        if(n > len) return;

        for(int i = 0; i < step; i++)
            cout<<"  ";
        cout<<buf[n]<<endl;
        
        prt_heap(n*2+0, step+1);
        prt_heap(n*2+1, step+1);
    }


    int root;
    int len;
    int* buf;
};

int main(void)
{
    srand(time(nullptr));

    heap h(100);

    for(int i = 0; i < 10; i++)
    {
        int tmp = rand()%100;
        cout<<tmp<<"  ";
        h.push(tmp);
    }
    cout<<endl;

    h.prt_heap(h.root, 0);

    for(int i = 0; i < 12; i++)
        cout<<h.pop()<<endl;

    return 0;
}
