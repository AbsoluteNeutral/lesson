#include "utm.h"
#include "myutm.h"
#include <stdio.h>

int main(){

    double Lat = 1.360010;
    double Long = 103.772049;
    double utmNorth = 0.0;
    double utmEast = 0.0;
    char   utmZone[4];

    UTM::LLtoUTM(1.360010, 103.772049, utmNorth, utmEast, utmZone);
    
    printf("North:%lf, East:%lf, Zone:%s\n", utmNorth, utmEast, utmZone);
    
    UTM::UTMtoLL(utmNorth, utmEast, utmZone, Lat,  Long);
    printf("Lat:%lf, Long:%lf\n", Lat, Long);
    
    
    double Lat2 = 1.360010;
    double Long2 = 103.772049;
    double utmNorth2 = 0.0;
    double utmEast2 = 0.0;
    char   utmZone2[4];
    
    UTMA::LLtoUTM(1.360010, 103.772049, utmNorth2, utmEast2, utmZone2);
    printf("North:%lf, East:%lf, Zone:%s\n", utmNorth2, utmEast2, utmZone2);
    
    UTMA::UTMtoLL(utmNorth2, utmEast2, utmZone2, Lat2, Long2);
    printf("Lat:%lf, Long:%lf\n", Lat2, Long2);
}
