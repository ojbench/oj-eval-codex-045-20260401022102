#include <iostream>
#include <cstdio>

// Only iostream/cstdio are allowed per problem statement.

// We simulate an elevator with requests on floors [0, 1e9].
// Maintain two heaps:
//  - up-heap (min-heap) for requests strictly above current floor
//  - down-heap (max-heap) for requests strictly below current floor
// For cancel, we use lazy deletion by marking in a simple open-addressing hash set of active requests.
// Because constraints are up to 5e5 operations, custom hash is fine.

struct HashSet {
    // simple open addressing hash set for int keys (floor numbers)
    // We need up to around number of active requests (<= operations), choose capacity ~ 1<<21 (~2M) for low collision.
    // But memory must be reasonable: 2M ints ~ 8MB, plus flags. We'll choose power of two >= 2*5e5 -> 1<<20 = 1,048,576.
    // Store keys and state: 0 empty, 1 used, 2 deleted. We can avoid 'deleted' by rehashing; but we only need contains and insert/erase.
    // We'll implement: insert, erase, contains.
    static const int CAP = 1<<20; // 1,048,576
    int keys[CAP];
    unsigned char state[CAP];
    HashSet(){
        for(int i=0;i<CAP;i++) state[i]=0;
    }
    inline unsigned int h(unsigned int x) const {
        // 32-bit mix
        x ^= x >> 16; x *= 0x7feb352d; x ^= x >> 15; x *= 0x846ca68b; x ^= x >> 16;
        return x & (CAP-1);
    }
    bool contains(int x) const {
        unsigned int i = h((unsigned int)x);
        while(state[i]){
            if(state[i]==1 && keys[i]==x) return true;
            i = (i+1) & (CAP-1);
        }
        return false;
    }
    void insert(int x){
        unsigned int i = h((unsigned int)x);
        int first_del = -1;
        while(state[i]){
            if(state[i]==1 && keys[i]==x) return; // already
            if(state[i]==2 && first_del==-1) first_del = (int)i;
            i = (i+1) & (CAP-1);
        }
        if(first_del!=-1){ i = (unsigned int)first_del; }
        keys[i]=x; state[i]=1;
    }
    void erase(int x){
        unsigned int i = h((unsigned int)x);
        while(state[i]){
            if(state[i]==1 && keys[i]==x){ state[i]=2; return; }
            i = (i+1) & (CAP-1);
        }
    }
};

struct MinHeap {
    // for up requests (min-heap)
    static const int N = 600000; // sufficient for operations
    int a[N]; int sz;
    MinHeap():sz(0){}
    void push(int x){ a[++sz]=x; int i=sz; while(i>1){ int p=i>>1; if(a[p]<=a[i]) break; int t=a[p]; a[p]=a[i]; a[i]=t; i=p; } }
    int top(){ return a[1]; }
    void pop(){ if(sz==0) return; a[1]=a[sz--]; int i=1; while(true){ int l=i<<1, r=l+1, s=i; if(l<=sz && a[l]<a[s]) s=l; if(r<=sz && a[r]<a[s]) s=r; if(s==i) break; int t=a[i]; a[i]=a[s]; a[s]=t; i=s; }
    }
    bool empty() const { return sz==0; }
};

struct MaxHeap {
    // for down requests (max-heap)
    static const int N = 600000;
    int a[N]; int sz;
    MaxHeap():sz(0){}
    void push(int x){ a[++sz]=x; int i=sz; while(i>1){ int p=i>>1; if(a[p]>=a[i]) break; int t=a[p]; a[p]=a[i]; a[i]=t; i=p; } }
    int top(){ return a[1]; }
    void pop(){ if(sz==0) return; a[1]=a[sz--]; int i=1; while(true){ int l=i<<1, r=l+1, s=i; if(l<=sz && a[l]>a[s]) s=l; if(r<=sz && a[r]>a[s]) s=r; if(s==i) break; int t=a[i]; a[i]=a[s]; a[s]=t; i=s; }
    }
    bool empty() const { return sz==0; }
};

// Place large structures in global storage to avoid stack overflow
static MinHeap g_up;
static MaxHeap g_down;
static HashSet g_active;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if(!(std::cin>>n)) return 0;

    long long cur = 0; // current floor
    int dir = 1; // 1 = up, -1 = down; initial up
    MinHeap &up = g_up;
    MaxHeap &down = g_down;
    HashSet &active = g_active; // track active requested floors

    for(int i=0;i<n;i++){
        char op[16];
        std::cin>>op;
        if(op[0]=='a' && op[1]=='d'){
            long long x; std::cin>>x;
            int xi = (int)x;
            // ignore if x equals cur (problem guarantees x != current floor when adding)
            if(!active.contains(xi)){
                active.insert(xi);
                if(xi>cur) up.push(xi);
                else if(xi<cur) down.push(xi);
            }
        }else if(op[0]=='c'){
            long long x; std::cin>>x; int xi=(int)x;
            if(active.contains(xi)){
                active.erase(xi); // lazy; leave in heap and skip when popping
            }
        }else if(op[0]=='a'){
            // execute next request following rules
            // rule (1): if no pending, do nothing
            // Clean invalid tops lazily
            while(!up.empty() && !active.contains(up.top())) up.pop();
            while(!down.empty() && !active.contains(down.top())) down.pop();

            if(dir==1){
                if(!up.empty()){
                    int t=up.top(); up.pop(); if(active.contains(t)){ active.erase(t); cur=t; }
                }else if(!down.empty()){
                    dir=-1; int t=down.top(); down.pop(); if(active.contains(t)){ active.erase(t); cur=t; }
                } // else none, do nothing
            }else{ // dir == -1
                if(!down.empty()){
                    int t=down.top(); down.pop(); if(active.contains(t)){ active.erase(t); cur=t; }
                }else if(!up.empty()){
                    dir=1; int t=up.top(); up.pop(); if(active.contains(t)){ active.erase(t); cur=t; }
                }
            }

            // After moving, we need to reclassify remaining pending floors relative to new cur? No: we decided heaps by value
            // However, requests equal to cur should not exist (we erase executed). Future adds will be compared to cur.
            // But pending items in heaps may now be on wrong side (e.g., cur increases, some previously-up become down). That's okay
            // because their numeric value relative to new cur may flip; but our heaps contain absolute floors. We must maintain that
            // up heap should contain those > current cur, and down heap those < current cur. Since cur changed, previous partition invalid.
            // To fix: we must not rely on heaps pre-partitioned by old cur. Instead we should move elements between heaps after cur changes.
            // We'll do a periodic rebalancing: after action, we lazily push elements from wrong heap when they reach the top and are on wrong side.
            // Implement: After updating cur, we will move from up->down while top <= cur, and from down->up while top >= cur, repeatedly.
            while(!up.empty() && !active.contains(up.top())) up.pop();
            while(!down.empty() && !active.contains(down.top())) down.pop();
            while(!up.empty() && up.top()<=cur){ int v=up.top(); up.pop(); if(active.contains(v)) down.push(v); }
            while(!down.empty() && down.top()>=cur){ int v=down.top(); down.pop(); if(active.contains(v)) up.push(v); }
        }else if(op[0]=='l'){
            std::cout<<cur<<"\n";
        }
    }
    return 0;
}
