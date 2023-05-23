# Kontroll av indikator LEDs på NIR-prototype

### void initLedPins(void);
Funksjon som initierer alle pinnene som LED-ene er koblet til.

## Grønn LED
Den grønne LED-en brukes for å indikere status på forsøket.
Koblet til pinne 42 (PORTL PIN7)

### void greenLedOn(void);
Skrur grønn led på. 
Skrus på når det er et pågående forsøk.

### void greenLedBlink(void);
Skrur grønn LED av og på med 500 ms tidsintervall. 
Brukes ikke.

### void greenLedOff(void);
Skrur grønn LED av. 
Brukes når forsøket avsluttes.

## Rød LED
Skal indikere feil i systemet.
Koblet til pinne 41 (PORTG PIN0)

### void redLedOn(void);
Skrur rød LED på. 
Brukes ved kritisk feil i systemet.

### void redLedBlink(void);
Skrur rød LED av og på med 500 ms tidsintervall. 
Brukes for å indikere mindre feil i systemet.

### void redLedOff(void);
Skrur rød LED av.
Brukes når det ikke er noen feil i systemet.

## Indikator LED på LED-hode
Denne LED-en skal fortelle nåer det er et pågående forsøk.
Når LED lyse må ikke LED-hode rettes mot øyne da lyset vil kunne gjøre skade over tid.
Koblet til pinne 40 (PORTG PIN1)

### void testIndicatorOn(void);
Funksjon som skrur på test Indikator LED. Brukes før forsøk starter.

### void testIndicatorOff(void);
Funksjon som srur test indikator LED av. Brukes når forsøk avsluttes.



