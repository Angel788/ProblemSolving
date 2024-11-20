/*
  Idea pricipal_resolucion: mover un elemento lo mas que se puda hacia la derecha
  Tecnica empleada para llegar a las observaciones: Fijar una poscion y ver como interactua
  Observaciones:
  1) Si estoy en un lugar X, puedo alcanzar todos lo maximos que tengo desde 1 hasta X
     Demostracion: Si no soy el mayor en mi rango es evidente, porque puedo ir a al elemento 
     maximo porque simplemente soy menor, pero si no es porque soy el mayor o igual al mayor
   2) Para moverme mas hacia la derecha entoces debe de exitir un numero inferior a mi que 
   me lleve a el, cual seria la mejor estrategia escojer el mas hacia la derecha por el punto 1,
   porque puedo aumentar la posibilidad de encontrar algo mayor
   3) Para moverme hacia la izquierda lo mejor es usar el elemento mas grande en ese segmento, porque almenos
   es mayor a mi o soy igual ese por 1), al moverme a esa posicion tengo mas posibilidades de agarrar un elemento 
   mas a la darecha porque es mayor a mi elemento actual,con lo cual pude abarcar mas numeros menores a mi eso hace
   que existan mas posibilidades de llegar mas a la derecha, es algo simple de ver porque al menos se diferencia por x
   donde x>=0 entonces a+x hay mas rango con el cual jugar.
*/
#include <bits/stdc++.h>
using namespace std;
const int N=5e5+1;
typedef long long ll;
#define endl "\n"
ll dp[N];
ll maxr[N],pos[N];
vector<int>trans[N];
ll st[N*4+2];
void update(int l, int r, int idx, int x, int i) {
    if (l == r) {st[i] = x; return;}
    int m = l+r>>1;
    if (idx <= m) update(l, m, idx, x, i*2+1);
    else update(m+1, r, idx, x, i*2+2);
    st[i] =max (st[i*2+1] ,st[i*2+2]);
}
int query(int l, int r, int a, int b, int i) {
    if (a > r || b < l) return -1e9;
    if (a <= l && r <= b) return st[i];
    int m = l+r>>1;
    return max(query(l, m, a, b, 2*i+1), query(m+1, r, a, b, 2*i+2));
}
ll rep(int pos){
    ll &a=dp[pos];
    if(a!=-1)return a;
    a=maxr[pos];
    for(auto tran:trans[pos])a=max(a,rep(tran));
    return a;
}
void test(){
    int n;cin>>n;
    set<ll>maxe[n+1];
    vector<ll>nums(n+1);
    for(int i=1;i<=n;i++){
        ll a;cin>>nums[i];
        pos[i]=0;
        maxe[nums[i]].insert(i);
        maxr[i]=max(maxr[i-1],nums[i]);
        dp[i]=-1;
        if(nums[i]>maxr[i-1])maxr[i]=nums[i],pos[i]=i;
        else maxr[i]=maxr[i-1],pos[i]=pos[i-1];
        trans[i].clear();
    }
    for(int i=0;i<=n;i++){
        update(0,n,i,(maxe[i].size()?*maxe[i].rbegin():0),0);
    }
    for(int i=1;i<=n;i++){
        int a=nums[i];
        maxe[a].erase(maxe[a].find(i));
        update(0,n,a,(maxe[a].size()?*maxe[a].rbegin():0),0);
        trans[i].push_back(query(0,n,0,a-1,0));
        if(pos[i]!=i)trans[i].push_back(pos[i]);
    }
    for(int i=1;i<=n;i++){
        if(dp[i]==-1)rep(i);
        cout<<dp[i]<<" ";
    }
    cout<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;cin>>t;
    while(t--)test();
    return 0;
}