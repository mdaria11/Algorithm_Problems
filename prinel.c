#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF ((int) 1e7)

int *dp;
int minnrop = 10000;

void initializedpvector() {
	dp = malloc(sizeof(int)*100001);
	dp[1] = 0;
	for(int i = 2; i < 100001; i++) {
		dp[i] = INF;
	}
}

int* finddivisorsfor(int n) {  // calculam divizorii
	int *divisors;
	divisors = malloc(sizeof(int)*1000);
	int aux = 0;
	for(int i = 1; i <= sqrt(n); i++) {
		if (n%i == 0) {
			divisors[aux] = i;
			aux++;
			if (n/i != 0 && n/i != n) {
				divisors[aux] = n/i;
				aux++;
			}
		}
	}
	divisors[aux] = 0;
	return divisors;
}

int nroperatii(int target) {
	if (dp[target] != INF) {
		return dp[target];
	}
	for(int i = 2; i <= target; i++) {  // luam toate numerele
		int *divisors;
		divisors = finddivisorsfor(i);  // divizorii numarului curent
		int div = 0;
		while(divisors[div] != 0) {  // luam divizorii
			if (dp[i] > dp[i-divisors[div]]+1) {  // minimizam nr de operatii
				dp[i] = dp[i-divisors[div]]+1;
			}
			div++;
		}
		free(divisors);
	}
	return dp[target];
}

int findmaxpoints(int n, int k, int *nrop, int *points) {
	int *dpp;
	int sumforfirst = 0;
	int maxnrop = 0;
	int maxpoints = 0;
	// numarul total de operatii cu care sa formam toate numerele
	for(int i = 0; i < n; i++) {
		maxnrop = maxnrop + nrop[i];
		maxpoints = maxpoints + points[i];  // numarul de puncte pentru toate numerele
	}
	if (maxnrop <= k) {  // se pot forma toate numerele cu cele k operatii
		return maxpoints;
	}
	dpp = calloc((k+1), sizeof(int));
	for(int i = 0; i < n; i++) {  // luam toate numerele
		for(int w = k; w >= minnrop; w--) {
			if (nrop[i] <= w) {  // verificam daca putem sa facem numarul
				if (dpp[w] < dpp[w-nrop[i]]+points[i]) {  // maximizam numarul de puncte
					dpp[w] = dpp[w-nrop[i]]+points[i];
				}
			}
		}
	}
	int maxx = dpp[k];
	free(dpp);
	return maxx;
}

int main() {
	FILE *input, *output;
	input = fopen("prinel.in", "r");
	output = fopen("prinel.out", "w");
	int n, k, *target, *points, *nrop, maxpoints, maxtarget = -1, maxindex;
	fscanf(input, "%d %d", &n, &k);
	target = malloc(sizeof(int)*(n));
	points = malloc(sizeof(int)*(n));
	nrop = malloc(sizeof(int)*(n));
	initializedpvector();
	for(int i = 0; i < n; i++) {
		fscanf(input, "%d", &target[i]);
	}
	for(int i = 0; i < n; i++) {
		if (target[i] > maxtarget) {
			maxtarget = target[i];  // target maxim
			maxindex = i;
		}
	}
	// calculam nr minim de operatii pentru toate nr<=maxtarget
	nrop[maxindex] = nroperatii(maxtarget);
	for(int i = 0; i < n; i++) {
		fscanf(input, "%d", &points[i]);
	}
	for(int i = 0; i < n; i++) {
		nrop[i] = nroperatii(target[i]);
	}
	for(int i = 0; i < n; i++) {
		if (nrop[i] < minnrop) {
			minnrop = nrop[i];  // nr minim de operatii din toate numerele
		}
	}
	maxpoints = findmaxpoints(n, k, nrop, points);  // numar maxim de puncte
	fprintf(output, "%d", maxpoints);
	free(target);
	free(points);
	free(nrop);
	fclose(output);
	fclose(input);
	free(dp);
	return 0;
}
