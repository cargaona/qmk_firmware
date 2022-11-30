# SPCGear GK630K Tournament

![SPCGear GK630K](https://i.imgur.com/vxRSWAk.png)

A compact 87-key (TKL) wired gaming keyboard with RGB lighting.

* Keyboard Maintainer: [tfuxu](https://github.com/tfuxu)
* Based on original [Pull Request](https://github.com/SonixQMK/qmk_firmware/pull/133) by: [ppkt](https://github.com/ppkt)
    * and on Keychron C1 RGB by: [noldevin](https://github.com/noldevin)
* Hardware Availability: [SPCGear](https://spcgear.com/en/product/gk630k-tournament-kailh-red-rgb/)

## How to compile

Make example for this keyboard (after setting up your build environment):

    make spcgear/gk630k:default

Make example with VIA support:

    make spcgear/gk630k:via

## Flashing instructions:

1. Refer to [Bootloader](#bootloader) section to enter the bootloader mode
2. Download and open [Sonix Flasher](https://github.com/SonixQMK/sonix-flasher/releases/latest)
3. If not set already, select `SN32F24X` under 'Device', and `0x00` in 'qmk offset'
4. Click 'Flash QMK...' button, and select the correct QMK firmware

## Bootloader

Enter the bootloader in 4 ways:

* **Reboot option in Sonix Flasher**: If you are on stock firmware, download [Sonix Flasher](https://github.com/SonixQMK/sonix-flasher/releases/latest) and click 'Reboot to Bootloader' button
* **Keycode in layout**: Press `Fn + Esc` combination on keyboard
* **Bootmagic reset**: Hold down the ESC key and plug in the keyboard
* **Physical reset button**: Briefly short 3th pin (BOOT) of the MCU with GND pin

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
