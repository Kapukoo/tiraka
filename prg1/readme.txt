TIRAKA projekti 1, rautatiet.
Kasper Kivistö
kasper.kivisto@tuni.fi
50302871

Projektin toteutuksessa on käytetty asemien ja alueiden perustietojen tallentamiseen unordered_map tietorakennetta (station_data ja region_data), johon on lisättynä oma struct. Tällöin perustietojen kuten nimen ja koordinaattien haku on helppoa aseman tai alueen id:llä. unordered_mappia on käytetty tässä siitä syystä, että se on mahdollistaa nopean hakemisen uniikkien avaimien (tässä tapauksessa id:n) avulla. 

Toteutuksen muissa kohdissa, joissa tarvitaan esimerkiksi tietyssä järjestyksessä asemien teitoja, on käytetty erilaisia tietorakenteita, esimerkiksi aakkosjärjestelyssä map -tietorakennetta ja paikan avulla järjestelyssä mmultiset -tietorakennetta. Näin toteutettuna samaa dataa tallennetaan ja poistetaan monesta eri tietorakenteesta, joka tulee viemään enemmän muistia, mutta näin saadaan nopeutettua koodin suoritusta.

Seuraavaksi nopea perustelut jokaiselle tietorakenteelle:

-std::vector<StationID> station_ids_vector:
	nopeasti mielivaltaisessa järjestyksessä tulostaessa stationID:t on helpompi lisätä suoraan vektoriin O(1) nopeudella, kuin käydä ne uudelleen for-looppia käyttäen myöhemmin.

-std::map<Name, StationID> stations_in_name_order:
	Map tietorakenne järjestää tiedot heti lisätessä ja tämä on log(n) nopeudella toimiva tapahtuma, verrattuna sort() -funktion nlog(n).

-std::multiset<std::pair <double, std::pair<int, StationID> > > stations_in_lenght:
	Multiset toimii samaan tapaan kuin map, eli kaikki tiedot on heti järjestyksessä, jolloin sorttausta ei tarvitse tehdä. Lisäksi tässä tapauksessa jos pituuden ovat samat niin multiset järjestää tiedot seuraavan parissa olevan datan mukaan. Tässä tapauksessa pienemmän y:n mukaan.

-std::map<Coord, StationID> map_coord_id:
	Nopea hakeminen log(n) uniikilleilla koordinaitella vastaava StationID. 
