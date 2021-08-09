#ifndef HLIB_BF_VA_ARGS_H_
#define HLIB_BF_VA_ARGS_H_

#define VA_ARG_1(_1,...) _1
#define VA_ARG_2(_1,...) VA_ARG_1(__VA_ARGS__)
#define VA_ARG_3(_1,...) VA_ARG_2(__VA_ARGS__)
#define VA_ARG_4(_1,...) VA_ARG_3(__VA_ARGS__)
#define VA_ARG_5(_1,...) VA_ARG_4(__VA_ARGS__)
#define VA_ARG_6(_1,...) VA_ARG_5(__VA_ARGS__)
#define VA_ARG_7(_1,...) VA_ARG_6(__VA_ARGS__)
#define VA_ARG_8(_1,...) VA_ARG_7(__VA_ARGS__)
#define VA_ARG_9(_1,...) VA_ARG_8(__VA_ARGS__)
#define VA_ARG_N(N,...) VA_ARG_##N(__VA_ARGS__)


#endif