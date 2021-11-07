# RG129-junak-srece

# Kontrole: 
Igrac se moze kretati pomocu tastera AWDS, a za pucanj koristi taster K.

Precice:    
n/N - preskace najavnu spicu(pocetnu animaciju)   
p/P - precica za preskakanje prvog sektora    
o/O - pokrece krajnju animaciju   

# Tok igre:         
Pocetna animacija: vestica krade sliku iz muzeja i bezi kroz portal, a za njom krece kugla sa stuba koja je ustvari macka.  
Prvi nivo: cilj je upucati sve neprijatelje kako bi granica nestala i zapoceo drugi nivo.    
Drgi nivo: cilj je sakupiti pravi kljuc za otvaranje druge granice i izaci iz lavirinta.    
Zavrsna animacija(kraj igre): kraj igre je kad igrac predje mesto gde je bila druga granica. Tada se aktivira kranja animacija gde vestica baca sliku Junaka srece u smece.   

# Funkcionalnost igre:    
Health igraca predstavljen je kao tri srca u gornjem desnom uglu ekrana. Radnje koje rezultuju gubljenjem jednog health-a su: kolizija igraca i kackastog neprijatelja, kolizija igraca i pucnja bilo kog neprijatelja, kolizija igraca i siljaka. U slucaju da igrac prilikom ovih desavanja ima vise od jednog zivota bice restartovan na odgovarajuce mesto (startnu poziciju prvog ili drugog nivoa). Ako je igrac izgubio poslednji zivot igrica se restartuje.    

Kocka neprijatelj menja boju kao upozorenje igracu pre nego sto ispali svoj pucanj. 

U drugom nivou jedan kjuc otvara granicu i taj kljuc je neophodno skupiti za prelazak igrice. Drugi kljuc je klopka koja aktivira pomerajuci zid siljaka i nije potrebno skupiti ga za zavrsetak igrice. 
# Pokretanje igre:    
Linux - gcc Main.c -lGL -lGLU -lglut -lm    
Windows - Otvoriti datoteku JunakSrece.vcxproj u VisualStudio i pokrenuti ga odatle.

