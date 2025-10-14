/* Copyright (c) 2025 Hugo Coto */

#include "flag.h"

int
main(int argc, char **argv)
{
        char *b;
        char *foo;

        /* Optional. Set program info */
        flag_program(.help = "Flag2.h by Hugo Coto", .name = "hflag");

        /* Register flags. The first argument is a pointer that should be set to
         * the constant string with the argument. If the flag is not set, it
         * would be set to NULL. See flag_opts */
        flag_add(&foo, "--foo", "-f", .def = "nothing", .help = "foo flag", .nargs = 1);

        if (flag_parse(&argc, &argv)) {
                flag_show_help(STDOUT_FILENO);
                exit(1);
        }

        printf("foo = %s\n", foo);

        return 0;
}
