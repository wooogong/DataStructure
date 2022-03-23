#include<iostream>
#include<algorithm>
#include<queue>
#include<utility>

using namespace std;

struct node
{
    int s, e, v;

    bool operator <(node& n)
    {
        return (this->v < n.v);
    }
};

int mst_val;

int find_root(int n, int* root_map)
{
    if(n == root_map[n]) 
        return root_map[n];

    root_map[n] = find_root(root_map[n], root_map);

    return root_map[n];
}

void update_root(int a, int b, int* root_map)
{
    int root_a = find_root(a, root_map);
    int root_b = find_root(b, root_map);

    root_map[root_b] = root_a;
}

int main(void)
{
    node path[] = {{0,1,9}, {0,2,10}, {1,3,10}, 
                    {1,4,5}, {1,6,3}, {2,3,9}, 
                    {2,4,7}, {2,5,2}, {3,5,4}, 
                    {3,6,8}, {4,6,1}, {5,6,6}};

    int root_map[sizeof(path)/sizeof(path[0])];

    queue<pair<int, int> > q;

    for(int i = 0; i < sizeof(path)/sizeof(path[0]); i++)
        root_map[i] = i;

    sort(path, path+sizeof(path)/sizeof(path[0]));
    
    for(int i = 0; i < sizeof(path)/sizeof(path[0]); i++)
        cout<<path[i].v<<endl;
    cout<<endl;

    for(int i = 0; i < sizeof(path)/sizeof(path[0]); i++)
    {
        int s = path[i].s;
        int e = path[i].e;
        int v = path[i].v;

        if(find_root(s, root_map) == find_root(e, root_map))
            continue;

        update_root(s, e, root_map);
        q.push(make_pair(s,e));
        mst_val += v;
    }

    while(!q.empty())
    {
        pair<int, int> p = q.front();
        q.pop();
        cout<<p.first<<" "<<p.second<<endl;
    }

    cout<<mst_val<<endl;

    return 0;
}
