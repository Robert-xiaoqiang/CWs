#include <iostream>
#include <vector>

using namespace std;

long long determinant(vector< vector<long long> > m) 
{
	long long ret = 0;
	auto n = m.size();
	if(n == 1) {
		ret = m[0][0];
	} else if(n == 2) {
		ret = m[0][0] * m[1][1] - m[1][0] * m[0][1];
	} else {
		// 0 row expand
		long long sign = 1ll;
		// for each column
		for(unsigned int i = 0u; i < n; i++) {
			auto mc = m;
			mc.erase(mc.begin());
			for(unsigned int c = 0u; c < mc.size(); c++) mc[c].erase(mc[c].begin() + i);
			ret += sign * m[0][i] * determinant(mc);
			sign *= -1ll;
		}
	}

	return ret;
}

int main()
{
	vector<vector<long long>> m = {
		{ 1ll, 2ll, 7ll },
		{ 3ll, 4ll, 8ll },
		{ 5ll, 6ll, 9ll }
	};
	cout << determinant(m) << endl;
	return 0;
}