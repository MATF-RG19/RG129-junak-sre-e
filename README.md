# RG129-junak-sre-e
Junak sreće

Kontrole: 
Igrac se moze kretati pomocu tastera AWDS, a za pucanj koristi taster K.

Funkcionisanje igre:

U prvom delu igre igrac treba da unisti sve neprijatelje kako bi mu se otvorila prva granica. Neprijatelji mogu da promene boju u crvenu na kraci vremenski period sto je upozorenje da ce neprijatelj uskoro da puca i da igrac treba da se pazi. Ako igrac dotakne neprijatelje ili ako bude pogodjen pucnjem neprijatelja on gubi zivot i restartuje se na pocetnu poziciju. Zivoti su predtavljeni preko srca. Jedno srce je jedan zivot a igrac ih na pocetku igre ima ukupno tri. Dokle god ima zivota kad izgubi njegov proces nije izgubljen(ubijeni neprijatelji su idalje ubijeni), ali ako izgubi i poslednje srce cela igrica se restartuje i svi prethodno unisteni neprijatelji se vracaju. 
Kad predje prvu zonu nestace ograda i pojavice se novi neprijatelji i prepreke. Druga vrsta neprijatelja je staticna i ju igrac ne moze da unisti svojim pucnjem vec mora da skupi kljuc kako bi unistio te neprijatelje. Taj put mu otezava to sto novi neprijatelji pucaju duze metkove u 4 pravca tako da mora biti oprezan da ne zakaci neki od metkova..... 

Pokretanje igre:
(za sada je samo tu cetvrta verzija)
gcc 4.c -lGL -lGLU -lglut -lm
