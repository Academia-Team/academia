; Contains constants to make working with the raster functions easier.
;
; Copyright Academia Team 2023


; The maximum value for the x coordinate (in pixels) for a 32-bit wide raster
; image such that the entire image is still visible on the Atari ST's monochrome
; screen.
RAST32_MAX_VIS_X:	equ		608

; A value for the x coordinate (in pixels) for a 32-bit wide raster image such
; that the image would be horizontally centered on the Atari ST's monochrome
; screen.
RAST32_MID_VIS_X:	equ		304

; The value for the x coordinate (in pixels) for a 32-bit wide raster image such
; that half of the image is cropped off from the left.
RAST32_LHALF_X:		equ		-16

; The value for the x coordinate (in pixels) for a 32-bit wide raster image such
; that half of the image is cropped off from the right.
RAST32_RHALF_X:		equ		624

; The minimum value for the x coordinate (in pixels) for a 32-bit wide raster
; image such that part of the image is still visible on the Atari ST's
; monochrome screen.
RAST32_MIN_X:		equ		-31


; The maximum value for the x coordinate (in pixels) for a 16-bit wide raster
; image such that the entire image is still visible on the Atari ST's monochrome
; screen.
RAST16_MAX_VIS_X:	equ		624

; The value for the x coordinate (in pixels) for a 16-bit wide raster image such
; that half of the image is cropped off from the left.
RAST16_LHALF_X:		equ		-8

; The value for the x coordinate (in pixels) for a 16-bit wide raster image such
; that half of the image is cropped off from the right.
RAST16_RHALF_X:		equ		632

; A value for the x coordinate (in pixels) for a 16-bit wide raster image such
; that the image would be horizontally centered on the Atari ST's monochrome
; screen.
RAST16_MID_VIS_X:	equ		312

; The minimum value for the x coordinate (in pixels) for a 16-bit wide raster
; image such that part of the image is still visible on the Atari ST's
; monochrome screen.
RAST16_MIN_X:		equ		-15


; The maximum value for the x coordinate (in pixels) for a 8-bit wide raster
; image such that the entire image is still visible on the Atari ST's monochrome
; screen.
RAST8_MAX_VIS_X:	equ		632

; The value for the x coordinate (in pixels) for a 8-bit wide raster image such
; that half of the image is cropped off from the left.
RAST8_LHALF_X:		equ		-4

; The value for the x coordinate (in pixels) for a 8-bit wide raster image such
; that half of the image is cropped off from the right.
RAST8_RHALF_X:		equ		636

; A value for the x coordinate (in pixels) for a 8-bit wide raster image such
; that the image would be horizontally centered on the Atari ST's monochrome
; screen.
RAST8_MID_VIS_X:	equ		316

; The minimum value for the x coordinate (in pixels) for a 16-bit wide raster
; image such that part of the image is still visible on the Atari ST's
; monochrome screen.
RAST8_MIN_X:		equ		-7


; A value for the y coordinate (in pixels) for a 32 px high raster image such
; that the image would be vertically centered on the Atari ST's monochrome
; screen.
RAST32H_MID_VIS_Y:	equ		184

; The maximum value for the y coordinate (in pixels) for a 32 px high raster
; image such that the entire image is still visible on the Atari ST's monochrome
; screen.
RAST32H_MAX_VIS_Y:	equ		368

; The value for the y coordinate (in pixels) for a 32 px high raster image such
; that half of the image is cropped off from the top.
RAST32H_THALF_Y:	equ		-16

; The value for the y coordinate (in pixels) for a 32 px high raster image such
; that half of the image is cropped off from the bottom.
RAST32H_BHALF_Y:	equ		384

; The minimum value for the y coordinate (in pixels) for a 32 px high raster
; image such that part of the image is still visible on the Atari ST's
; monochrome screen.
RAST32H_MIN_Y:		equ		-31


; A value for the y coordinate (in pixels) for a 16 px high raster image such
; that the image would be vertically centered on the Atari ST's monochrome
; screen.
RAST16H_MID_VIS_Y:	equ		192

; The maximum value for the y coordinate (in pixels) for a 16 px high raster
; image such that the entire image is still visible on the Atari ST's monochrome
; screen.
RAST16H_MAX_VIS_Y:	equ		384

; The value for the y coordinate (in pixels) for a 16 px high raster image such
; that half of the image is cropped off from the top.
RAST16H_THALF_Y:	equ		-8

; The value for the x coordinate (in pixels) for a 16 px high raster image such
; that half of the image is cropped off from the bottom.
RAST16H_BHALF_Y:	equ		392

; The minimum value for the y coordinate (in pixels) for a 16 px high raster
; image such that part of the image is still visible on the Atari ST's
; screen.
RAST16H_MIN_Y:		equ		-15


; A value for the y coordinate (in pixels) for a 8 px high raster image such
; that the image would be vertically centered on the Atari ST's monochrome
; screen.
RAST8H_MID_VIS_Y:	equ		196

; The maximum value for the y coordinate (in pixels) for a 8 px high raster
; image such that the entire image is still visible on the Atari ST's monochrome
; screen.
RAST8H_MAX_VIS_Y:	equ		392

; The value for the y coordinate (in pixels) for a 8 px high raster image such
; that half of the image is cropped off from the top.
RAST8H_THALF_Y:		equ		-4

; The value for the x coordinate (in pixels) for a 8 px high raster image such
; that half of the image is cropped off from the bottom.
RAST8H_BHALF_Y:		equ		396

; The minimum value for the y coordinate (in pixels) for a 8 px high raster
; image such that part of the image is still visible on the Atari ST's
; monochrome screen.
RAST8H_MIN_Y:		equ		-7