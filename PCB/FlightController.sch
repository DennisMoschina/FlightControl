EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RF_Module:ESP32-WROOM-32 U?
U 1 1 6107FEF9
P 3450 2800
F 0 "U?" H 3450 4381 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 3450 4290 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 3450 1300 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 3150 2850 50  0001 C CNN
	1    3450 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR?
U 1 1 61086C35
P 3450 4200
F 0 "#PWR?" H 3450 3950 50  0001 C CNN
F 1 "GNDD" H 3454 4045 50  0000 C CNN
F 2 "" H 3450 4200 50  0001 C CNN
F 3 "" H 3450 4200 50  0001 C CNN
	1    3450 4200
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 6108CFDB
P 3450 950
F 0 "#PWR?" H 3450 800 50  0001 C CNN
F 1 "VDD" H 3465 1123 50  0000 C CNN
F 2 "" H 3450 950 50  0001 C CNN
F 3 "" H 3450 950 50  0001 C CNN
	1    3450 950 
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR?
U 1 1 6108E6E5
P 8000 3150
F 0 "#PWR?" H 8000 2900 50  0001 C CNN
F 1 "GNDD" H 8004 2995 50  0000 C CNN
F 2 "" H 8000 3150 50  0001 C CNN
F 3 "" H 8000 3150 50  0001 C CNN
	1    8000 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 2700 8000 3150
Wire Wire Line
	3450 950  3450 1400
$Comp
L Sensor_Motion:MPU-6000 U?
U 1 1 610915D7
P 8000 2000
F 0 "U?" H 8000 2881 50  0000 C CNN
F 1 "MPU-6000" H 8000 2790 50  0000 C CNN
F 2 "Sensor_Motion:InvenSense_QFN-24_4x4mm_P0.5mm" H 8000 1200 50  0001 C CNN
F 3 "https://store.invensense.com/datasheets/invensense/MPU-6050_DataSheet_V3%204.pdf" H 8000 1850 50  0001 C CNN
	1    8000 2000
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 610938B9
P 8000 1000
F 0 "#PWR?" H 8000 850 50  0001 C CNN
F 1 "VDD" H 8015 1173 50  0000 C CNN
F 2 "" H 8000 1000 50  0001 C CNN
F 3 "" H 8000 1000 50  0001 C CNN
	1    8000 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 1300 8000 1000
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 61094D58
P 4750 1700
F 0 "J?" H 4722 1582 50  0000 R CNN
F 1 "Conn_01x02_Male" H 4722 1673 50  0000 R CNN
F 2 "" H 4750 1700 50  0001 C CNN
F 3 "~" H 4750 1700 50  0001 C CNN
	1    4750 1700
	-1   0    0    1   
$EndComp
Wire Wire Line
	4050 1600 4550 1600
$Comp
L power:GNDD #PWR?
U 1 1 61098577
P 4550 1700
F 0 "#PWR?" H 4550 1450 50  0001 C CNN
F 1 "GNDD" H 4554 1545 50  0000 C CNN
F 2 "" H 4550 1700 50  0001 C CNN
F 3 "" H 4550 1700 50  0001 C CNN
	1    4550 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 1600 2850 950 
Wire Wire Line
	2850 950  3450 950 
Connection ~ 3450 950 
$Comp
L Connector_Generic:Conn_02x07_Odd_Even J?
U 1 1 6109BC10
P 3400 5550
F 0 "J?" H 3450 6067 50  0000 C CNN
F 1 "Conn_02x07_Odd_Even" H 3450 5976 50  0000 C CNN
F 2 "" H 3400 5550 50  0001 C CNN
F 3 "~" H 3400 5550 50  0001 C CNN
	1    3400 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 5850 3700 5750
Connection ~ 3700 5350
Wire Wire Line
	3700 5350 3700 5250
Connection ~ 3700 5450
Wire Wire Line
	3700 5450 3700 5350
Connection ~ 3700 5550
Wire Wire Line
	3700 5550 3700 5450
Connection ~ 3700 5650
Wire Wire Line
	3700 5650 3700 5550
Connection ~ 3700 5750
Wire Wire Line
	3700 5750 3700 5650
Wire Wire Line
	3200 5850 3200 5750
Connection ~ 3200 5350
Wire Wire Line
	3200 5350 3200 5250
Connection ~ 3200 5450
Wire Wire Line
	3200 5450 3200 5350
Connection ~ 3200 5550
Wire Wire Line
	3200 5550 3200 5450
Connection ~ 3200 5650
Wire Wire Line
	3200 5650 3200 5550
Connection ~ 3200 5750
Wire Wire Line
	3200 5750 3200 5650
$Comp
L power:GNDD #PWR?
U 1 1 6109E8A9
P 3700 5850
F 0 "#PWR?" H 3700 5600 50  0001 C CNN
F 1 "GNDD" H 3704 5695 50  0000 C CNN
F 2 "" H 3700 5850 50  0001 C CNN
F 3 "" H 3700 5850 50  0001 C CNN
	1    3700 5850
	1    0    0    -1  
$EndComp
Connection ~ 3700 5850
$Comp
L power:VSS #PWR?
U 1 1 610A0D8F
P 3200 5850
F 0 "#PWR?" H 3200 5700 50  0001 C CNN
F 1 "VSS" H 3215 6023 50  0000 C CNN
F 2 "" H 3200 5850 50  0001 C CNN
F 3 "" H 3200 5850 50  0001 C CNN
	1    3200 5850
	-1   0    0    1   
$EndComp
Connection ~ 3200 5850
$EndSCHEMATC
