set(pri_req include)
idf_component_register(SRCS "app_main.c"
                    INCLUDE_DIRS "."
                    REQUIRES ${pri_req})