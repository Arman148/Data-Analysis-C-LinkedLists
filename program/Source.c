#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int fill_with_integer (int *p, int n, int value) {
	p[n] = value;
	return 0;
}
void reading_string(char str[]) {
	gets(str);
	printf("str = %s\n", str);
	return str;
}

int are_equal(char* str1, char* str2) {
	int result;
	result = strcmp(str1, str2);
	return result;
}

int v_function(int *v, int *n, FILE **file, int *pocet_zaznamov, char*** titles, char*** autors, char*** p_type, int** p_time, int** p_date) {
	if (*v == 1 && *n == 1) {
		for (int k = 0; k < *pocet_zaznamov; k++) {
			printf("\n");
			printf("%s\n", (*titles)[k]);
			printf("%s\n", (*autors)[k]);
			printf("%s\n", (*p_type)[k]);
			printf("%d\n", (*p_time)[k]);
			printf("%d\n", (*p_date)[k]);
			printf("\n");

			
		}



	}
	else {
		*v = 1;
		char line[200];

		if (v) {

		}
		*file = fopen("subor.txt", "r");
		
		if (!(*file)) {
			printf("Neotvoreny subor\n");
		}
		else {
			while (fgets(line, sizeof(line), *file)) {
				line[strcspn(line, "\n")] = 0;
				printf("%s\n", line);
				if (strcmp(line, "\n") == 0) {
					printf("\n");
				}
			}
			fseek(*file, 0, SEEK_SET);

		}
		
		

		//fclose(file);
	}

	

	return 0;
}

int o_function(int* v, int* n, FILE** file, int* pocet_zaznamov, char*** titles, char*** autors, char*** p_type, int** p_time, int** p_date) {

	if (*v == 1 && *n == 1) {
		int date, a, ind = 0;
		int* index;
		int* copy_of_date_array;
		int pd;
		copy_of_date_array = malloc(*pocet_zaznamov * sizeof(int));
		index = malloc(*pocet_zaznamov * sizeof(int));
		for (int a = 0; a < *pocet_zaznamov; a++) {
			copy_of_date_array[a] = (*p_time)[a];
		}

		printf("\n");

		for (int i = 0; i < *pocet_zaznamov; i++) {
			for (int j = i + 1; j < *pocet_zaznamov; j++) {
				if (copy_of_date_array[i] > copy_of_date_array[j]) {
					a = copy_of_date_array[i];
					copy_of_date_array[i] = copy_of_date_array[j];
					copy_of_date_array[j] = a;
				}
			}
		}

		for (int k = 0; k < *pocet_zaznamov; k++) {
			for (int t = 0; t < *pocet_zaznamov; t++) {
				if ((*p_time)[t] == copy_of_date_array[k]) {
					index[ind] = t;
					ind++;
				}
			}
		}
		printf("zadajte datum: ");
		scanf("%ld", &date);

		for (int j = 0; j < *pocet_zaznamov; j++) {
			pd = (*p_date)[j];

			if (pd == date && (!strcmp("UP", (*p_type)[index[j]]) || !strcmp("UD", (*p_type)[index[j]]))) {
				printf("%d  %s   %s     %s\n", (*p_time)[index[j]], (*p_type)[index[j]], (*autors)[index[j]], (*titles)[index[j]]);
			}
		}
		printf("\n");
		for (int t = 0; t < *pocet_zaznamov; t++) {
			pd = (*p_date)[t];
			if (pd == date && (!strcmp("PP", (*p_type)[index[t]]) || !strcmp("PD", (*p_type)[index[t]]))) {
				printf("%d  %s   %s     %s\n", (*p_time)[index[t]], (*p_type)[index[t]], (*autors)[index[t]], (*titles)[index[t]]);
			}
		}

	}
	else if (*v == 1 && *n != 1) {
		char** t = NULL;
		char** a = NULL;
		char** p_tp = NULL;
		int* p_tm = NULL;
		int* p_d = NULL;
		char line[200];
		int length = 0, i = 0;
		int line_count = 1;
		while (fgets(line, sizeof(line), *file)) {
			if (strcmp(line, "\n") == 0) {
				line_count = line_count + 1;
			}
		}
		t = malloc(line_count * sizeof(char*));
		a = malloc(line_count * sizeof(char*));
		p_tp = malloc(line_count * sizeof(char*));
		p_tm = malloc(line_count * sizeof(int));
		p_d = malloc(line_count * sizeof(int));

		fseek(*file, 0, SEEK_SET);


		for (int i = 0; i < line_count; i++) {
			for (int j = 0; j < 5; j++) {
				fgets(line, sizeof(line), *file);
				if (strcmp(line, "\n") == 0) {
					j--;
				}

				length = strlen(line);
				line[strcspn(line, "\n")] = 0;
				if (j == 0) {
					t[i] = malloc(length * sizeof(char));
					strcpy(t[i], line);
				}
				else if (j == 1) {
					a[i] = malloc(length * sizeof(char));
					strcpy(a[i], line);
				}
				else if (j == 2) {
					p_tp[i] = malloc(length * sizeof(char));
					strcpy(p_tp[i], line);
				}
				else if (j == 3) {
					int time = atoi(line);
					fill_with_integer(p_tm, i, time);
				}
				else if (j == 4) {
					int date = atoi(line);
					fill_with_integer(p_d, i, date);
				}
			}
		}

		int date, ind = 0, o;
		int b;
		int* index;
		int* copy_of_date_array;
		int pd;
		copy_of_date_array = malloc(line_count * sizeof(int));
		index = malloc(line_count * sizeof(int));

		
		for (int b = 0; b < line_count; b++) {
			copy_of_date_array[b] = p_tm[b];
		}

		printf("\n");
		
		for (int i = 0; i < line_count; i++) {
			for (int j = i + 1; j < line_count; j++) {
				if (copy_of_date_array[i] > copy_of_date_array[j]) {
					o = copy_of_date_array[i];
					copy_of_date_array[i] = copy_of_date_array[j];
					copy_of_date_array[j] = o;
				}
			}
		}

		for (int k = 0; k < line_count; k++) {
			for (int t = 0; t < line_count; t++) {
				if (p_tm[t] == copy_of_date_array[k]) {
					index[ind] = t;
					ind++;
				}
			}
		}

		printf("zadajte datum: ");
		scanf("%ld", &date);

		for (int j = 0; j < line_count; j++) {
			pd = p_d[j];

			if (pd == date && (!strcmp("UP", p_tp[index[j]]) || !strcmp("UD", p_tp[index[j]]))) {				
				printf("%d  %s   %s     %s\n", p_tm[index[j]], p_tp[index[j]], a[index[j]], t[index[j]]);
			}
		}
		printf("\n");
		for (int e = 0; e < line_count; e++) {
			pd = p_d[e];
			if (pd == date && (!strcmp("PP", p_tp[index[e]]) || !strcmp("PD", p_tp[index[e]]))) {
				printf("%d  %s   %s     %s\n", p_tm[index[e]], p_tp[index[e]], a[index[e]], t[index[e]]);
			}
		}

	}
	else {
		printf("subor este nebol otvoreny\n");
	}
	return 0;
}

int n_function(int* v, int* n, FILE **file, int *pocet_zaznamov, char ***titles, char ***autors, char ***p_type, int **p_time, int **p_date) {
	char line[200];
	int length = 0, i = 0;

	if (*v != 1) {
		printf("neotvoreny subor\n");
	}
	else {
		
		if (!(*file)) {
			printf("Neotvoreny subor\n");
		}
		else {
			while (fgets(line, sizeof(line), *file)) {
				if (strcmp(line, "\n") == 0) {
					*pocet_zaznamov = *pocet_zaznamov + 1;
				}
			}
			*titles = malloc(*pocet_zaznamov * sizeof(char*));
			*autors = malloc(*pocet_zaznamov * sizeof(char*));
			*p_type = malloc(*pocet_zaznamov * sizeof(char*));
			*p_time = malloc(*pocet_zaznamov * sizeof(int));
			*p_date = malloc(*pocet_zaznamov * sizeof(int));
			

			fseek(*file, 0, SEEK_SET);

			

			for (int i = 0; i < *pocet_zaznamov; i++) {
				for (int j = 0; j < 5; j++) {
					fgets(line, sizeof(line), *file);
					if (strcmp(line, "\n") == 0) {
						j--;
					}

					length = strlen(line);
					line[strcspn(line, "\n")] = 0;
					if (j == 0) {
						(*titles)[i] = malloc(length * sizeof(char));
						strcpy((*titles)[i], line);
					}
					else if (j == 1) {
						(*autors)[i] = malloc(length * sizeof(char));
						strcpy((*autors)[i], line);
					}
					else if (j == 2) {
						(*p_type)[i] = malloc(length * sizeof(char));
						strcpy((*p_type)[i], line);
					}
					else if (j == 3) {						
						int time = atoi(line);
						fill_with_integer(*p_time, i, time);
					}
					else if (j == 4) {
						int date = atoi(line);
						fill_with_integer(*p_date, i, date);
					}
				}
			}
			
			*n = 1;

			
		}
		printf("Nacitane data\n");
	}
	


	return 0;
}

int s_function(int *v, int*n, int* pocet_zaznamov, char*** titles, char*** autors, char*** p_type, int** p_time, int** p_date) {
	printf("S\n");
	if (*v == 1 && *n == 1) {
		int date;
		int pd;
		char type[3];
		printf("zadajte datum: ");
		scanf("%ld", &date);
		printf("zadajte typ: ");
		scanf("%s", type);
		for (int i = 0; i < *pocet_zaznamov; i++) {
			pd = (*p_date)[i];			
			if (pd == date && (!strcmp(type, (*p_type)[i]) ) ) {
				printf("%d	%s	%s\n", (*p_time)[i], (*autors)[i], (*titles)[i]);
			}
			
		}
	}
	else {
		printf("Polia nie su vytvorene");
	}

	return 0;
}

int h_function(int* v, int* n, int* pocet_zaznamov, char*** titles, char*** autors, char*** p_type, int** p_time, int** p_date) {
	int pocet_up = 0, pocet_ud = 0, pocet_pp = 0, pocet_pd = 0;
	char up[] = "UP";
	char ud[] = "UD";
	char pp[] = "PP";
	char pd[] = "PD";
	int min_cas = 800;
	int max_cas = 1000;
	if (*v == 1 && *n == 1) {
		printf("Hodina		UP     UD     PP      PD\n\n"); 
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < *pocet_zaznamov; j++) {
				
				if (!strcmp("UP", (*p_type)[j])) {
					if ((*p_time)[j] > min_cas && (*p_time)[j] < max_cas) {
						pocet_up++;
					}
					
				}
				if (!strcmp("UD", (*p_type)[j])) {
					if ((*p_time)[j] > min_cas && (*p_time)[j] < max_cas) {
						pocet_ud++;
					}
					

				}
				if (!strcmp("PP", (*p_type)[j])) {
					if ((*p_time)[j] > min_cas && (*p_time)[j] < max_cas) {
						pocet_pp++;
					}
					

				}
				if (!strcmp("PD", (*p_type)[j])) {
					if ((*p_time)[j] > min_cas && (*p_time)[j] < max_cas) {
						pocet_pd++;
					}
					
				}
				
			}

			if (i == 0) {
				printf("08:00-09:59:	");
			}
			else if (i == 1) {
				printf("10:00-11:59:	");
			}
			else if (i == 2) {
				printf("10:00-11:59:	");
			}
			else if (i == 3) {
				printf("12:00-13:59:	");
			}
			else if (i == 4) {
				printf("14:00-15:59:	");
			}
			else if (i == 5) {
				printf("16:00-17:59:    ");
			}
			else if (i == 6) {
				printf("18:00-19:59     ");
			}
			printf("%d      %d       %d       %d  \n", pocet_up, pocet_ud, pocet_pp, pocet_pd);
			min_cas += 200;
			max_cas += 200;

			pocet_pd = 0;
			pocet_pp = 0;
			pocet_ud = 0;
			pocet_up = 0;
			printf("\n");
		}

	}
	else {
		printf("polia nie su vytvorene");
	}
	
	return 0;
}

int z_function(int* v, int* n, int* pocet_zaznamov, char*** titles, char*** autors, char*** p_type, int** p_time, int** p_date) {
	char title[200];
	int r, d = 0;
	int index = 0;
	
	if (*v == 1 && *n == 1) {
		//printf("titles[2] = %s ", (*titles)[2]);
		scanf("\n");
		fgets(title, 200, stdin);
		title[strcspn(title, "\n")] = 0;
		printf("title = %s\n", title);		
		for (int i = 0; i < *pocet_zaznamov; i++) {
			r = are_equal(title, (*titles)[i]);
			if (r == 0) {
				index = i;
				free((*titles)[i]);
				break;
			}
			
		}
		printf("index = %d\n\n\n\n", index);
		char** before_index_title;
		before_index_title = malloc(index * sizeof(char*));
		for (int j = 0; j < index; j++) {
			int len = strlen((*titles)[j]);
			before_index_title[j] = malloc(len * sizeof(char*));
			strcpy(before_index_title[j], (*titles)[j]);
			printf("before_index_title[%d] = %s\n", j, before_index_title[j]);

		}
		char** after_index;
		after_index = malloc((*pocet_zaznamov - 1) * sizeof(char*));
		for (int k = index+1; k < *pocet_zaznamov; k++) {
			int len = strlen((*titles)[k]);
			after_index[k] = malloc(len * sizeof(char*));
			strcpy(after_index[k], (*titles)[k]);
			printf("after_index[%d] = %s\n", k, after_index[k]);
		}

		/*
		before_index_title = malloc((*pocet_zaznamov - 1) * sizeof(char*));
		printf("index = %d\n", index);
		for (int k = 0; k < i; k++) {
			before_index_title[k] = malloc(strlen((*titles)[i]) * sizeof(char));
			strcpy(before_index_title[k], (*titles)[k]);
			printf("A\n");
			printf("before_index_title[%d] = %s\n", k, before_index_title[k]);

		}
		for (int o = 0; o < i; o++) {
			printf("before_index_title[%d] = %s\n", o, before_index_title[o]);
		}
		*/
		for (int j = 0; j < *pocet_zaznamov; j++) {
			printf("titles[%d] = %s\n", j, (*titles)[j]);
		}
	}
	else {
		printf("Polia nie su vytvorene\n");
	}
	return 0;
}

int p_function(int* v, int* n, int* pocet_zaznamov, char*** titles, char*** autors, char*** p_type, int** p_time, int** p_date) {


	if (*v == 1 && *n == 1) {
		int length = 0;
		printf("pocet zaznamov = %d\n", *pocet_zaznamov);
		char s[20];
		//char s[1];
		char title[200];
		char meno[150];
		char type[5];
		int time = 0;
		int date = 0;
		scanf("%[^\n]s\n", s);
		fgets(s, 20, stdin);
		fgets(title, 200, stdin);
		fgets(meno, 100, stdin);
		fgets(type, 100, stdin);
		scanf("%d", &time);
		scanf("%d", &date);
		title[strcspn(title, "\n")] = 0;
		meno[strcspn(meno, "\n")] = 0;
		type[strcspn(type, "\n")] = 0;

		*titles = realloc(*titles, (*pocet_zaznamov + 1) * sizeof(char*));
		*autors = realloc(*autors, (*pocet_zaznamov + 1) * sizeof(char*));
		*p_type = realloc(*p_type, (*pocet_zaznamov + 1) * sizeof(char*));
		*p_time = realloc(*p_time, (*pocet_zaznamov + 1) * sizeof(int));
		*p_date = realloc(*p_date, (*pocet_zaznamov + 1) * sizeof(int));
		
		
		for (int i = 0; i < *pocet_zaznamov + 1; i++) {
			if (i == *pocet_zaznamov) {
				(*titles)[*pocet_zaznamov] = malloc(strlen(title) * sizeof(char));
				strcpy((*titles)[*pocet_zaznamov], title);
				(*autors)[*pocet_zaznamov] = malloc(strlen(meno) * sizeof(char));
				strcpy((*autors)[*pocet_zaznamov], meno);
				(*p_type)[*pocet_zaznamov] = malloc(strlen(type) * sizeof(char));
				strcpy((*p_type)[*pocet_zaznamov], type);
				fill_with_integer(*p_time, *pocet_zaznamov, time);
				fill_with_integer(*p_date, *pocet_zaznamov, date);
				
			}
		}
		*pocet_zaznamov = *pocet_zaznamov + 1;
		printf("pocet zaznamov = %d\n", *pocet_zaznamov);
	}
	else {
		printf("Polia nie su vytvorene \n");
	}
	
	return 0;
}

int k_function() {
	printf("k\n");
	return 0;
}

int i_function(int** p_time, int* pocet_zaznamov) {
	int k;
	int t, o;
	int cisla[10] = {0};
	scanf("%d", &k);
	if (k > 0) {
		for (int i = 0; i < *pocet_zaznamov; i++) {
			if (((*p_time)[i] % k) == 0) {
				t = (*p_time)[i];
				printf("t = %d\n", t);
				for (int j = 0; j < 4; j++) {
					o = t % 10;
					printf("o = %d\n", o);
					t = t / 10;
					printf("t in for = %d\n", t);
					cisla[o]++;
				}
			}
		}
	}
	else {
		printf("cislo k je nulove alebo kladne\n");
	}

	for (int l = 0; l < 10; l++) {
		if (cisla[l] != 0) {
			printf("%d : ", l);
			for (int t = 0; t < cisla[l]; t++) {
				printf("*");
			}
			printf("\n");
		}		
	}

	return 0;	
}

int y_function(int* pocet_zaznamov, char*** autors, int *y) {
	char str[256];
	char bigStr[256];
	int pocet_men = 0;
	int t = 0;
	scanf("%s", &str);
	//bigStr = tupper(str);
	char** mena = NULL;
	if (*y != 0) {
		printf("uz bola zavolana");
	}
	else {

		for (int i = 0; i < *pocet_zaznamov; i++) {
			if (strstr((*autors)[i], str) != 0) {
				pocet_men++;
			}
		}

		mena = malloc(pocet_men * sizeof(char*));

		for (int j = 0; j < *pocet_zaznamov; j++) {
			if (strstr((*autors)[j], str) != 0) {
				printf("(*autors)[%d] = %s\n", j, (*autors)[j]);
				mena[t] = malloc(strlen((*autors)[j]) * sizeof(char));
				strcpy(mena[t], (*autors)[j]);
				t++;
			}
		}

		for (int k = 0; k < t; k++) {
			printf("mena[%d] = %s\n", k, mena[k]);

			printf("/////////////////////\n");
		}

	}

	return 0;
}

void navigation() {
	int v = 0, n = 0, pocet_zaznamov = 1, y = 0;
	FILE* file = 0;
	printf("v o n s h z p k, x - exit \n");
	char func_name = NULL;
	char** titles = NULL;
	char** autors = NULL;
	char** p_type = NULL;
	int* p_time = NULL;
	int* p_date = NULL;




	printf("zadajte pismeno: ");
	while (1) {
		scanf("%c", &func_name);;
		printf("\n");
		switch (func_name) {
		case 'v':
			v_function(&v, &n, &file, &pocet_zaznamov, &titles, &autors, &p_type, &p_time, &p_date);
			break;
		case 'o':
			o_function(&v, &n, &file, &pocet_zaznamov, &titles, &autors, &p_type, &p_time, &p_date);
			break;
		case 'n':
			n_function(&v, &n, &file, &pocet_zaznamov, &titles, &autors, &p_type, &p_time, &p_date);
			
			break;
		case 's':
			s_function(&v, &n, &pocet_zaznamov, &titles, &autors, &p_type, &p_time, &p_date);
			break;
		case 'h':
			h_function(&v, &n, &pocet_zaznamov, &titles, &autors, &p_type, &p_time, &p_date);;
			break;
		case 'z':
			z_function(&v, &n, &pocet_zaznamov, &titles, &autors, &p_type, &p_time, &p_date);;
			break;
		case 'p':
			p_function(&v, &n, &pocet_zaznamov, &titles, &autors, &p_type, &p_time, &p_date);
			break;
		case 'i':
			i_function(&p_time, &pocet_zaznamov);
			break;
		case 'y':
			y_function(&pocet_zaznamov, &autors, &y);
			break;

		case 'k':
			if (n == 1 && v == 1) {
				for (int i = 0; i < pocet_zaznamov; i++) {
					free(titles[i]);
					free(autors[i]);
					free(p_type[i]);
				}
				free(titles);
				free(autors);
				free(p_type);
				free(p_time);
				free(p_date);
				fclose(file);
				exit(1);

			} 
			else if (v == 1 && n == 0) {
				fclose(file);
				exit(1);
			}
			else {
				exit(1);
			}			
			break;
		default:
			printf("zadajte pismeno: ");
			break;
		}


	}
}

int main() {

	navigation();
	return 0;
}