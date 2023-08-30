# STRCK-Software
Software pro Smart Turtle Robot Car Kit

# Jak naprogramovat stavebnici
1. Stáhněte ze stránek https://github.com/leandraycz/STRCK-Software/releases nejnovější verzi software.
2. Stažený soubor rozbalte.
3. Stavebnici připojte k počítači pomocí USB kabelu.
4. Flashovací software spustíte příkazem "STRCK-Flasher.exe".
5. V roletce port zvolte COM port na kterém se nachází připojená stavebnice.
6. Klikněte na tlačítko "Flash!" a vyčkejte na dokončení.
7. Stavebnice je nyní naprogramována.

# Zapojení (digital)
0. NC
1. NC
2. Levý Line tracking sensor
3. IR přijímač
4. Prostřední Line tracking sensor
5. Pravý Line tracking sensor
6. Servo
7. NC
8. NC
9. Vstup modulu motorů IN1
10. Vstup modulu motorů IN2
11. Vstup modulu motorů IN4
12. Vstup modulu motorů IN3
13. NC

# Zapojení (analog)
URFO1 - Utrasonický modul (z leva)
1. pin VCC
2. pin Echo
3. pin trig
4. pin GND

# Ovládání
Program se ovládání pomoci dálkového IR ovladače dodávaného ke stavebnici nebo pomoci USB portu(pokročilí uživatelé). 
Tlačítko 1 až 3 přepíná herní módy. Tlačítka šipek slouží k ovládání pohybu stavebnice (herní mód 2), ovládání serva (herní mód 1). V herním módu 3 se program řidí pomocí Line tracking sensoru na spodní straně stavebnice.
