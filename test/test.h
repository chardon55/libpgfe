#ifndef LIGPGFE_TEST_TEST_H
#define LIGPGFE_TEST_TEST_H

#define ARGS int argc, char **argv

#define TEST_INIT                                                                                                      \
    char *option = argv[1];                                                                                            \
    char output_str[400];

#define TEST_CASE(cmd, name)                                                                                           \
    if (!strcmp(option, cmd)) {                                                                                        \
        name(argc, argv);                                                                                              \
    }                                                                                                                  \
    else

#endif