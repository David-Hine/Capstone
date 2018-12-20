EESchema Schematic File Version 4
LIBS:puck_design-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Microcontroller and peripherals"
Date "2018-11-21"
Rev "v01"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Author: Team 2"
$EndDescr
$Comp
L puck_library:TE832-M1 U3
U 1 1 5BF49E68
P 2450 4700
F 0 "U3" H 1975 5015 50  0000 C CNN
F 1 "TE832-M1" H 1975 4924 50  0000 C CNN
F 2 "" H 2000 5000 50  0001 C CNN
F 3 "" H 2000 5000 50  0001 C CNN
	1    2450 4700
	1    0    0    -1  
$EndComp
$Comp
L puck_library:BT840F U2
U 1 1 5C08C7CF
P 4600 2450
F 0 "U2" H 4600 3917 50  0000 C CNN
F 1 "BT840F" H 4600 3826 50  0000 C CNN
F 2 "XCVR_BT840F" H 4600 2450 50  0001 L BNN
F 3 "https://www.digikey.ca/product-detail/en/fanstel-corp/BT840F/1914-1019-1-ND/8323672?utm_source=snapeda&utm_medium=aggregator&utm_campaign=symbol" H 4600 2450 50  0001 L BNN
F 4 "BLE 5 Module: Nordic nRF52840 SoC _Range 930 Meters_" H 4600 2450 50  0001 L BNN "Field4"
F 5 "SMD-16 Fanstel" H 4600 2450 50  0001 L BNN "Field5"
F 6 "BT840F" H 4600 2450 50  0001 L BNN "Field6"
F 7 "Fanstel Corp." H 4600 2450 50  0001 L BNN "Field7"
F 8 "1914-1019-1-ND" H 4600 2450 50  0001 L BNN "Field8"
	1    4600 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C08C93F
P 1900 1750
F 0 "#PWR?" H 1900 1500 50  0001 C CNN
F 1 "GND" H 1905 1577 50  0000 C CNN
F 2 "" H 1900 1750 50  0001 C CNN
F 3 "" H 1900 1750 50  0001 C CNN
	1    1900 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 1550 1900 1550
Wire Wire Line
	1900 1550 1900 1450
Wire Wire Line
	2100 1250 1900 1250
Wire Wire Line
	2100 1350 1900 1350
Connection ~ 1900 1350
Wire Wire Line
	1900 1350 1900 1250
Wire Wire Line
	2100 1450 1900 1450
Connection ~ 1900 1450
Wire Wire Line
	1900 1450 1900 1350
$Comp
L power:GND #PWR?
U 1 1 5C094FBE
P 7250 3550
F 0 "#PWR?" H 7250 3300 50  0001 C CNN
F 1 "GND" H 7255 3377 50  0000 C CNN
F 2 "" H 7250 3550 50  0001 C CNN
F 3 "" H 7250 3550 50  0001 C CNN
	1    7250 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3950 3100 4250
Wire Wire Line
	4500 3950 4500 4250
Wire Wire Line
	5200 3950 5200 4200
$Comp
L Device:C C1
U 1 1 5C0A4E4C
P 7250 3400
F 0 "C1" H 7365 3446 50  0000 L CNN
F 1 "4.7uF" H 7365 3355 50  0000 L CNN
F 2 "" H 7288 3250 50  0001 C CNN
F 3 "~" H 7250 3400 50  0001 C CNN
	1    7250 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 3950 3200 4700
Wire Wire Line
	3300 4850 3300 3950
Wire Wire Line
	3400 5000 3400 3950
$Comp
L power:GND #PWR?
U 1 1 5C0FA8F0
P 1150 5950
F 0 "#PWR?" H 1150 5700 50  0001 C CNN
F 1 "GND" H 1155 5777 50  0000 C CNN
F 2 "" H 1150 5950 50  0001 C CNN
F 3 "" H 1150 5950 50  0001 C CNN
	1    1150 5950
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5C0FA933
P 750 4650
F 0 "#PWR?" H 750 4500 50  0001 C CNN
F 1 "VCC" H 767 4823 50  0000 C CNN
F 2 "" H 750 4650 50  0001 C CNN
F 3 "" H 750 4650 50  0001 C CNN
	1    750  4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  4650 750  4700
Wire Wire Line
	4900 4700 4900 3950
$Comp
L Device:C C2
U 1 1 5C133E91
P 1150 4850
F 0 "C2" H 1265 4896 50  0000 L CNN
F 1 "0.1uF" H 1265 4805 50  0000 L CNN
F 2 "" H 1188 4700 50  0001 C CNN
F 3 "~" H 1150 4850 50  0001 C CNN
	1    1150 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  4700 1150 4700
Connection ~ 1150 4700
Wire Wire Line
	1150 4700 1650 4700
$Comp
L Device:C CX
U 1 1 5C143212
P 3400 5400
F 0 "CX" H 3515 5446 50  0000 L CNN
F 1 "XuF" H 3515 5355 50  0000 L CNN
F 2 "" H 3438 5250 50  0001 C CNN
F 3 "~" H 3400 5400 50  0001 C CNN
	1    3400 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:C CX
U 1 1 5C145DBB
P 2950 5400
F 0 "CX" H 3065 5446 50  0000 L CNN
F 1 "XuF" H 3065 5355 50  0000 L CNN
F 2 "" H 2988 5250 50  0001 C CNN
F 3 "~" H 2950 5400 50  0001 C CNN
	1    2950 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:C CX
U 1 1 5C146CAE
P 2500 5400
F 0 "CX" H 2615 5446 50  0000 L CNN
F 1 "XuF" H 2615 5355 50  0000 L CNN
F 2 "" H 2538 5250 50  0001 C CNN
F 3 "~" H 2500 5400 50  0001 C CNN
	1    2500 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 5750 2950 5750
Wire Wire Line
	2950 5550 2950 5750
Connection ~ 2950 5750
Wire Wire Line
	2950 5750 3400 5750
Wire Wire Line
	3200 4700 2500 4700
Wire Wire Line
	2300 5000 3400 5000
Wire Wire Line
	3400 5750 3400 5550
Wire Wire Line
	2500 5750 2500 5550
Connection ~ 1150 5000
Wire Wire Line
	1150 5000 1650 5000
Connection ~ 2500 5750
Wire Wire Line
	2300 4850 2950 4850
Wire Wire Line
	1150 5000 1150 5750
Wire Wire Line
	1150 5750 2500 5750
Connection ~ 1150 5750
Wire Wire Line
	1150 5750 1150 5950
Wire Wire Line
	2500 5250 2500 4700
Connection ~ 2500 4700
Wire Wire Line
	2500 4700 2300 4700
Wire Wire Line
	2950 5250 2950 4850
Connection ~ 2950 4850
Wire Wire Line
	2950 4850 3300 4850
Wire Wire Line
	3400 5250 3400 5000
Connection ~ 3400 5000
$Comp
L puck_library:MCP73831-2 U4
U 1 1 5C1755A4
P 11050 5650
F 0 "U4" H 9025 8015 50  0000 C CNN
F 1 "MCP73831-2" H 9025 7924 50  0000 C CNN
F 2 "" H 9050 8050 50  0001 C CNN
F 3 "" H 9050 8050 50  0001 C CNN
	1    11050 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 5550 3900 5550
Wire Wire Line
	3900 5550 3900 3950
$Comp
L puck_library:ITG-3701 U1
U 1 1 5BF49DCF
P 5050 5400
F 0 "U1" H 5450 6100 50  0000 L CNN
F 1 "ITG-3701" H 5400 6000 50  0000 L CNN
F 2 "" H 5050 5400 50  0001 C CNN
F 3 "" H 5050 5400 50  0001 C CNN
	1    5050 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 5250 4300 5250
Wire Wire Line
	4300 5250 4300 3950
$Comp
L Device:C C4
U 1 1 5C19A914
P 5150 6350
F 0 "C4" H 5265 6396 50  0000 L CNN
F 1 "0.1uF" H 5265 6305 50  0000 L CNN
F 2 "" H 5188 6200 50  0001 C CNN
F 3 "~" H 5150 6350 50  0001 C CNN
	1    5150 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 6500 5150 6600
$Comp
L Device:R R1
U 1 1 5C1C106E
P 9600 4050
F 0 "R1" H 9670 4096 50  0000 L CNN
F 1 "20K" H 9670 4005 50  0000 L CNN
F 2 "" V 9530 4050 50  0001 C CNN
F 3 "~" H 9600 4050 50  0001 C CNN
	1    9600 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 1550 1900 1750
Connection ~ 1900 1550
$Comp
L Connector:Barrel_Jack J1
U 1 1 5C1E55FA
P 7950 3650
F 0 "J1" H 8005 3975 50  0000 C CNN
F 1 "Barrel_Jack" H 8005 3884 50  0000 C CNN
F 2 "" H 8000 3610 50  0001 C CNN
F 3 "~" H 8000 3610 50  0001 C CNN
	1    7950 3650
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5C1F6E15
P 7250 3250
F 0 "#PWR?" H 7250 3100 50  0001 C CNN
F 1 "VCC" H 7267 3423 50  0000 C CNN
F 2 "" H 7250 3250 50  0001 C CNN
F 3 "" H 7250 3250 50  0001 C CNN
	1    7250 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BH1
U 1 1 5C20407B
P 10000 4100
F 0 "BH1" H 10118 4196 50  0000 L CNN
F 1 "Battery Holder" H 10118 4105 50  0000 L CNN
F 2 "" V 10000 4160 50  0001 C CNN
F 3 "~" V 10000 4160 50  0001 C CNN
	1    10000 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 3550 10000 3550
$Comp
L power:GND #PWR?
U 1 1 5C171B07
P 5150 6600
F 0 "#PWR?" H 5150 6350 50  0001 C CNN
F 1 "GND" H 5155 6427 50  0000 C CNN
F 2 "" H 5150 6600 50  0001 C CNN
F 3 "" H 5150 6600 50  0001 C CNN
	1    5150 6600
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5C1763E4
P 4200 5100
F 0 "#PWR?" H 4200 4950 50  0001 C CNN
F 1 "VCC" H 4217 5273 50  0000 C CNN
F 2 "" H 4200 5100 50  0001 C CNN
F 3 "" H 4200 5100 50  0001 C CNN
	1    4200 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 5450 4200 5100
Wire Wire Line
	4200 5450 4350 5450
Wire Wire Line
	5150 6000 5150 6200
$Comp
L power:GND #PWR?
U 1 1 5C1952E8
P 5250 6000
F 0 "#PWR?" H 5250 5750 50  0001 C CNN
F 1 "GND" H 5255 5827 50  0000 C CNN
F 2 "" H 5250 6000 50  0001 C CNN
F 3 "" H 5250 6000 50  0001 C CNN
	1    5250 6000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C198C17
P 6750 5300
F 0 "#PWR?" H 6750 5050 50  0001 C CNN
F 1 "GND" H 6755 5127 50  0000 C CNN
F 2 "" H 6750 5300 50  0001 C CNN
F 3 "" H 6750 5300 50  0001 C CNN
	1    6750 5300
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5C1A6C20
P 6000 5500
F 0 "#PWR?" H 6000 5350 50  0001 C CNN
F 1 "VCC" H 6017 5673 50  0000 C CNN
F 2 "" H 6000 5500 50  0001 C CNN
F 3 "" H 6000 5500 50  0001 C CNN
	1    6000 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 5550 6000 5550
Wire Wire Line
	6000 5550 6000 5500
$Comp
L power:GND #PWR?
U 1 1 5C1AFCAE
P 3100 4250
F 0 "#PWR?" H 3100 4000 50  0001 C CNN
F 1 "GND" H 3105 4077 50  0000 C CNN
F 2 "" H 3100 4250 50  0001 C CNN
F 3 "" H 3100 4250 50  0001 C CNN
	1    3100 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C1B399E
P 3800 4250
F 0 "#PWR?" H 3800 4000 50  0001 C CNN
F 1 "GND" H 3805 4077 50  0000 C CNN
F 2 "" H 3800 4250 50  0001 C CNN
F 3 "" H 3800 4250 50  0001 C CNN
	1    3800 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C1B750E
P 4500 4250
F 0 "#PWR?" H 4500 4000 50  0001 C CNN
F 1 "GND" H 4505 4077 50  0000 C CNN
F 2 "" H 4500 4250 50  0001 C CNN
F 3 "" H 4500 4250 50  0001 C CNN
	1    4500 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C1B9448
P 5200 4250
F 0 "#PWR?" H 5200 4000 50  0001 C CNN
F 1 "GND" H 5205 4077 50  0000 C CNN
F 2 "" H 5200 4250 50  0001 C CNN
F 3 "" H 5200 4250 50  0001 C CNN
	1    5200 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 3950 3800 4250
Wire Wire Line
	5100 4200 5200 4200
Wire Wire Line
	5100 4200 5100 4700
Connection ~ 5200 4200
Wire Wire Line
	5200 4200 5200 4250
Wire Wire Line
	8250 3550 8700 3550
$Comp
L power:GND #PWR?
U 1 1 5C1E4D3E
P 8250 4050
F 0 "#PWR?" H 8250 3800 50  0001 C CNN
F 1 "GND" H 8255 3877 50  0000 C CNN
F 2 "" H 8250 4050 50  0001 C CNN
F 3 "" H 8250 4050 50  0001 C CNN
	1    8250 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C1E619E
P 7650 3000
F 0 "#PWR?" H 7650 2750 50  0001 C CNN
F 1 "GND" H 7655 2827 50  0000 C CNN
F 2 "" H 7650 3000 50  0001 C CNN
F 3 "" H 7650 3000 50  0001 C CNN
	1    7650 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 3200 10000 3550
Wire Wire Line
	10000 3550 10000 3900
Connection ~ 10000 3550
Wire Wire Line
	7100 3050 7100 3250
Wire Wire Line
	7100 3250 7250 3250
Connection ~ 7250 3250
Wire Wire Line
	7100 2850 7650 2850
Wire Wire Line
	7650 2850 7650 3000
Wire Wire Line
	8700 4400 5600 4400
Wire Wire Line
	5600 3950 5600 4400
Wire Wire Line
	8700 4050 8700 4400
Wire Wire Line
	9350 3800 9600 3800
Wire Wire Line
	9600 3800 9600 3900
Wire Wire Line
	9600 4400 9600 4200
Wire Wire Line
	9350 4050 9350 4400
Wire Wire Line
	9600 4400 9600 4500
$Comp
L power:GND #PWR?
U 1 1 5C2012D6
P 9600 4500
F 0 "#PWR?" H 9600 4250 50  0001 C CNN
F 1 "GND" H 9605 4327 50  0000 C CNN
F 2 "" H 9600 4500 50  0001 C CNN
F 3 "" H 9600 4500 50  0001 C CNN
	1    9600 4500
	1    0    0    -1  
$EndComp
Connection ~ 9600 4400
Wire Wire Line
	9350 4400 9600 4400
Wire Wire Line
	9600 4400 10000 4400
Wire Wire Line
	10000 4400 10000 4200
Wire Wire Line
	8250 4050 8250 3750
$Comp
L Battery_Management:BQ297xy U5
U 1 1 5C1BCCE4
P 9650 2450
F 0 "U5" H 9650 2817 50  0000 C CNN
F 1 "BQ297xy" H 9650 2726 50  0000 C CNN
F 2 "Package_SON:WSON-6_1.5x1.5mm_P0.5mm" H 9650 2800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/bq2970.pdf" H 9400 2650 50  0001 C CNN
	1    9650 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5C1BCFEB
P 6000 5800
F 0 "C5" H 6115 5846 50  0000 L CNN
F 1 "0.1uF" H 6115 5755 50  0000 L CNN
F 2 "" H 6038 5650 50  0001 C CNN
F 3 "~" H 6000 5800 50  0001 C CNN
	1    6000 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 5650 6000 5550
Connection ~ 6000 5550
Wire Wire Line
	6750 5250 6750 5300
Wire Wire Line
	5750 5250 6500 5250
Wire Wire Line
	6000 5950 6000 6100
Wire Wire Line
	6000 6100 6500 6100
Wire Wire Line
	6500 6100 6500 5250
Connection ~ 6500 5250
Wire Wire Line
	6500 5250 6750 5250
$Comp
L Device:C C3
U 1 1 5C1C3957
P 4200 5800
F 0 "C3" H 4315 5846 50  0000 L CNN
F 1 "0.1uF" H 4315 5755 50  0000 L CNN
F 2 "" H 4238 5650 50  0001 C CNN
F 3 "~" H 4200 5800 50  0001 C CNN
	1    4200 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 5450 4200 5650
Connection ~ 4200 5450
$Comp
L power:GND #PWR?
U 1 1 5C1C7CCF
P 4200 6000
F 0 "#PWR?" H 4200 5750 50  0001 C CNN
F 1 "GND" H 4205 5827 50  0000 C CNN
F 2 "" H 4200 6000 50  0001 C CNN
F 3 "" H 4200 6000 50  0001 C CNN
	1    4200 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 5950 4200 6000
Wire Wire Line
	4100 6400 5000 6400
Wire Wire Line
	5000 6000 5000 6400
Wire Wire Line
	4100 3950 4100 6400
$Comp
L puck_library:VBAT U?
U 1 1 5C1D3A49
P 9550 2600
F 0 "U?" H 10400 2200 50  0001 C CNN
F 1 "VBAT" H 10053 2050 50  0000 L CNN
F 2 "" H 10400 2200 50  0001 C CNN
F 3 "" H 10400 2200 50  0001 C CNN
	1    9550 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 3950 6600 4250
Wire Wire Line
	6600 4250 7100 4250
Wire Wire Line
	7100 4250 7100 4100
$Comp
L puck_library:VBAT U?
U 1 1 5C1DA232
P 6650 3500
F 0 "U?" H 7500 3100 50  0001 C CNN
F 1 "VBAT" H 7153 2950 50  0000 L CNN
F 2 "" H 7500 3100 50  0001 C CNN
F 3 "" H 7500 3100 50  0001 C CNN
	1    6650 3500
	1    0    0    -1  
$EndComp
$EndSCHEMATC
