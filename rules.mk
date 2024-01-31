PS2_MOUSE_ENABLE = yes
PS2_ENABLE = yes
PS2_DRIVER = busywait
AUDIO_ENABLE = yes
AUDIO_DRIVER = pwm_software
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
OLED_TRANSPORT = i2c
DEFAULT_FOLDER = bfb/blackpill/blackpill_f411
CUSTOM_MATRIX = lite
NKRO_ENABLE = no

SRC += matrix.c