#################################################################################################
##
## @file:       izracun_donosa.py
##
## @brief:      Izracun donostnosti nepremicnin z upoštevanjem stroškov, davkov in uporabe vzvoda.
##
##              Uporabo vzvoda je povzeto iz knjige "Kam je izginil moj denar" Robert T. Kiyosaki.
##
## @date:		05.10.2023
## @author:		Ziga Miklosic
## @version:    V0.0.5
##
#################################################################################################

#################################################################################################
##  IMPORTS
#################################################################################################
import os

#################################################################################################
##  DEFINITIONS
#################################################################################################

## Script version
SCRIPT_VERSION          = "V0.0.5"

## Stopnja normiranega dohodka
#
# Unit: %
NORMIRNA_DOHODEK_PER    = 10.0

## Davek na dobišek najema
#
# Unit: %
DAVEK_NA_DOBICEK_PER    = 25.0

## Zavarovanje nepremicnine
#
# Unit: € / mes
ZAVAROVANJE_NEPREMICNINE_EUR = 3.58

## Dodatek na stavbno zemljisce
#
#   Enkrat na leto
#
# Unit: €
STAVBNO_ZEMLJISCE_EUR = 50.0

## Obdobje nenajemnosti
#
#   Na letni ravni v mesecih
#
# Unit: stevilo mesecev
OBDOBJE_NENAJMENOSTI_MES = 2

## Stroski obnove
#
#   V procentih letnega prihodka
#
# Unit: %
STROSEK_OBNOVE_PER = 7

## Stanovanjski sklad
#
# Unit: €/mes
STANOVANSKI_SKLAD_EUR = 39.79



#################################################################################################
##  FUNCTIONS
#################################################################################################


# ===============================================================================
# @brief:   Main program entry
#
# @return:       void 
# ===============================================================================
def main():

    # Clear console
    os.system("cls")

    print( "******************************************************************" )
    print( "Skripta: izracun_donosa.py" )
    print( "Verzija: %s" % SCRIPT_VERSION )
    print( "******************************************************************" )
    print( "" );

    # Cena nepremicnine
    i_cena = 0

    # Kvadratura
    i_kvadratura = 0

    # Najemnina
    i_najemnina = 0
    print( "==================================================================" )
    print( "    PODATKI O NEPREMICNINI ");
    print( "" );
    i_cena = float( input( "Cena nepremicnine [€]: " ))
    i_kvadratura = float( input( "Kvadratura [m^2]: " ))
    i_najemnina = float( input( "Visina najemnine [€]: " ))

    print( "" )
    print( "==================================================================" )
    print( "    PODATKI O VZVODU (KREDITIRANJU) ");
    print( "" );
    i_lastni_kapital = float( input( "Lastni kapital [€]: " ))
    i_obrok_kredita = float( input( "Mesešni obrok [€]: " )) 

    if i_kvadratura > 0:
        print( "" );
        print( "==================================================================" )
        print( " %40s" % "KONFIGURACIJA SKRIPTE");
        print( " %20s: %.1f %%"         % ( "Davek na dohodek",         DAVEK_NA_DOBICEK_PER ))
        print( " %20s: %.1f %%"         % ( "Normiran dohodek",         NORMIRNA_DOHODEK_PER ))
        print( " %20s: %.0f mesecev"    % ( "Obdobje nenajemnosti",     OBDOBJE_NENAJMENOSTI_MES ))
        print( " %20s: %.2f €"          % ( "Zavarovanje",              ZAVAROVANJE_NEPREMICNINE_EUR ))
        print( " %20s: %.1f %%"         % ( "Stroski obnove",           STROSEK_OBNOVE_PER ))
        print( "" );
        print( " %20s: %.2f k€/m^2"     % ( "Cena na povrsino",         ( i_cena / i_kvadratura ) ))
        print( "" );

        # Izracun davkov in prihodkov
        bruto_prihodek      = ( 12 - OBDOBJE_NENAJMENOSTI_MES ) * i_najemnina
        davcna_osnova       = ( bruto_prihodek * ((( 100.0 - NORMIRNA_DOHODEK_PER ) / 100.0 )))
        davek               = ( davcna_osnova * ( DAVEK_NA_DOBICEK_PER / 100.0 ))
        neto_prihodek       = ( bruto_prihodek - davek )
        
        # Izracun stroskov
        stroski_obnove      = ( STROSEK_OBNOVE_PER/100.0 * neto_prihodek )
        stroski_sklad       =  STANOVANSKI_SKLAD_EUR * 12 
        stroski_zavarovanje =  ZAVAROVANJE_NEPREMICNINE_EUR * 12
        stroski_kredita     = ( i_obrok_kredita * 12 )
        stroski_skupaj      = stroski_obnove + STAVBNO_ZEMLJISCE_EUR + stroski_sklad + stroski_zavarovanje + stroski_kredita

        # Izracun dobicka
        dobicek = neto_prihodek - stroski_skupaj

        print( "==================================================================" )
        print( " %30s" % "DOHODKI (letno)")
        print( " %20s: %.2f €" % ( "Bruto dohodek", bruto_prihodek ))
        print( " %20s: %.2f €" % ( "Davcna osnova", davcna_osnova ))
        print( " %20s: %.2f €" % ( "Davek",         davek ))
        print( "  ------------------------------------------------------")
        print( " %20s: %.2f €" % ( "Neto dohodek",  neto_prihodek ))
        print( "" );

        print( "==================================================================" )
        print( " %30s" % "ODHODKI (letno)")
        print( " %20s: %.2f €" % ( "Obnova",            stroski_obnove ))
        print( " %20s: %.2f €" % ( "Stavbno",           STAVBNO_ZEMLJISCE_EUR ))
        print( " %20s: %.2f €" % ( "Zavarovanje",       stroski_zavarovanje ))
        print( " %20s: %.2f €" % ( "Stan. sklad",       stroski_sklad ))
        print( " %20s: %.2f €" % ( "Stroški kredita",   stroski_kredita ))
        print( "  ------------------------------------------------------")
        print( " %20s: %.2f €" % ( "Skupni stroški",    stroski_skupaj ))
        print( "" );

        print( "==================================================================" )
        print( " %30s" % "DENARNI TOK (letno)")
        print( " %20s: %.2f €" % ( "Neto prihodek",     neto_prihodek ))
        print( " %20s: %.2f €" % ( "Skupni stroski",    stroski_skupaj ))
        print( "  ------------------------------------------------------")
        print( " %20s: %.2f € (%.2f €/mesec)" % ( "Denarni tok", dobicek, dobicek/12 ))
        print( "" )

        print( "==================================================================" )
        print( " %30s" % "DONOSNOST")
        print( " %20s: %.2f %%" % ( "Letna donosnost",  (( dobicek / i_cena ) * 100 )))
        print( " %20s: %.1f let" % ( "St. let izplacitve",  ( i_cena / dobicek )))
        print( "" )

        if i_obrok_kredita > 0:
            print( "==================================================================" )
            print( " %30s" % "DONOSNOST Z UPOSTEVANJEM VZVODA (glede na lastni vlozen kapital)")
            print( " %20s: %.2f %%" % ( "Letna donosnost",  (( dobicek / i_lastni_kapital ) * 100 )))
            print( " %20s: %.1f let" % ( "St. let izplacitve",  ( i_lastni_kapital / dobicek )))
            print( "" )
    else:
        print( "Neveljavni vhodni podatki!" )


    input( "Press any key to exit..." );

    # **********************************************************************
    #   MAIN LOOP
    # **********************************************************************
    while True:
        break


#################################################################################################
##  CLASSES
#################################################################################################


#################################################################################################
# Main
#################################################################################################
if __name__ == "__main__":
    main()
