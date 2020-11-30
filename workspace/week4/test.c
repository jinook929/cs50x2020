#include <getopt.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *filters = "bgrs";
    char filter = getopt(argc, argv, filters);
    printf("%s\n", filters);
    printf("%c\n", filter);
    printf("%i\n", optind);
    printf("%s\n", argv[optind]);
    printf("%s\n", argv[optind + 1]);

    return 0;
}