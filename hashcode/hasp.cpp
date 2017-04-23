#include <bits/stdc++.h>

using namespace std;

ifstream fin("videos_worth_spreading.in");
ofstream fout("videos_worth_spreading.out");

const int VMAX = 1e4 + 4;//nr videouri
const int EMAX = 1e3 + 3;//nr endpoint
const int RMAX = 1e6 + 6;//nr requests
const int CMAX = 1e3 + 3;//cache servers
const int XMAX = 5e5 + 5;//capacity of each server

int v, e, r, c, x;

int video[VMAX];
int datac[EMAX];
int space[CMAX];//space left

int taken[CMAX][VMAX];

struct  Dist{
	int id;
	int lat;
	Dist(int id, int lat) {
		this->id = id;
		this->lat = lat;
	}
};

struct Req {

	int idv;//numele serverului
	int nrr;//cate requesturi

	Req(int idv, int nrr) : idv(idv), nrr(nrr) {
	}
};
vector<Dist> endp[EMAX];
vector<Req> endr[EMAX];

vector<int> res[CMAX];
int cachedfilled;

int ind[EMAX];
int delay[EMAX];

int vec[EMAX];

void read() {
	fin >> v >> e >> r >> c >> x;

	for(int i = 0 ; i < c; ++i)
		space[i] = x;

	for(int i = 0 ; i < v; ++i) {
		fin >> video[i];//max 1000
	}

	for(int i = 0 ; i < e; ++i) {

		int ld;//data center->this endpoint
		int k;//cache conntected
		fin >> ld >> k; //ld max 4000, 

		datac[i] = ld;


		for(int j = 0 ; j < k; ++j) {
			int id, lat; fin >> id >> lat;
			endp[i].push_back(Dist(id, lat));
			vec[i]++;
		}


	}

	for(int i = 0 ; i < r ;++i) {
		int rv, re, rn;
		//rv  = id video
		//re = endpoint
		//nr req
		fin >> rv >> re >> rn;
		endr[re].push_back(Req(rv, rn));

	}
}

struct Cmp {

	bool operator() (const int ii, const int jj) {
		return delay[ii]> delay[jj] ; //descrascator
	}
} cmp;

struct CmpReq {
	bool operator() (const Req r1, const Req r2) {
		return r1.nrr > r2.nrr ;
	}
} cmp2;

void solve() {

	for(int i = 0 ; i < e; ++i) {
		for(Req r : endr[i]) {
			delay[i] += (video[r.idv] * r.nrr); //10^10 / 100
		}
	}

	for(int i = 0 ; i < e; ++i)
		ind[i] = i;

	sort(ind , ind + e, cmp);

	//sortez requesturile
	for(int i = 0 ; i < e; ++i) {
		sort(endr[i].begin(), endr[i].end(), cmp2);
	}

	//completez requesturile
	for(int i = 0 ; i < e; ++i) {
		int xx = ind[i];

		//completare brute force
		//request from endpoint

		int reqsolved = 0;
		for(Req r : endr[xx]) {
			
			int videoid = r.idv;
			int mini = 0;
			//take near chaches
			for(Dist d : endp[xx]) {

				//d.id = cache ul pe care vreau sa pun
				if(space[d.id] >= video[videoid]) {
					
					
					
					if(taken[d.id][videoid] == 0) {

						space[d.id] -= video[videoid];
						res[d.id].push_back(videoid);
						taken[d.id][videoid] = 1;
					}

					reqsolved++;

					break;
				}
			}

		}
	}
}

void print() {


	for(int i = 0 ; i < c; ++i) 
		if(res[i].size() > 0)
			cachedfilled++;

	fout << cachedfilled << '\n';

	for(int i = 0; i < c; ++i)
		if(res[i].size() > 0) {
			
			fout << i << ' ';
			
			for(int xx : res[i])
				fout << xx << ' ';
			fout << '\n';
		}
}

int main() {

	read();

	solve();

	print();
	return 0;
}

