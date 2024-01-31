Start menu: QMK MSYS
go to qmk_firmware directory

Make:
    
	qmk compile -kb bfb/blackpill/blackpill_f411 -km default

Flash:

	qmk flash -kb bfb/blackpill/blackpill_f411 -km default

https://docs.qmk.fm/#/getting_started_build_tools 
https://docs.qmk.fm/#/getting_started_make_guide
https://docs.qmk.fm/#/newbs

1. Press and hold    Boot
2. Press and release NRST
3. Release           Boot

(if this doesn't work - connect A10 to GND with a resistor)
(if there are still unknown issues - try updating QMK MSYS:  git pull --recurse-submodules) 

Creating images:
1. Photoshop, 128x32px, Grayscale, black BG. Draw an image with a pencil tool.
2. Save the image as JPG.
3. Go to https://javl.github.io/image2cpp/
4. Upload the JPG.
5. Canvas:				128x32
   Background color:	Black
   Code output format:	Plain bytes
   Draw mode:			Vertical - 1bit per pixel (even though the display is set as horizontal in QMK by default)
6. Generate code, copy and paste.


