#include <stdio.h>

int main() {
	FILE *input, *output;
	input = fopen("walsh.in", "r");
	output = fopen("walsh.out", "w");
	int n, k, lines, neg, x, y;
	fscanf(input, "%d %d", &n, &k);
	for(int i = 0; i < k ; i++) {
		fscanf(input, "%d %d", &x, &y);
		lines = n;
		neg = 0;
		while(lines != 1) {  // cat timp n-am ajuns la W1
			if (x <= lines/2) {
				if (y > lines/2) {  // cadran2
					y = y-lines/2;
				}
			} else {
				if (y <= lines/2) {  // cadran3
					x = x-lines/2;
				} else {  // cadran4
					neg++;
					x = x-lines/2;
					y = y-lines/2;
				}
			}
			lines = lines/2;  // actualizam matricea cu cadranul gasit
		}
		if (neg%2 == 0) {
			fprintf(output, "0\n");
		} else {
			fprintf(output, "1\n");
		}
	}
	fclose(output);
	fclose(input);
	return 0;
}
