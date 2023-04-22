; Contains constants to make working with the raster functions easier.
;
; Copyright Academia Team 2023


; The maximum value for the x coordinate (in pixels) for a 32-bit wide
; raster image such that the entire image is still visible on the Atari ST's
; monochrome screen.
RAST32_MAX_VIS_X:	equ	608

; A value for the x coordinate (in pixels) for a 32-bit wide raster
; image such that the image would be horizontally centered on the Atari ST's
; monochrome screen.
RAST32_MID_VIS_X:	equ	304

; The minimum value for the x coordinate (in pixels) for a 32-bit wide
; raster image such that part of the image is still visible on the Atari ST's
; monochrome screen.
RAST32_MIN_X:	equ	-31


; The maximum value for the x coordinate (in pixels) for a 16-bit wide
; raster image such that the entire image is still visible on the Atari ST's
; monochrome screen.
RAST16_MAX_VIS_X:	equ	624

; A value for the x coordinate (in pixels) for a 16-bit wide raster
; image such that the image would be horizontally centered on the Atari ST's
; monochrome screen.
RAST16_MID_VIS_X:	equ	312

; The minimum value for the x coordinate (in pixels) for a 16-bit wide
; raster image such that part of the image is still visible on the Atari ST's
; monochrome screen.
RAST16_MIN_X:	equ	-15


; The maximum value for the x coordinate (in pixels) for a 8-bit wide
; raster image such that the entire image is still visible on the Atari ST's
; monochrome screen.
RAST8_MAX_VIS_X:	equ	632

; A value for the x coordinate (in pixels) for a 8-bit wide raster
; image such that the image would be horizontally centered on the Atari ST's
; monochrome screen.
RAST8_MID_VIS_X:	equ	316

; The minimum value for the x coordinate (in pixels) for a 16-bit wide
; raster image such that part of the image is still visible on the Atari ST's
; monochrome screen.
RAST8_MIN_X:		equ	-7