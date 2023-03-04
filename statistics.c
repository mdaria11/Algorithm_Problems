#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contributions {
	int wordindex;
	int c;
};

// ordoneaza descresc dupa contributie
int cmpfunct(const void *a, const void *b) {
	struct contributions *aa = (struct contributions *)a;
	struct contributions *bb = (struct contributions *)b;
	return bb->c - aa->c;
}

int* sortwords(char **words, int n, int **frecv, int indexlitera) {
	int *newwords;
	newwords = malloc(sizeof(int)*n);
	struct contributions *contrib;
	contrib = malloc(sizeof(struct contributions)*n);
	for(int i = 0; i < n; i++) {  // luam toate cuvintele
		contrib[i].wordindex = i;
		// calculam contributia lit in cuv
		contrib[i].c = 2*(frecv[i])[indexlitera]-strlen(words[i]);
	}
	qsort(contrib, n, sizeof(struct contributions), cmpfunct);
	for(int i = 0; i < n; i++) {
		newwords[i] = contrib[i].wordindex;
	}
	free(contrib);
	return newwords;  // vector cu indicii cuvintelor ordonate dupa contributie
}

int main() {
	FILE *input, *output;
	input = fopen("statistics.in", "r");
	output = fopen("statistics.out", "w");
	int n, length, maxlength = 0, **frecv, current, *frecvtotal;
	char **words, aux[500];
	fscanf(input, "%d", &n);
	words = malloc(sizeof(char*)*n);
	frecv = malloc(sizeof(int*)*n);
	frecvtotal = calloc(26, sizeof(int));
	for(int i = 0; i < n; i++) {
		frecv[i] = malloc(sizeof(int)*26);
		for(int j = 0; j < 26; j++) {
			(frecv[i])[j] = 0;
		}
	}
	for(int i = 0; i < n; i++) {
		fscanf(input, "%s", aux);
		length = strlen(aux);
		words[i] = malloc(sizeof(char)*(length+1));
		snprintf(words[i], length+1, "%s", aux);
		maxlength = maxlength+length;  // lungimea totala a cuvintelor
		for(int j = 0; j < length; j++) {  // numarare frecvente litere
			int index = (int)(aux[j]-97);
			(frecv[i])[index]++;
			frecvtotal[index]++;
		}
	}
	int *newwords;
	int *concatenari;
	concatenari = malloc(sizeof(int)*26);
	int auxc = 0;
	for(int i = 0; i < 26; i++) {  // luam fiecare litera
		if (frecv[i] == 0) {
			continue;
		}
		current = n;
		int currentlength = maxlength;
		newwords = sortwords(words, n, frecv, i);  // sortam vectorul
		while(current > 0) {
			if (frecvtotal[i]*2-1 >= currentlength) {  // am gasit litera dominanta
				break;
			}
			// calculam noua frecventa
			frecvtotal[i] = frecvtotal[i]-(frecv[newwords[current-1]])[i];
			// calculam noua lungime
			currentlength = currentlength-strlen(words[newwords[current-1]]);
			current--;
		}
		concatenari[auxc] = current;  // nr maxim de concatenari pentru litera curenta
		auxc++;
	}
	int maxever = -1;
	for(int i = 0; i < auxc; i++) {
		if (concatenari[i] > maxever) {
			maxever = concatenari[i];  // nr maxim de concatenari
		}
	}
	if (maxever == 0) {
		fprintf(output, "-1");
	} else {
		fprintf(output, "%d", maxever);
	}
	for(int i = 0; i < n; i++) {
		free(words[i]);
		free(frecv[i]);
	}
	free(words);
	free(newwords);
	free(frecv);
	free(frecvtotal);
	free(concatenari);
	fclose(output);
	fclose(input);
	return 0;
}
