#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; if(!(cin>>n)) return 0;
    vector<int> L(n+1,-1), R(n+1,-1), parent(n+1,0);
    for(int i=1;i<=n;i++){
        int a,b;cin>>a>>b;L[i]=a;R[i]=b; if(a!=-1) parent[a]=i; if(b!=-1) parent[b]=i;
    }
    int root=1; for(int i=1;i<=n;i++){ if(parent[i]==0){ root=i; break; } }

    // compute depths via BFS
    vector<int> depth(n+1,0);
    if(root!=-1){
        queue<int> q; depth[root]=1; q.push(root);
        while(!q.empty()){
            int u=q.front(); q.pop();
            if(L[u]!=-1){ depth[L[u]]=depth[u]+1; q.push(L[u]); }
            if(R[u]!=-1){ depth[R[u]]=depth[u]+1; q.push(R[u]); }
        }
    }

    auto inorder = [&](int start){
        vector<int> res; res.reserve(n);
        vector<int> st; st.reserve(n);
        int cur=start;
        while(cur!=-1 || !st.empty()){
            while(cur!=-1){ st.push_back(cur); cur=L[cur]; }
            cur=st.back(); st.pop_back();
            res.push_back(cur);
            cur=R[cur];
        }
        return res;
    };

    int t; cin>>t;
    for(int qi=0; qi<t; ++qi){
        int k; cin>>k;
        for(int i=1;i<=n;i++) if(depth[i] && depth[i]%k==0) swap(L[i],R[i]);
        auto res = inorder(root);
        for(size_t i=0;i<res.size();++i){
            cout<<res[i];
            if(i+1<=res.size()) cout<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
