#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

class Shark {
public:
	int r{};
	int c{};
	int s{};
	int dr{ 0 };
	int dc{ 0 };
	int z{};
	bool is_caugth{ false };
};

int R, C, M;
int pcol;
vvi wumi;
vector<Shark> sharks;

void eat(int i, int j) {
	auto mxz = int{ -1 };
	for (auto s = 0; s < M; ++s) {
		const auto& sh = sharks[s];

		if (!sh.is_caugth && sh.r == i && sh.c == j) {
			if (mxz < sh.z) {
				mxz = sh.z;
			}
		}
	}

	for (auto s = 0; s < M; ++s) {
		auto& sh = sharks[s];

		if (!sh.is_caugth && sh.r == i && sh.c == j) {
			if (sh.z < mxz) {
				sh.is_caugth = true;
			}
		}
	}

	wumi[i][j] = 1;
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> R >> C >> M;
	pcol = -1;

	wumi = vvi(R, vi(C, 0));
	sharks = vector<Shark>(M);

	for (auto i = 0; i < M; ++i) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;

		auto sh = Shark{};
		sh.r = r - 1;
		sh.c = c - 1;
		sh.s = s;
		if (1 == d) {
			sh.dr = -1;
			sh.dc = 0;
		}
		else if (2 == d) {
			sh.dr = 1;
			sh.dc = 0;
		}
		else if (3 == d) {
			sh.dr = 0;
			sh.dc = 1;
		}
		else if (4 == d) {
			sh.dr = 0;
			sh.dc = -1;
		}
		sh.z = z;

		sharks[i] = sh;
		wumi[sh.r][sh.c] += 1;
	}

	auto ans = ll{ 0 };
	while (pcol < C) {
		// move person
		++pcol;

		if (pcol == C) {
			break;
		}

		// get a shark
		auto isFound = bool{ false };
		for (auto r = 0; !isFound && r < R; ++r) {
			const auto val = wumi[r][pcol];
			if (0 <= val) {
				for (auto s = 0; !isFound && s < M; ++s) {
					if (!sharks[s].is_caugth &&
						sharks[s].r == r && sharks[s].c == pcol) {
						ans += sharks[s].z;
						sharks[s].is_caugth = true;
						isFound = true;
						break;
					}
				}
			}
		}

		// move sharks
		wumi = vvi(R, vi(C, 0));

		for (auto i = 0; i < M; ++i) {
			auto& sh = sharks[i];

			if (sh.is_caugth) {
				continue;
			}

			auto moves = sh.s;
			if (0 == sh.dr) {
				moves %= ((C - 1) * 2);
				while (0 < moves) {
					if ((0 == sh.c && sh.dc < 0) ||
						(C - 1 == sh.c && 0 < sh.dc)) {
						sh.dc *= -1;
					}

					sh.c += sh.dc;

					--moves;
				}
			}
			else if (0 == sh.dc) {
				moves %= ((R - 1) * 2);
				while (0 < moves) {
					if ((0 == sh.r && sh.dr < 0) ||
						(R - 1 == sh.r && 0 < sh.dr)) {
						sh.dr *= -1;
					}

					sh.r += sh.dr;

					--moves;
				}
			}

			wumi[sh.r][sh.c] += 1;
		}

		for (auto i = 0; i < R; ++i) {
			for (auto j = 0; j < C; ++j) {
				if (1 < wumi[i][j]) {
					eat(i, j);
				}
			}
		}
	}

	cout << ans;

	return 0;
}