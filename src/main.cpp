// Achsentest V03
// basierend auf Code von Jonathan Haas, 2019

// V03
// verschiedene Baugruppen mit Motorachse und Sensor für Initialisierung
// können direkt an Hauptplatine angeschlossen und über LCD Menu angesteuert werden

// V0301
// 'alter Getriebemotor' mit aufgenommen um besser Vergleiche machen zu können
// Minebea Motor sowohl mit 1:30 als auch 1:76 Getriebe verwendbar

// V302
// Z-Achse Dauerlauf --> mFunc_startLongTimeRun
// wiederholt Ablauf in exampleRun[0] mit einer Pause von 9sec
// Anzeige der Wiederholungen in vPrintStatus

// Offen
// Nach Speichern der neuen Parameter war zumindest Achsenlänge noch auf dem alten Wert als SampleRun1 gestartet wurde
// User Axis 1  und User Axis 2 anlegen
// Dauerlauf noch keine Loops (User Axis)

// ## in settings auf weitere Achsen Umstellen
// ## bislang nur Axis One und Two definiert, aber nur Axis One verwendet -- AXIS_ONE steht für physikalische Endstufe am Kanal 1, AXIS_TWO ...
// ## in menucallbacks startexamplerun geht vPrintStatus nicht mit param (param verändert sich - wodurch?)
//## Back in den Menus entfernen --> in MENUCONTROL_h Anzahl der Menüpunkte ändern; direkte Aufrufe bei callbacks auf Initfahrt ID ändern

// V4.00
// Umstellung auf neue Menustruktur mit Achsenauswahl, danach Benutzung der Achse
// Parameter können in EEPROM abgelegt werden; Reset to default möglich

// V4.01 und V4.02
// Hinzufügen von Motorachsen
// Motorachse hier im Menu anlegen, LCD Menu Parameter anpassen
// in menucontrol.h die Anzahl der Menuelemente
// #define _LCDML_DISP_cnt    47           // gesamte Anzahl der Menuelemente
// in settings.h die neuen Achsentypen anlegen
// #define AXIS_TYPE_472_INJ_Z          11
// in settings.cpp die entsprechende Zweige für Parameter und spezielle Achsenabläufe anlegen

// V 4.03
// Anzeige von Version und Anzahl der realisierten Achsen am Startbilschirm
// Umbenennung bestehender Achsen auf Projektnummer + Benennung
// Polarität der Lichtschranke als Setting aufgenommen;
// Achsen 0430 und 0472 mit aufgenommen


// V 4.04 (Jonathan Haas)
// Das Menü-Layout und sämtliche Slit-Funktionen wurden von 'SF2 Slit V1.00' übernommen
// Erweiterungen:
// 'Clear EEPROM' wurde unter 'Select Parameter' hinzugefügt. Hiermit lässt sich der gesamte EEPROM-Speicherbereich auf Value '-1' setzen.
//
// Außerdem wurde eine C++ Klasse 'DigitControl' implementiert und optimiert um in Menüfunktionen mit der Dezimalstellen-Steuerung redundanten Code zu vermeiden. 
// Die Funktionen dieser Klasse sind in digitcontrol.cpp dokumentiert.
//
// Separate Hadware-Channels ('aStepper[u8motorIndex]' und 'aSettings[u8motorIndex]') wurden entfernt.
// Nun wird der Motor ausschließlich über das globale Objeckt 'stepMotor' angesteuert. Der Motor wird nach jedem Wechsel des Achsen-Typs mit den dementsprechenden PINs initialisiert.
// Hierfür steht die Funktion 'vInitializeMotor()' aus stepmotor.cpp bereit. Diese initalisiert den Motor anhand den globalen Settings 'sMotorSettings'. In besagtem Modul wurden 
// noch diverse andere Funktionen für die Ansteuerung des Motors implementiert.
//
// Auch für die Achsensettings steht nun wie angedeutet nur noch eine globale Struktur 'sMotorSettings' zur Verfügung. 
// 
// Die Finite State Machine wurde von dem Fsms-Modul in das Stepmotor-Modul integriert und somit entfernt.
//
// V4.05 (Markus S.)
// Für die Nutzung der SF2 monochromatoren wird der HW-Kanal Motor 4 gesplittet, so dass 2 Motoren angeschlossen werden können
// Das Signal Enable 4 teilen sich dabei die Motoren, Ansonsten alles für Motor 4 und Motor 5 angelegt
// Split-FLB und 2 Endstufen notwendig
// SF2 EX Grating (Motor 1) und OrderSort-Filter (Motor 2) mit aufgenommen
//
// Sobald in Menü die 2 auskommentierten Zeilen aktiviert werden --> Darstellungsprobleme
// fehlend: Einstellung der Wellenlänge über Cursor --> automatisches Einstellen der Order Sorting Filter
// Formel WL zu Schritte
//
// V4.06 (Jonathan Haas)
// Bugfix: Fehlerhafte Anzeige der Menüeinträge beseitigt.
// Durch setzten des '_LCDML_cfg_use_ram' defines in der "main.cpp" lässt sich der Bug beseitigen.
// Der Speicher für die Content Strings der Menüeinträge wird nun im Ram statt im Flash allokiert.
//
// Die Funktion "Use def. Axis Pos -> SF2 Wavelength -> Set Wavelength" wurde erweitert. Der automatisierte Wavelength Modus ist unter diesem Menüeintrag nun implementiert.
// Zusätzlich wurde der Wellenlängenbefehl zum Serial-Mode für den SF2 Monochromator hinzugefügt.
// Wie gewöhnlich lässt sich das Grating, sowie der Order-Sorting-Filter nun mit dem Befehl "w 520" auf die Wellenlänge 520 einstellen.
//
// V4.08 (Markus S.)
// Neue Linearisierung für SF2 mit Blitzlampe CLARIO 0202 --> bezogen auf Slit-Breite 2mm und Flüssigkeitslichtleiter D=3mm am Ausgang



// ToDo:
// - Portfolio der Achsen ergänzen.
// - Zusätzliche Variable für den Monochromatortyp zum Wellenlängenbefehl hinzufügen, damit sich ein beliebeiger Monochromatortyp im Serial-Mode definieren lässt.
// - "SF2 Ex Slits 0.5s" für "All Slits"



// Durch dieses Define wird der Speicher für die Content Strings der Menüeinträge nun im Ram statt im Flash allokiert.
// Dies ist für alle Nicht-Arduino-Boards notwendig.
#define _LCDML_cfg_use_ram


float Version = 4.08;
int NumOfAxis = 20;
int NumOfMono = 2;

#include "MotorDriver.h"

LCDMenuLib2_menu LCDML_0(255, 0, 0, NULL, NULL); // root menu element (do not change)
LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

LCDML_addAdvanced(0, LCDML_0, 1, NULL, "", mFunc_showAxisName, 0, _LCDML_TYPE_dynParam); // NULL = no menu function
LCDML_addAdvanced(1, LCDML_0, 2, NULL, "Use Axis", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(2, LCDML_0_2, 1,   NULL, "Enable", mFunc_enableMotor, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(3, LCDML_0_2, 2,   NULL, "Disable", mFunc_disableMotor, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(4, LCDML_0_2, 3,   NULL, "Init", mFunc_startInitRun, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(5, LCDML_0_2, 4,   NULL, "Serial Mode", mFunc_startSerialMode, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(6, LCDML_0_2, 5  , NULL, "Move wo Init to", mFunc_startMoveSteps, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(7, LCDML_0_2, 6,   NULL, "Move with Init to", mFunc_startMoveStepsInit, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(8, LCDML_0_2, 7,   NULL, "Step Loose Check", mFunc_startStepCheck, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(9, LCDML_0_2, 8,   NULL, "Long Time Run", mFunc_startLongTimeRun, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(10, LCDML_0_2, 9,  NULL, "Offset Run", mFunc_startOffsetRun, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(11, LCDML_0_2, 10, NULL, "Sample Run 1", mFunc_startExampleRun, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(12, LCDML_0_2, 11, NULL, "Sample Run 2", mFunc_startExampleRun, 1, _LCDML_TYPE_default);
LCDML_addAdvanced(13, LCDML_0_2, 12, NULL, "Zeropoint", mFunc_startMoveToSpecialPos, POS_LEFT, _LCDML_TYPE_default);
LCDML_addAdvanced(14, LCDML_0_2, 13, NULL, "Full Axis Range", mFunc_startMoveToSpecialPos, POS_RIGHT, _LCDML_TYPE_default);
LCDML_addAdvanced(15, LCDML_0_2, 14, NULL, "1/2 Axis Range", mFunc_startMoveToSpecialPos, POS_MIDDLE, _LCDML_TYPE_default);
LCDML_addAdvanced(16, LCDML_0, 3, NULL, "Select Parameter", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(17, LCDML_0_3, 1, NULL, "Status", mFunc_printStatus, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(18, LCDML_0_3, 2, NULL, "Set Speed", mFunc_setSpeed, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(19, LCDML_0_3, 3, NULL, "Set Acceleration", mFunc_setAcceleration, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(20, LCDML_0_3, 4, NULL, "Set Rotation Dir", mFunc_setRotationDir, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(21, LCDML_0_3, 5, NULL, "Set Sensor Polarity", mFunc_setSensorPolarity, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(22, LCDML_0_3, 6, NULL, "Set Vref", mFunc_setVref, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(23, LCDML_0_3, 7, NULL, "Set Axis Range", mFunc_setAxisRange, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(24, LCDML_0_3, 8, NULL, "Save Settings", mFunc_saveSettingsToEeprom, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(25, LCDML_0_3, 9, NULL, "Set Default Settings", mFunc_setDefaultSettings, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(26, LCDML_0_3, 10, NULL, "Clear EEPROM", mFunc_clearEeprom, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(27, LCDML_0, 4, NULL, "Use def. Axis Pos", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(28, LCDML_0_4, 1, NULL, "421 Objekt.Haydon", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(29, LCDML_0_4_1, 1, 0, "Linse FI", mFunc_startExampleRun, 2, _LCDML_TYPE_default);
LCDML_addAdvanced(30, LCDML_0_4_1, 2, 0, "Linse LUM", mFunc_startExampleRun, 3, _LCDML_TYPE_default);
LCDML_addAdvanced(31, LCDML_0_4_1, 3, 0, "Bottom Messung", mFunc_startExampleRun, 4, _LCDML_TYPE_default);
LCDML_addAdvanced(32, LCDML_0_4_1, 4, 0, "Init", mFunc_startExampleRun, 5, _LCDML_TYPE_default);
LCDML_addAdvanced(33, LCDML_0_4, 2, NULL, "430 Transport X", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(34, LCDML_0_4_2, 1, 0, "Plate Out left", mFunc_startExampleRun, 2, _LCDML_TYPE_default);
LCDML_addAdvanced(35, LCDML_0_4_2, 2, 0, "Plate Out right", mFunc_startExampleRun, 3, _LCDML_TYPE_default);
LCDML_addAdvanced(36, LCDML_0_4_2, 3, 0, "Detect Plate X", mFunc_startExampleRun, 4, _LCDML_TYPE_default);
LCDML_addAdvanced(37, LCDML_0_4_2, 4, 0, "100% ABS Value Pos", mFunc_startExampleRun, 5, _LCDML_TYPE_default);
LCDML_addAdvanced(38, LCDML_0_4, 3, NULL, "430 Transport Y", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(39, LCDML_0_4_3, 1, 0, "Plate Out Y", mFunc_startExampleRun, 2, _LCDML_TYPE_default);
LCDML_addAdvanced(40, LCDML_0_4_3, 2, 0, "Detect Plate Y", mFunc_startExampleRun, 3, _LCDML_TYPE_default);
LCDML_addAdvanced(41, LCDML_0_4_3, 3, 0, "100% ABS Value Pos", mFunc_startExampleRun, 4, _LCDML_TYPE_default);
LCDML_addAdvanced(42, LCDML_0_4, 4, NULL, "430 Exc Source", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(43, LCDML_0_4_4, 1, 0, "Blitzlampe", mFunc_startExampleRun, 2, _LCDML_TYPE_default);
LCDML_addAdvanced(44, LCDML_0_4_4, 2, 0, "IR Blocker", mFunc_startExampleRun, 3, _LCDML_TYPE_default);
LCDML_addAdvanced(45, LCDML_0_4_4, 3, 0, "AS Laser", mFunc_startExampleRun, 4, _LCDML_TYPE_default);
LCDML_addAdvanced(46, LCDML_0_4_4, 4, 0, "LED Kopplung", mFunc_startExampleRun, 5, _LCDML_TYPE_default);
LCDML_addAdvanced(47, LCDML_0_4, 5, NULL, "430 top/bottom", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(48, LCDML_0_4_5, 1, 0, "Lichtweg offen", mFunc_startExampleRun, 2, _LCDML_TYPE_default);
LCDML_addAdvanced(49, LCDML_0_4_5, 2, 0, "LUM Linse in Pfad", mFunc_startExampleRun, 3, _LCDML_TYPE_default);
LCDML_addAdvanced(50, LCDML_0_4_5, 3, 0, "Spiegel bottom", mFunc_startExampleRun, 4, _LCDML_TYPE_default);
LCDML_addAdvanced(51, LCDML_0_4, 6, NULL, "430 PMT Achse", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(52, LCDML_0_4_6, 1, 0, "Extended IR PMT", mFunc_startExampleRun, 2, _LCDML_TYPE_default);
LCDML_addAdvanced(53, LCDML_0_4_6, 2, 0, "LUM PMT", mFunc_startExampleRun, 3, _LCDML_TYPE_default);
LCDML_addAdvanced(54, LCDML_0_4, 7, NULL, "SF2 Ex Slit In", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(55, LCDML_0_4_7, 1, 0, "  4 mm", mFunc_startExampleRun, 2, _LCDML_TYPE_default);
LCDML_addAdvanced(56, LCDML_0_4_7, 2, 0, "  3 mm", mFunc_startExampleRun, 3, _LCDML_TYPE_default);
LCDML_addAdvanced(57, LCDML_0_4_7, 3, 0, "  2 mm", mFunc_startExampleRun, 4, _LCDML_TYPE_default);
LCDML_addAdvanced(58, LCDML_0_4_7, 4, 0, "  1 mm", mFunc_startExampleRun, 5, _LCDML_TYPE_default);
LCDML_addAdvanced(59, LCDML_0_4_7, 5, 0, "0.5 mm", mFunc_startExampleRun, 6, _LCDML_TYPE_default);
LCDML_addAdvanced(60, LCDML_0_4, 8, NULL, "SF2 Ex Slit Mid", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(61, LCDML_0_4_8, 1, 0, "  4 mm", mFunc_startExampleRun, 2, _LCDML_TYPE_default);
LCDML_addAdvanced(62, LCDML_0_4_8, 2, 0, "  3 mm", mFunc_startExampleRun, 3, _LCDML_TYPE_default);
LCDML_addAdvanced(63, LCDML_0_4_8, 3, 0, "  2 mm", mFunc_startExampleRun, 4, _LCDML_TYPE_default);
LCDML_addAdvanced(64, LCDML_0_4_8, 4, 0, "  1 mm", mFunc_startExampleRun, 5, _LCDML_TYPE_default);
LCDML_addAdvanced(65, LCDML_0_4_8, 5, 0, "0.5 mm", mFunc_startExampleRun, 6, _LCDML_TYPE_default);
LCDML_addAdvanced(66, LCDML_0_4, 9, NULL, "SF2 Ex Slit Out", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(67, LCDML_0_4_9, 1, 0, "  4 mm", mFunc_startExampleRun, 2, _LCDML_TYPE_default);
LCDML_addAdvanced(68, LCDML_0_4_9, 2, 0, "  3 mm", mFunc_startExampleRun, 3, _LCDML_TYPE_default);
LCDML_addAdvanced(69, LCDML_0_4_9, 3, 0, "  2 mm", mFunc_startExampleRun, 4, _LCDML_TYPE_default);
LCDML_addAdvanced(70, LCDML_0_4_9, 4, 0, "  1 mm", mFunc_startExampleRun, 5, _LCDML_TYPE_default);
LCDML_addAdvanced(71, LCDML_0_4_9, 5, 0, "0.5 mm", mFunc_startExampleRun, 6, _LCDML_TYPE_default);
LCDML_addAdvanced(72, LCDML_0_4, 10, NULL, "SF2 Ex all Slits", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(73, LCDML_0_4_10, 1, 0, "  4 mm", mFunc_startSlitsRun, 2, _LCDML_TYPE_default);
LCDML_addAdvanced(74, LCDML_0_4_10, 2, 0, "  3 mm", mFunc_startSlitsRun, 3, _LCDML_TYPE_default);
LCDML_addAdvanced(75, LCDML_0_4_10, 3, 0, "  2 mm", mFunc_startSlitsRun, 4, _LCDML_TYPE_default);
LCDML_addAdvanced(76, LCDML_0_4_10, 4, 0, "  1 mm", mFunc_startSlitsRun, 5, _LCDML_TYPE_default);
LCDML_addAdvanced(77, LCDML_0_4_10, 5, 0, "0.5 mm", mFunc_startSlitsRun, 6, _LCDML_TYPE_default);

LCDML_addAdvanced(78, LCDML_0_4, 11, NULL, "SF2 Ex Slits 0.5s", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(79, LCDML_0_4_11, 1, NULL, "SF2 Ex Slit In",mFunc_startSlitStepRun, AXIS_TYPE_SF2_EX_SLIT_IN, _LCDML_TYPE_default);
LCDML_addAdvanced(80, LCDML_0_4_11, 2, NULL, "SF2 Ex Slit Mid", mFunc_startSlitStepRun, AXIS_TYPE_SF2_EX_SLIT_MID, _LCDML_TYPE_default);
LCDML_addAdvanced(81, LCDML_0_4_11, 3, NULL, "SF2 Ex Slit Out", mFunc_startSlitStepRun, AXIS_TYPE_SF2_EX_SLIT_OUT, _LCDML_TYPE_default);

LCDML_addAdvanced(82, LCDML_0_4, 12, NULL, "SF2 Wavelength", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(83, LCDML_0_4_12, 1, 0, "Set Wavelength", mFunc_startWLRun, MON_TYPE_SF2, _LCDML_TYPE_default);
LCDML_addAdvanced(84, LCDML_0_4, 13, NULL, "SF2 Order Sorting", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(85, LCDML_0_4_13, 1, 0, "200 < WL <= 325", mFunc_startExampleRun, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(86, LCDML_0_4_13, 2, 0, "325 < WL <= 520", mFunc_startExampleRun, 1, _LCDML_TYPE_default);
LCDML_addAdvanced(87, LCDML_0_4_13, 3, 0, "520 < WL <= 1000", mFunc_startExampleRun, 2, _LCDML_TYPE_default);
LCDML_addAdvanced(88, LCDML_0_4, 14, NULL, "H1512 Wavelength", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(89, LCDML_0_4_14, 1, 0, "Set Wavelength", mFunc_startWLRun, MON_TYPE_H1512, _LCDML_TYPE_default);


LCDML_addAdvanced(90, LCDML_0, 5,    NULL, "Choose Axis Type", 0, 0, _LCDML_TYPE_default);
LCDML_addAdvanced(91, LCDML_0_5, 1,  NULL, "421 X-Transport", mFunc_initSettings, AXIS_TYPE_421_TRANSPORT_X, _LCDML_TYPE_default);
LCDML_addAdvanced(92, LCDML_0_5, 2,  NULL, "421 Y-Transport", mFunc_initSettings, AXIS_TYPE_421_TRANSPORT_Y, _LCDML_TYPE_default);
LCDML_addAdvanced(93, LCDML_0_5, 3,  NULL, "421 MPC Z 1:30", mFunc_initSettings, AXIS_TYPE_421_MPC_Z_3, _LCDML_TYPE_default);
LCDML_addAdvanced(94, LCDML_0_5, 4,  NULL, "421 MPC Z Spindle", mFunc_initSettings, AXIS_TYPE_421_MPC_Z_4, _LCDML_TYPE_default);
LCDML_addAdvanced(95, LCDML_0_5, 5,  NULL, "421 Objekt.Haydon", mFunc_initSettings, AXIS_TYPE_421_LENS_CHANGE, _LCDML_TYPE_default);
LCDML_addAdvanced(96, LCDML_0_5, 6,  NULL, "430 X-Transport", mFunc_initSettings, AXIS_TYPE_430_TRANSPORT_X, _LCDML_TYPE_default);
LCDML_addAdvanced(97, LCDML_0_5, 7,  NULL, "430 Y-Transport", mFunc_initSettings, AXIS_TYPE_430_TRANSPORT_Y, _LCDML_TYPE_default);
LCDML_addAdvanced(98, LCDML_0_5, 8,  NULL, "430 top Optic Z", mFunc_initSettings, AXIS_TYPE_430_TOP_OPTIC_Z, _LCDML_TYPE_default);
LCDML_addAdvanced(99, LCDML_0_5, 9,  NULL, "430 top/bottom", mFunc_initSettings, AXIS_TYPE_430_TOP_BOTTOM, _LCDML_TYPE_default);
LCDML_addAdvanced(100, LCDML_0_5, 10, NULL, "430 bot Optic Z", mFunc_initSettings, AXIS_TYPE_430_BOT_OPTIC_Z, _LCDML_TYPE_default);
LCDML_addAdvanced(101, LCDML_0_5, 11, NULL, "430 Exc Source", mFunc_initSettings, AXIS_TYPE_430_EX_SOURCE, _LCDML_TYPE_default);
LCDML_addAdvanced(102, LCDML_0_5, 12, NULL, "430 PMT-Achse", mFunc_initSettings, AXIS_TYPE_430_PMT_AXIS, _LCDML_TYPE_default);
LCDML_addAdvanced(103, LCDML_0_5, 13, NULL, "472 Injector X", mFunc_initSettings, AXIS_TYPE_472_INJ_X, _LCDML_TYPE_default);
LCDML_addAdvanced(104, LCDML_0_5, 14, NULL, "472 Injector Z", mFunc_initSettings, AXIS_TYPE_472_INJ_Z, _LCDML_TYPE_default);
LCDML_addAdvanced(105, LCDML_0_5, 15, NULL, "User Axis", mFunc_initSettings, AXIS_TYPE_USER, _LCDML_TYPE_default);
LCDML_addAdvanced(106, LCDML_0_5, 16, NULL, "SF2 Ex Slit In", mFunc_initSettings, AXIS_TYPE_SF2_EX_SLIT_IN, _LCDML_TYPE_default);
LCDML_addAdvanced(107, LCDML_0_5, 17, NULL, "SF2 Ex Slit Mid", mFunc_initSettings, AXIS_TYPE_SF2_EX_SLIT_MID, _LCDML_TYPE_default);
LCDML_addAdvanced(108, LCDML_0_5, 18, NULL, "SF2 Ex Slit Out", mFunc_initSettings, AXIS_TYPE_SF2_EX_SLIT_OUT, _LCDML_TYPE_default);
LCDML_addAdvanced(109, LCDML_0_5, 19, NULL, "SF2 Ex Grating", mFunc_initSettings, AXIS_Type_SF2_Grating, _LCDML_TYPE_default);
LCDML_addAdvanced(110, LCDML_0_5, 20, NULL, "SF2 Ex OrderFilter", mFunc_initSettings, AXIS_Type_SF2_OrderSort, _LCDML_TYPE_default);
// create menu
LCDML_createMenu(_LCDML_DISP_cnt);

void setup()
{
  // LCD löschen (nach Reset)
  lcd.clear();
  // Warte auf LCD (wegen Power up)
  delay(LCD_SHOW_DELAY);
  // LCD Init
  lcd.init();
  lcd.clear();
  lcd.setBacklight(100);
  lcd.setPosition(0, 0);
  lcd.printf(" Achsentestgeraet ");
  lcd.setPosition(0, 2);
  lcd.printf(" Version %.2f", Version);
  lcd.setPosition(0, 3);
  lcd.printf(" %i Achsen, %i Monos", NumOfAxis, NumOfMono);
  delay(LCD_SHOW_DELAY);

  // Lade zuerst die Settings (aus EEPROM oder Default) und konfiguriere anschließend die Motor-Hardware
  vInitializeSettings();
  vInitializeMotor();
  // Lade die Samples anhand des Achsen-Typs
  vSetExampleRuns(sMotorSettings.u8axisType);

  Serial.begin(9600);

  pinMode(PIN_LSSIG_TXA, INPUT);

  // setup joystick pins
  pinMode(PIN_JOYSTICK_UP, INPUT_PULLUP);
  pinMode(PIN_JOYSTICK_RIGHT, INPUT_PULLUP);
  pinMode(PIN_JOYSTICK_DOWN, INPUT_PULLUP);
  pinMode(PIN_JOYSTICK_LEFT, INPUT_PULLUP);
  pinMode(PIN_JOYSTICK_CENTRE, INPUT_PULLUP);

  // LCDMenuLib Setup
  LCDML_setup(_LCDML_DISP_cnt);

  // Enable Menu Rollover
  LCDML.MENU_enRollover();
}

void loop()
{
  LCDML.loop();
}

void lcdml_menu_display()
/* ******************************************************************** */
{
  // update content
  // ***************
  if (LCDML.DISP_checkMenuUpdate())
  {
    // clear menu
    // ***************
    LCDML.DISP_clear();

    // declaration of some variables
    // ***************
    // content variable
    char content_text[_LCDML_DISP_cols]; // save the content text of every menu element

    // menu element object
    LCDMenuLib2_menu *tmp;
    // some limit values
    uint8_t i = LCDML.MENU_getScroll();
    uint8_t maxi = _LCDML_DISP_rows + i;
    uint8_t n = 0;

    // check if this element has children
    if ((tmp = LCDML.MENU_getDisplayedObj()) != NULL)
    {
      // loop to display lines
      do
      {
        // check if a menu element has a condition and if the condition be true
        if (tmp->checkCondition())
        {
          // check the type off a menu element
          if (tmp->checkType_menu() == true)
          {
            // display normal content
            LCDML_getContent(content_text, tmp->getID());
            lcd.setPosition(1, n);
            lcd.print(content_text);

          }
          else
          {
            if (tmp->checkType_dynParam())
            {
              tmp->callback(n);
            }
          }
          // increment some values
          i++;
          n++;
        }
        // try to go to the next sibling and check the number of displayed rows
      } while (((tmp = tmp->getSibling(1)) != NULL) && (i < maxi));
    }
  }

  if (LCDML.DISP_checkMenuCursorUpdate())
  {
    // init vars
    uint8_t n_max = (LCDML.MENU_getChilds() >= _LCDML_DISP_rows) ? _LCDML_DISP_rows : (LCDML.MENU_getChilds());
    uint8_t scrollbar_min = 0;
    uint8_t scrollbar_max = LCDML.MENU_getChilds();
    uint8_t scrollbar_cur_pos = LCDML.MENU_getCursorPosAbs();
    uint8_t scroll_pos = ((1. * n_max * _LCDML_DISP_rows) / (scrollbar_max - 1) * scrollbar_cur_pos);

    // display rows
    for (uint8_t n = 0; n < n_max; n++)
    {
      //set cursor
      lcd.setPosition(0, n);

      //set cursor char
      if (n == LCDML.MENU_getCursorPos())
      {
        lcd.write(_LCDML_DISP_cfg_cursor);
      }
      else
      {
        lcd.write(' ');
      }

      // delete or reset scrollbar
      if (_LCDML_DISP_cfg_scrollbar == 1)
      {
        if (scrollbar_max > n_max)
        {
          lcd.setPosition((_LCDML_DISP_cols - 1), n);
          lcd.write((uint8_t)0);
        }
        else
        {
          lcd.setPosition((_LCDML_DISP_cols - 1), n);
          lcd.print(' ');
        }
      }
    }

    // display scrollbar
    if (_LCDML_DISP_cfg_scrollbar == 1)
    {
      if (scrollbar_max > n_max)
      {
        //set scroll position
        if (scrollbar_cur_pos == scrollbar_min)
        {
          // min pos
          lcd.setPosition((_LCDML_DISP_cols - 1), 0);
          lcd.write((uint8_t)1);
        }
        else if (scrollbar_cur_pos == (scrollbar_max - 1))
        {
          // max pos
          lcd.setPosition((_LCDML_DISP_cols - 1), (n_max - 1));
          lcd.write((uint8_t)4);
        }
        else
        {
          // between
          lcd.setPosition((_LCDML_DISP_cols - 1), scroll_pos / n_max);
          lcd.write((uint8_t)(scroll_pos % n_max) + 1);
        }
      }
    }
  }
}
