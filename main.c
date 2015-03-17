#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

char *uzycie =
		"Użycie: (opcjonalnie APPROX_BASE_SIZE=m) %s -we plik(i)-wejściowe -p plik-pośredni (opcjonalnie) -wy plik_wyjściowy -n liczba-słów-w-n-gramie -i liczba-operacji \n"
		"            Jeżeli plik z tekstem został podany to\n"
		"               czyta z niego\n"
		"               - liczba słów powinna wynosić >= 4\n"
		"            endfi\n"
		"            Jeżeli dany jest plik-wyjściowy to\n"
		"               - "
                "               - "
                "               - "
                "               - "
                "               - "
                "               - "
		"            endif\n";

int main (int argc, char **argv) {
	int opt;								
	char *in = NULL;
	char *pos = NULL
	char *out = NULL;
	int i = 100;
	int n = 100; 	/* domyślne ustawienie potrzebne do działania programu */
	double *dane_a = NULL;
	double *dane_b = NULL;


	if (argv[1] == NULL) {
		fprintf (stderr, uzycie, argv[0]);
	}

	while ((opt = getopt (argc, argv, "we:p:wy:n:i:")) != -1) { 		/* opcje działanie + zapisywanie wyborów użytkownika */
		switch (opt) {
		case 'we':
			in = optarg;
			break;
		case 'p':
			pos = optarg;
			break;
		case 'wy':
			out = optarg;
			break;
		case 'n':
			n = atof (optarg);
			break;
		case 'i':
			i = atoi (optarg);
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
	}
}
