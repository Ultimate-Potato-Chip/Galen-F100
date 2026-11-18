idf_component_register(
    SRCS "main.c" "nv3052c.c"
    INCLUDE_DIRS "."
    REQUIRES esp_lcd driver
)
