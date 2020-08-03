#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false),cin.tie(0)
#define ll long long
#define prl pair<ll,ll>
#define pri pair<int,int>
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define sz(x) ((int)(x).size())
#define fi first
#define se second
#define db double
#define N 1000005
#define mod 1000000007
#define INF 1000000000
#define eps 1e-8
#define pi  3.141592653589793
using namespace std;
mt19937 mrand(random_device{}());
uniform_int_distribution<ll> dist(0, 100000000);
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll qpow(ll a, ll b) { ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)res = res * a % mod; a = a * a % mod; }return res; }
struct qandn {
	int low, high, x1, x2, id;
	bool operator <(qandn& b) { return low < b.low || low == b.low && id < b.id; }
}c[2 * N];
bool ans[N];

struct nodes {
	int v, ls, rs;
}node[20 * N];
int ncnt = 1;
void Insert(int id, int cur, int l, int r) {
	if (l == r) {
		node[cur].v = max(c[id].high, node[cur].v);
		return;
	}
	int mid = l + r >> 1;
	if (mid >= c[id].x1) {
		if (!node[cur].ls) {
			node[cur].ls = ++ncnt;
			node[ncnt].v = -INF;
		}
		Insert(id, node[cur].ls, l, mid);
	}
	else {
		if (!node[cur].rs) {
			node[cur].rs = ++ncnt;
			node[ncnt].v = -INF;
		}
		Insert(id, node[cur].rs, mid + 1, r);
	}
	node[cur].v = max(node[node[cur].rs].v, node[node[cur].ls].v);
	return;
}

int query(int L, int R, int cur, int l, int r) {
	if (l > R || r < L || L>R || !cur)return -INF;
	if (l >= L && r <= R)return node[cur].v;
	int mid = l + r >> 1;
	return max(query(L, R, node[cur].ls, l, mid), query(L, R, node[cur].rs, mid + 1, r));
}


int main() {
	IOS;
	int n, q;
	cin >> n >> q;
	rep(i, 1, n + 1) {
		int y, r;
		cin >> c[i].x1 >> y >> r;
		c[i].low = y - r, c[i].high = y + r, c[i].x2 = 0;
		c[i].id = -1;
	}
	rep(i, n + 1, n + q + 1) {
		int y;
		cin >> c[i].x1 >> y >> c[i].x2 >> y >> c[i].low >> c[i].high;
		if (c[i].x1 > c[i].x2)swap(c[i].x1, c[i].x2);
		c[i].id = i - n - 1;
	}
	sort(c + 1, c + n + q + 1);
	node[0].v = -INF;
	rep(i, 1, q + n + 1) {
		if (c[i].id == -1) {
			Insert(i, 1, -INF, INF);
		}
		else {
			int ht = query(c[i].x1, c[i].x2, 1, -INF, INF);
			if (ht < c[i].high)ans[c[i].id] = 1;
		}
	}
	rep(i, 0, q)
		if (ans[i])cout << "YES\n";
		else cout << "NO\n";
	return 0;
}

