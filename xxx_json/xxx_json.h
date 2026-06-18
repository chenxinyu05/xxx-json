#ifndef XXX_JSON_H
#define XXX_JSON_H

#include <stdlib.h>

#ifndef XXX_JSON_FREE
# define XXX_JSON_FREE(ptr) free(ptr)
#endif

#ifndef XXX_JSON_MALLOC
# define XXX_JSON_MALLOC(size) malloc(size)
#endif

#ifndef XXX_JSON_REALLOC
# define XXX_JSON_REALLOC(size) realloc(size)
#endif

#ifndef XXX_JSON_CALLOC
# define XXX_JSON_CALLOC(count, size) calloc(count, size)
#endif

#ifndef XXX_JSON_ERROR
# include <stdio.h>
# define XXX_JSON_ERROR(format, ...) fprintf(stderr, "xxx_json error: " format "\n", ##__VA_ARGS__)
#endif

enum XXX_JSON_TYPE {
    XXX_JSON_NULL, XXX_JSON_BOOLEAN, XXX_JSON_NUMBER, XXX_JSON_STRING, XXX_JSON_ARRAY, XXX_JSON_OBJECT
};

typedef struct xxx_json xxx_json_t;
typedef struct xxx_json_null xxx_json_null_t;
typedef struct xxx_json_boolean xxx_json_boolean_t;
typedef struct xxx_json_number xxx_json_number_t;
typedef struct xxx_json_string xxx_json_string_t;
typedef struct xxx_json_array xxx_json_array_t;
typedef struct xxx_json_object xxx_json_object_t;

#ifdef __cplusplus
extern "C" {
#endif

#ifndef XXX_RESTRICT
    #if defined(__cplusplus)
        // C++ 环境下：只在主流编译器中启用 __restrict 扩展
        #if defined(_MSC_VER) || defined(__GNUC__) || defined(__clang__)
            #define XXX_RESTRICT __restrict
        #else
            #define XXX_RESTRICT /* 遇到严格或冷门的 C++ 编译器，安全退化为空 */
        #endif
    #elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
        // C 环境下：只有当编译器明确声明支持 C99 或更高版本时，才使用原生 restrict
        #define XXX_RESTRICT restrict
    #else
        // 古老的 C89/C90 环境：安全退化为空
        #define XXX_RESTRICT
    #endif
#endif

static inline int xxx_json_init(xxx_json_t *self);
static inline void xxx_json_deinit(xxx_json_t *self);

// static inline int xxx_json_null_init(xxx_json_null_t *self);
// static inline void xxx_json_null_destory(xxx_json_null_t *self);

static inline int xxx_json_boolean_init(xxx_json_boolean_t *self);
static inline void xxx_json_boolean_deinit(xxx_json_boolean_t *self);
static inline int xxx_json_boolean_copy(xxx_json_boolean_t *dst, const xxx_json_boolean_t *src);
static inline void xxx_json_boolean_move(xxx_json_boolean_t *dst, xxx_json_boolean_t *src);

static inline int xxx_json_number_init(xxx_json_number_t *self);
static inline void xxx_json_number_deinit(xxx_json_number_t *self);
static inline int xxx_json_number_copy(xxx_json_number_t *XXX_RESTRICT dst, const xxx_json_number_t *XXX_RESTRICT src);
static inline void xxx_json_number_move(xxx_json_number_t *dst, xxx_json_number_t *src);

static inline int xxx_json_string_init(xxx_json_string_t *self);

#ifdef __cplusplus
}
#endif

struct xxx_json_null {};

int xxx_json_null_init(xxx_json_null_t *self) {
    (void)self;
    return 0;
}

struct xxx_json_boolean {
    bool value;
};

struct xxx_json_number {};

struct xxx_json_string {};

struct xxx_json_array {};

struct xxx_json_object {};

struct xxx_json {
    int type;
    union {
        xxx_json_null_t     null;
        xxx_json_boolean_t  boolean;
        xxx_json_number_t   number;
        xxx_json_string_t   string;
        xxx_json_array_t    array;
        xxx_json_object_t   object;
    };
};


int xxx_json_parse(xxx_json_t *self, const char *s, size_t n);

int xxx_json_init(xxx_json_t *self) {
    self->type = XXX_JSON_NULL;
    return 0;
}

void xxx_json_deinit(xxx_json_t *self);

#endif
