#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

char *uzycie =
		"Użycie: (opcjonalnie APPROX_BASE_SIZE=m) %s -p plik-z-punktami -g plik-out (wyjście) -o od_x -d do_x -n n_punktów\n"
		"            Jeżeli plik z punktami został podany to\n"
		"               czyta z niego\n"
		"               - liczba punktów powinna wynosić >= 4\n"
		"            endfi\n"
		"            Jeżeli dany jest plik-out to\n"
		"               program tworzy tabelę n-punktów z zakresu <od_x , do_x>\n"
		"               - od_x - pierwsza dana z pliku z punktami do aproksymacji\n"
		"               - do_x - jako ostatnia dana do aproksymacji\n"
		"               - n-punktów domyślnie 100\n"
		"               - n-punktów musi być > 1\n"
		"            Jeżeli zdefiniowano m w APPROX_BASE_SIZE to taka będzie liczba funkcji bazowych.\n"
		"               Domyślnie m jest definiowane w programie na podstawie algorytmu m = ((n-1)/2) - 1 (gdzie n - liczba punktów w pliku p).\n"
		"            endif\n";

int main (int argc, char **argv) {
	int opt;								
	char *in = NULL;
	char *out = NULL;
	double odX = 0;
	double doX = 0;
	int n = 100; 	/* domyślne ustawienie potrzebne do działania programu */
	double *dane_a = NULL;
	double *dane_b = NULL;

	points_t pts;
	pts.n = 0;

	if (argv[1] == NULL) {
		fprintf (stderr, uzycie, argv[0]);
	}

	while ((opt = getopt (argc, argv, "p:g:o:d:n:")) != -1) { 		/* opcje działanie + zapisywanie wyborów użytkownika */
		switch (opt) {
		case 'p':
			in = optarg;
			break;
		case 'g':
			out = optarg;
			break;
		case 'o':
			odX = atof (optarg);
			break;
		case 'd':
			doX = atof (optarg);
			break;
		case 'n':
			n = atoi (optarg);
			break;
		default:
			fprintf (stderr, uzycie, argv[0]);
			return EXIT_FAILURE;
		}
	}


	if( optind < argc ) {							
		fprintf( stderr, "\nPodano złe parametry!\n" );
		for( ; optind < argc; optind++ )
			fprintf( stderr, "\t\"%s\"\n", argv[optind] );
		fprintf( stderr, "\n" );
		fprintf( stderr, uzycie, argv[0] );
		return EXIT_FAILURE;
	}


	if (in != NULL) {
		FILE *inf = fopen (in, "r");
		if (inf == NULL) {
			fprintf (stderr, "%s: brak możliwości czytania pliku z danymi: %s\n\n", argv[0], in);
			return EXIT_FAILURE;
		}

		if (read_pts_failed (inf, &pts)) {
			fprintf (stderr, "%s: nieprawidłowa zawartość pliku z danymi: %s\n\n", argv[0], in);
			return EXIT_FAILURE;
		}
		else
			fclose (inf);		

