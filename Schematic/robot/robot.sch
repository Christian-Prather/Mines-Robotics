EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Lab 3 Robot"
Date "2020-10-19"
Rev "Version 3"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Author: Christian Prather"
$EndDescr
$Comp
L MCU_Module:Arduino_UNO_R3 A1
U 1 1 5F8E5CBD
P 4000 3300
F 0 "A1" H 4000 4481 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 4000 4390 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 4000 3300 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 4000 3300 50  0001 C CNN
	1    4000 3300
	1    0    0    -1  
$EndComp
$Comp
L OPB620:OPB620 S2
U 1 1 5F8E7D7F
P 7150 2650
F 0 "S2" H 7100 3020 50  0000 C CNN
F 1 "OPB620" H 7100 2929 50  0000 C CNN
F 2 "Schematic:OPTO_OPB620" H 7150 2650 50  0001 L BNN
F 3 "Optex" H 7150 2650 50  0001 L BNN
	1    7150 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5F8EBF51
P 6050 2200
F 0 "R1" H 6120 2246 50  0000 L CNN
F 1 "10k" H 6120 2155 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5980 2200 50  0001 C CNN
F 3 "~" H 6050 2200 50  0001 C CNN
	1    6050 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5F8EF4E7
P 7500 2050
F 0 "R4" H 7570 2096 50  0000 L CNN
F 1 "10k" H 7570 2005 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7430 2050 50  0001 C CNN
F 3 "~" H 7500 2050 50  0001 C CNN
	1    7500 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5F8F058A
P 5000 2700
F 0 "R2" V 5207 2700 50  0000 C CNN
F 1 "330" V 5116 2700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4930 2700 50  0001 C CNN
F 3 "~" H 5000 2700 50  0001 C CNN
	1    5000 2700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 5F8F0A1B
P 6450 2750
F 0 "R3" V 6243 2750 50  0000 C CNN
F 1 "330" V 6334 2750 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6380 2750 50  0001 C CNN
F 3 "~" H 6450 2750 50  0001 C CNN
	1    6450 2750
	0    1    1    0   
$EndComp
$Comp
L Driver_Motor:L298HN U1
U 1 1 5F8F49D9
P 6650 4100
F 0 "U1" H 6650 4981 50  0000 C CNN
F 1 "L298HN" H 6650 4890 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-15_P2.54x2.54mm_StaggerOdd_Lead4.58mm_Vertical" H 6700 3450 50  0001 L CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000240.pdf" H 6800 4350 50  0001 C CNN
	1    6650 4100
	1    0    0    -1  
$EndComp
$Comp
L OPB620:OPB620 S1
U 1 1 5F8E73E2
P 5750 2600
F 0 "S1" H 5700 2970 50  0000 C CNN
F 1 "OPB620" H 5700 2879 50  0000 C CNN
F 2 "Schematic:OPTO_OPB620" H 5750 2600 50  0001 L BNN
F 3 "Optex" H 5750 2600 50  0001 L BNN
	1    5750 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 2300 4600 2300
Wire Wire Line
	4850 2300 4850 2700
Wire Wire Line
	5150 2700 5350 2700
Wire Wire Line
	6050 2350 6050 2400
Wire Wire Line
	6050 2050 5900 2050
Wire Wire Line
	4850 2050 4850 2300
Connection ~ 4850 2300
Text GLabel 4000 4400 3    50   Input ~ 0
GND
Text GLabel 5350 2500 0    50   Input ~ 0
GND
Text GLabel 6050 2700 3    50   Input ~ 0
GND
Text GLabel 6150 2400 2    50   Input ~ 0
PIN_8
Wire Wire Line
	6150 2400 6050 2400
Connection ~ 6050 2400
Wire Wire Line
	6050 2400 6050 2500
Text GLabel 3250 3500 0    50   Input ~ 0
PIN_8
Wire Wire Line
	4850 2700 4850 3150
Wire Wire Line
	4850 3150 6300 3150
Wire Wire Line
	6300 3150 6300 2750
Connection ~ 4850 2700
Wire Wire Line
	6600 2750 6750 2750
Wire Wire Line
	7450 2550 7500 2550
Wire Wire Line
	7500 2550 7500 2350
Wire Wire Line
	7500 1900 5900 1900
Wire Wire Line
	5900 1900 5900 2050
Connection ~ 5900 2050
Wire Wire Line
	5900 2050 4850 2050
Text GLabel 7450 2750 3    50   Input ~ 0
GND
Text GLabel 6750 2550 1    50   Input ~ 0
GND
Text GLabel 7650 2350 2    50   Input ~ 0
PIN_7
Wire Wire Line
	7650 2350 7500 2350
Connection ~ 7500 2350
Wire Wire Line
	7500 2350 7500 2200
Text GLabel 3250 3400 0    50   Input ~ 0
PIN_7
Wire Wire Line
	3250 3400 3500 3400
Wire Wire Line
	3250 3500 3500 3500
Text GLabel 6050 3600 0    50   Input ~ 0
PIN_9
Text GLabel 6050 3700 0    50   Input ~ 0
PIN_10
Text GLabel 6050 4000 0    50   Input ~ 0
PIN_5
Text GLabel 6050 4100 0    50   Input ~ 0
PIN_6
Text GLabel 3250 3600 0    50   Input ~ 0
PIN_9
Text GLabel 3300 3700 0    50   Input ~ 0
PIN_10
Text GLabel 3250 3200 0    50   Input ~ 0
PIN_5
Text GLabel 3250 3300 0    50   Input ~ 0
PIN_6
Wire Wire Line
	3250 3600 3500 3600
Wire Wire Line
	3300 3700 3500 3700
Wire Wire Line
	3250 3200 3500 3200
Wire Wire Line
	3250 3300 3500 3300
Wire Wire Line
	4100 4400 4100 4950
Wire Wire Line
	4100 4950 6650 4950
Wire Wire Line
	6650 4950 6650 4800
Wire Wire Line
	4600 2300 4600 3200
Wire Wire Line
	4600 3200 6750 3200
Wire Wire Line
	6750 3200 6750 3400
Connection ~ 4600 2300
Wire Wire Line
	4600 2300 4850 2300
Text GLabel 6650 3400 0    50   Input ~ 0
VIN
Text GLabel 3900 2300 0    50   Input ~ 0
VIN
$Comp
L Switch:SW_MEC_5E SW?
U 1 1 5F90EC23
P 9350 3200
F 0 "SW?" H 9350 3585 50  0000 C CNN
F 1 "SW_MEC_5E" H 9350 3494 50  0000 C CNN
F 2 "" H 9350 3500 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=1371" H 9350 3500 50  0001 C CNN
	1    9350 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 3100 9150 3200
Wire Wire Line
	9550 3100 9550 3200
Text GLabel 9100 3300 0    50   Input ~ 0
PIN_2
Text GLabel 9650 3350 2    50   Input ~ 0
GND
Wire Wire Line
	9100 3300 9100 3100
Wire Wire Line
	9100 3100 9150 3100
Connection ~ 9150 3100
Wire Wire Line
	9550 3100 9650 3100
Wire Wire Line
	9650 3100 9650 3350
Connection ~ 9550 3100
$EndSCHEMATC
