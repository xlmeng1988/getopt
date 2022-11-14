#include <getopt.h>
#include <stdio.h>

static void showUsage(const char *cmd)
{
	printf("Usage: %s [options]\n\n"
		   "Options:\n"
		   "-a | --long_no_arg_short_a       option without argument which has\n"
		   "                                 short format(-a) and long format(--long_no_arg_short_a)\n"
		   "-b | --long_req_arg_short_b      option with an argument which has\n"
		   "                                 short format(-b) and long format(--long_req_arg_short_b)\n"
		   "     --long_no_arg_no_short      option without argument which has\n"
		   "                                 only long format(--long_no_arg_no_short)\n"
		   "     --long_with_arg_no_short    option with an argument which has\n"
		   "                                 only long format(--long_with_arg_no_short)\n"
		   , cmd);
}

int main(int argc, char *argv[])
{
	if (1 == argc)
	{
		showUsage(argv[0]);
		return 0;
	}
	const char short_options[] = "ab:";
	int lopt = 0;
	const struct option
		long_options[] = {
			{"long_no_arg_short_a", no_argument, NULL, 'a'},
			{"long_req_arg_short_b", required_argument, NULL, 'b'},
			{"long_no_arg_no_short", no_argument, &lopt, 1},
			{"long_with_arg_no_short", required_argument, &lopt, 2},
			{NULL, no_argument, NULL, 0}};
	// parse arguments
	while (1)
	{
		int c = 0;
		int lopt_idx = 0;
		c = getopt_long(argc, argv, short_options, long_options, &lopt_idx);
		//        printf("lopt_idx = %d\n", lopt_idx);
		//        printf("c = %c\t%d\n", c, c);
		if (-1 == c)
		{
			//            printf("optind = %d\n", optind);
			//            printf("optarg = %s\n", optarg);
			//            printf("argc = %d\n", argc);
			if (optind < argc)
			{
				printf("non-option ARGV-elements: ");
				while (optind < argc)
					printf("%s ", argv[optind++]);
				printf("\n");
				showUsage(argv[0]);
				return 1;
			}
			break; // finish
		}
		switch (c)
		{
		case 0:
		{
			switch (lopt)
			{
			case 1:
				printf("--long_no_arg_no_short\n");
				break;
			case 2:
				printf("--long_with_arg_no_short, arg = %s\n", optarg);
				break;
			default:
				break;
			}
			break;
		}
		case 'a':
		{
			printf("--long_no_arg_short_a or -a\n");
			break;
		}
		case 'b':
			printf("--long_req_arg_short_b or -b, b = %s\n", optarg);
			return 0;
		case 'h':
			showUsage(argv[0]);
			return 0;
		default:
			showUsage(argv[0]);
			return 1;
		}
	}
}