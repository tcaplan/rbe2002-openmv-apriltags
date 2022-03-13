Demonstrates communication with an Open MV camera using UART.

Pair with `openmv_scripts/apriltags_uart.py`.

See `images/camera-h7-pinout.png` for pinout of the Open MV camera (go to [[openmv.io]] for other camera versions). Defaults to UART 1.

The OpenMV camera is both 3.3V and 5V tolerant -- no need for level shifters.

You can test with both devices powered by USB. To run headless, save the script as `main.py` (see the Tools menu in the OpenMV IDE).