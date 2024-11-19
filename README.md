Project to familiarize myself with Zephyr RTOS, Device Tree and Zephyr bindings while also understanding the capabilites of the stm32f103C8T6 bluepill clone I've recently obtained. See ZEPHYR_COMMIT_HASH.txt to enable rolling back the state of the Zephyr repo to the state it was in when this project was last built successfully.

Optimizations have been disabled in prj.conf to facilitate debugging, which also increases the amount of flash required considerably. The clone of the "stm32 bluepill" board that I have includes 128k flash. The original Bluepill has 64k, so if you have one of these you probably need to comment out CONFIG_NO_OPTIMIZATIONS=y in prj.conf to get it to work on your board.

The python script serial-terminal.py is useful if you need to interact with the zephyr shell. At the time it was easier than trying to figure out how to interact with zephyr shell with vscode's serial monitor extension, which does work fine for monitoring. You'll need to edit the script for your com port - never got around to making it configurable.
