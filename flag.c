/* Copyright (c) 2025 Hugo Coto */

#include <stdio.h>
struct flag_opts {
        char *opt;
        char *abbr;
        char *help;
        int nargs;
        int *set;
        char *def;
        int required;
};

struct program_opts {
        int *argc;
        char ***argv;
        char *name;
        char *help;
} flag_prog = { 0 };


struct {
        int count;
        struct flag_opts *flags;
} flag_flags = { 0 };

#define flag_add(...) __flag_add((struct flag_opts) { __VA_ARGS__ })
#define flag_program(...) __flag_program((struct program_opts) { __VA_ARGS__ })

#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#define __flag_realloc(...) realloc(__VA_ARGS__)

void
flag_show_help(int fileno)
{
        int i;
        int first = 0;

        printf("usage: %s", flag_prog.name);
        if (flag_flags.count == 0) goto prog_help;

        for (i = 0; i < flag_flags.count; i++) {
                printf(flag_flags.flags[i].required ? " " : " [");
                if (flag_flags.flags[i].abbr)
                        printf("%s ", flag_flags.flags[i].abbr);
                printf("%s", flag_flags.flags[i].opt);
                printf(flag_flags.flags[i].required ? "" : "]");
        }

prog_help:
        printf("\n\n");
        if (flag_prog.help) printf("%s\n\n", flag_prog.help);
        if (flag_flags.count == 0) return;

        printf("options:\n");
        for (i = 0; i < flag_flags.count; i++) {
                printf(" ");
                printf("%s", flag_flags.flags[i].opt);
                if (flag_flags.flags[i].abbr)
                        printf(", %s", flag_flags.flags[i].abbr);
                int j;
                for (j = 0; j < flag_flags.flags[i].nargs; j++)
                        printf(" %c", toupper(flag_flags.flags[i].opt[2]));
                printf("\t\t");
                if (flag_flags.flags[i].help)
                        printf("%s", flag_flags.flags[i].help);
                if (flag_flags.flags[i].def)
                        printf(" (default: %s)", flag_flags.flags[i].def);
                printf("\n");
        }

}

void
__flag_add(struct flag_opts opts)
{
        flag_flags.flags = __flag_realloc(flag_flags.flags,
                                          (flag_flags.count + 1) * sizeof opts);
        flag_flags.flags[flag_flags.count] = opts;
        ++flag_flags.count;
}

void
__flag_program(struct program_opts opts)
{
        flag_prog = opts;
}

int
flag_parse(int *argc, char ***argv)
{
        if (!flag_prog.name) flag_prog.name = **argv;
        return 0;
}

int
main(int argc, char **argv)
{
        flag_program(.help = "Flag2.h by Hugo Coto");
        flag_add("--help", "-h", .help = "Show this help");
        flag_add("--foo", .help = "foo flag", .nargs = 2);
        flag_add("-b", .def = "BBB", .required = 1);
        flag_parse(&argc, &argv);
        flag_show_help(STDOUT_FILENO);
        return 0;
}
