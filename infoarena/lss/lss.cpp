#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int p, k;


typedef struct {
	int ind, val, add, viz;
} interval;


int v[NMAX];
interval a[NMAX * 4];
int vv[NMAX];
int ans;
int indexx;


//st, dr unde sunt// ab ce vreau sa updatez
void update(int nod, int st, int dr, int aa, int b, int val) {


	if(aa <= st && dr <= b) {

		//indicele nu se modifica
		a[nod].val += val;
		a[nod].add += val;
		a[nod].viz = 1;

		return ;
	}

	int mij = (st + dr) / 2;

	//updateaza daca e nevoie
	if (a[nod].viz == 1) {

        update(nod * 2, st, mij, st, mij, a[nod].add);
        update(nod * 2 + 1, mij + 1, dr, mij + 1, dr, a[nod].add);
        a[nod].viz = 0;
        a[nod].add = 0;
    }
    //st mij dr
    if(aa <= mij)
    	update(nod * 2, st, mij, aa, b, val);
    if(b > mij)
    	update(nod * 2 + 1, mij + 1, dr, aa, b, val);

    a[nod].val = a[nod * 2].val;
    a[nod].ind = a[nod * 2].ind;

    if(a[nod].val >= a[nod * 2 + 1].val) {
    	a[nod].val = a[nod * 2 + 1].val;
    	a[nod].ind = a[nod * 2 + 1].ind;
    }

}


void build(int nod, int st, int dr) {

	if(st >= dr) {
		a[nod].ind = st;
		a[nod].add = 0;
		a[nod].viz = 0;
		a[nod].val = v[st];
		return ;
	}

	int mij = (st + dr) / 2;

	build(nod * 2, st, mij);
	build(nod * 2 + 1, mij + 1, dr);

	a[nod].ind = a[nod * 2].ind;

	if(v[a[nod * 2 + 1].ind] <= v[a[nod].ind])
		a[nod].ind = a[nod * 2 + 1].ind;

	a[nod].val = v[a[nod].ind];
}

void query(int nod, int st, int dr, int aa, int b) {

	if(aa <= st && dr <= b) {
		//cout << st << ' ' << dr << ' ' << a[nod].val <<' ' << a[nod].ind << '\n';
		if(ans >= a[nod].val) {
			ans = a[nod].val;
			indexx = a[nod].ind;
		}

		return ;
	}

	int mij = (st + dr) / 2;

	if(a[nod].viz == 1) {
		update(nod * 2, st, mij, st, mij, a[nod].add);
		update(nod * 2 + 1, mij + 1, dr, mij + 1, dr, a[nod].add);
		a[nod].viz = 0;
		a[nod].add = 0;
	}


	//st, mij, dr
	if(aa <= mij)
		query(nod * 2, st, mij, aa, b);
	if(b > mij)
		query(nod * 2 + 1, mij + 1, dr, aa, b);
}

int main() {

	freopen("lss.in", "r", stdin);
	freopen("lss.out", "w", stdout);


	//1 2 3 k 1 2 3k
	cin >> k >> p;

	for(int i = 1; i <= p; ++i) {
		cin >> vv[i];
	}

	sort(vv + 1, vv + p + 1);

	for(int i = 1; i <= p; ++i) {
		v[i] = vv[i] % k;
		if(v[i] == 0)
			v[i] = k;
	}

	build(1, 1, p);
	int posf = 1;


	//cout << ans << ' ' << indexx << '\n';
	long long sum = 0;
	for(int i = 1; i <= p; ++i) {

		ans = INF;
		query(1, 1, p, 1, p);

		if(ans != 1) {
			
			ans = INF;
			query(1, 1, p, posf, posf);
			sum += 1ll* ans;

			v[posf] = -1;
			update(1, 1, p, posf, posf, INF);//sterg primul
			update(1, 1, p, posf + 1, p, -1);//cresc valoarea la restul

			do {
				posf++;
			} while(posf <= p && v[posf] == -1);

		} else {

			sum += 1ll * ans;
			v[indexx] = -1;
			update(1, 1, p, indexx, indexx, INF);
			update(1, 1, p, indexx + 1, p, -1);

			if(posf == indexx)
				do {
					posf++;
				} while(posf <= p && v[posf] == -1);
		}

	}

	cout << sum << '\n';
	return 0;
}