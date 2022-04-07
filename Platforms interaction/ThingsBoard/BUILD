cc_library(
    name = "cJSON-1.7.15",
    srcs = ["cJSON-1.7.15/cJSON.c"],
    hdrs = ["cJSON-1.7.15/cJSON.h"],
    includes = ["cJSON-1.7.15"], #cJSON-1.7.15 folder
)

cc_library(
    name = "thingsboard",
    srcs = ["thingsboard/thingsboard.c"],
    hdrs = ["thingsboard/thingsboard.h"],
    includes = ["thingsboard"], #cJSON-1.7.15 folder
    deps = [
        ":cJSON-1.7.15",        
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.c"],
    deps = [
        ":cJSON-1.7.15",        
        ":thingsboard",
    ],
)