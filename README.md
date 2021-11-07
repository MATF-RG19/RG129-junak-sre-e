# RG129-junak-sre-e
Junak sreće

Kontrole: 
Igrac se moze kretati pomocu tastera AWDS, a za pucanj koristi taster K.

Precice:    
n/N - preskace najavnu spicu(pocetnu animaciju)   
p/P - precica za preskakanje prvog sektora    
o/O - pokrece krajnju animaciju   

Tok igre:         
Pocetna animacija: vestica krade sliku iz muzeja i bezi kroz portal, a za njom krece kugla sa stuba koja je ustvari macka.  
Prvi nivo: cilj je upucati sve neprijatelje kako bi granica nestala i zapoceo drugi nivo.    
Drgi nivo: cilj je skupiti pravi kljuc za otvaranje druge granice i izaci iz lavirinta.    
Zavrsna animacija(kraj igre): kraj igre je kad igrac predje mesto gde je bila druga granica. Tada se aktivira kranja animacija gde vestica baca sliku Junaka srece u smece.   

Pokretanje igre:    
Linux - gcc Main.c -lGL -lGLU -lglut -lm    
Windows - Otvoriti datoteku JunakSrece.vcxproj u VisualStudio i pokrenuti ga odatle.

