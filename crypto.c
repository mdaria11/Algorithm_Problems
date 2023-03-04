#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

long nraparitii(char *key, char *subsir, int m, int n) {
	long *dp;
	long variables = 0;
	int *characters;
	characters = calloc(26, sizeof(int));
	for (int i = 0; i < n; i++) {  // numaram nr de litere distincte
		if(characters[(int)(subsir[i]-97)] == 0) {
			characters[(int)(subsir[i]-97)] = 1;
			variables++;
		}
	}
	dp = malloc(sizeof(long)*(m+1) * (n+1));
	for(int i = 0; i <= n; i++) {
		dp[i] = 0;
	}
	dp[0] = 1;
	for(int i = 1; i <= m; i++) {
		if (key[i-1] == '?') {  // se formeaza mai multe combinatii posibile
			dp[i*(n+1)] = (dp[(i-1)*(n+1)]%MOD * variables)%MOD;
		} else {
			dp[i*(n+1)] = dp[(i-1)*(n+1)];
		}
	}
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) {
			if (key[i-1] == '?') {  // consideram toate literele posibile
				dp[i*(n+1)+j] = (variables*dp[(i-1)*(n+1)+j]%MOD+dp[(i-1)*(n+1)+(j-1)])%MOD;
			} else {
				if (key[i-1] == subsir[j-1]) {  // adaugam noile subsecvente create
					dp[i*(n+1)+j] = (dp[(i-1)*(n+1)+(j-1)] + dp[(i-1)*(n+1)+j])%MOD;
				} else {  // ramanem cu acelasi nr de subsecvente
					dp[i*(n+1)+j] = dp[(i-1)*(n+1)+j];
				}
			}
		}
	}
	long nr = dp[m*(n+1)+n];
	free(dp);
	free(characters);
	return nr;
}

int main() {
	FILE *input, *output;
	input = fopen("crypto.in", "r");
	output = fopen("crypto.out", "w");
	int n, l;
	char *key, *subsir;
	fscanf(input, "%d %d", &n, &l);
	key = malloc(sizeof(char)*(n+1));
	subsir = malloc(sizeof(char)*(l+1));
	fscanf(input, "%s", key);
	fscanf(input, "%s", subsir);
	long nr = nraparitii(key, subsir, n, l);
	fprintf(output, "%ld", nr);
	free(key);
	free(subsir);
	fclose(output);
	fclose(input);
	return 0;
}
