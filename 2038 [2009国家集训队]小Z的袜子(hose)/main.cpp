﻿#include <cstdio>
#include <cstdarg>
#include <cctype>
#include <cmath>
#include <algorithm>
using namespace std;
void read(int n, ...)
{
	va_list li;
	va_start(li, n);
	while (n--)
	{
		int &x = *va_arg(li, int *), ch;
		x = 0;
		do ch = getchar();
		while (!isdigit(ch));
		do
		{
			x = x * 10 + ch - '0';
			ch = getchar();
		} while (isdigit(ch));
	}
	va_end(li);
}
const int N = 5e4;
int a[N], cnt[N];
pair<unsigned, unsigned> ans[N];
struct query
{
	int l, r, id, bid;
} q[N];
bool cmp_l(const query &a, const query &b) { return a.l < b.l; }
bool cmp(const query &a, const query &b) { return a.bid < b.bid || a.bid == b.bid&&a.r < b.r; }
unsigned gcd(unsigned a, unsigned b) { return b == 0 ? a : gcd(b, a%b); }
unsigned inc(int x)
{
	cnt[x]++;
	return (unsigned)cnt[x] * cnt[x] - (unsigned)(cnt[x] - 1)*(cnt[x] - 1);
}
unsigned dec(int x)
{
	cnt[x]--;
	return (unsigned)cnt[x] * cnt[x] - (unsigned)(cnt[x] + 1)*(cnt[x] + 1);
}
int main()
{
	int n, m;
	read(2, &n, &m);
	for (int i = 0; i < n; i++)
	{
		read(1, &a[i]);
		a[i]--;
	}
	for (int i = 0; i < m; i++)
	{
		read(2, &q[i].l, &q[i].r);
		q[i].l--;
		q[i].id = i;
	}
	sort(q, q + m, cmp_l);
	int s = sqrt(n);
	for (int i = 0, j = 0, k = 0; i + s <= n; i += s, j++)
		for (; q[k].l < i + s&&k < m; k++) q[k].bid = j;
	sort(q, q + m, cmp);
	unsigned ans = 0;
	int l = q[0].l, r = q[0].l;
	for (int i = 0; i < m; i++)
	{
		for (; l > q[i].l; l--) ans += inc(a[l - 1]);
		for (; r < q[i].r; r++) ans += inc(a[r]);
		for (; l < q[i].l; l++) ans += dec(a[l]);
		for (; r > q[i].r; r--) ans += dec(a[r - 1]);
		unsigned len = q[i].r - q[i].l, x = len*(len - 1), g = gcd(ans - len, x);
		::ans[q[i].id] = make_pair((ans - len) / g, x / g);
	}
	for (int i = 0; i < m; i++) printf("%u/%u\n", ::ans[i].first, ::ans[i].second);
}
