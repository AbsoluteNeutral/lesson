/* -*- mode: C++ -*-
 *
 *  Conversions between Latitude/Longitude and UTM
 *              (Universal Transverse Mercator) coordinates.
 *
 *  License: Modified BSD Software License Agreement
 *
 *  $Id$
 */
#ifndef _UTMA_H
#define _UTMA_H

/**  @file

 @brief Universal Transverse Mercator transforms.

 Functions to convert (spherical) latitude and longitude to and
 from (Euclidean) UTM coordinates.

 @author Chuck Gantz- chuck.gantz@globalstar.com
 
 Links:
 https://github.com/bakercp/ofxGeo/blob/master/libs/UTM/include/UTM/UTM.h
 https://fypandroid.wordpress.com/2011/09/03/converting-utm-to-latitude-and-longitude-or-vice-versa/
 http://pbw.eng.cu.edu.eg/wp-content/uploads/sites/14/pbw1/2016/3-PBW101A-Coordinate-systems.pdf
 
 
 */

#include <cmath>
#include <stdio.h>
#include <stdlib.h>



namespace UTMA
{
    // Grid granularity for rounding UTM coordinates to generate MapXY.
    const double grid_size = 100000.0;    // est. < 100 km grid
#define DEG_TO_RAD 0.017453292519943295769236907684886f
#define RAD_TO_DEG 57.295779513082320876798154814105f

// WGS84 Parameters (meters)
#define WGS84_A		6378137.0           // major axis Equatorial Radius (a)
#define WGS84_B		6356752.31424518    // minor axis Polar Radius      (b)
#define WGS84_F		0.0033528107	    // ellipsoid flattening         (a-b)/a
#define WGS84_E		0.0818191908	    // first eccentricity(est.0.08) sqrt(1-b2/a2)
// #define WGS84_EP	0.0820944379	    // second eccentricity

    // UTM Parameters
#define UTM_K0		0.9996		        // scale factor
// #define UTM_FE	500000.0	        // false easting
#define UTM_FN_N	0.0                 // false northing, northern hemisphere
#define UTM_FN_S	10000000.0          // false northing, southern hemisphere
#define UTM_E2		(WGS84_E*WGS84_E)   // e^2 (est. 0.007)
#define UTM_E4		(UTM_E2*UTM_E2)	    // e^4
// #define UTM_E6		(UTM_E4*UTM_E2)		// e^6
#define UTM_EP2		(UTM_E2/(1-UTM_E2))	// e'^2

    /**
     * Determine the correct UTM letter designator for the
     * given latitude
     *
     * @returns 'Z' if latitude is outside the UTM limits of 84N to 80S
     *
     * Written by Chuck Gantz- chuck.gantz@globalstar.com
     */
    char UTMLetterDesignator(const double Lat)
    {
        char LetterDesignator = 'Z';
        int ZoneLetterNumber = int((Lat + 84)/8)-1;
        switch(ZoneLetterNumber) {
            case 0: LetterDesignator = 'X'; break;
            case 1: LetterDesignator = 'W'; break;
            case 2: LetterDesignator = 'V'; break;
            case 3: LetterDesignator = 'U'; break;
            case 4: LetterDesignator = 'T'; break;
            case 5: LetterDesignator = 'S'; break;
            case 6: LetterDesignator = 'R'; break;
            case 7: LetterDesignator = 'Q'; break;
            case 8: LetterDesignator = 'P'; break;
            case 9: LetterDesignator = 'N'; break;
            case 10: LetterDesignator = 'M'; break;
            case 11: LetterDesignator = 'L'; break;
            case 12: LetterDesignator = 'K'; break;
            case 13: LetterDesignator = 'J'; break;
            case 14: LetterDesignator = 'H'; break;
            case 15: LetterDesignator = 'G'; break;
            case 16: LetterDesignator = 'F'; break;
            case 17: LetterDesignator = 'E'; break;
            case 18: LetterDesignator = 'D'; break;
            case 19: LetterDesignator = 'C'; break;
            default: break; // Error
        }
        // if     ((84 >= Lat) && (Lat >= 72))  LetterDesignator = 'X';
        // else if((72 > Lat)  && (Lat >= 64))  LetterDesignator = 'W';
        // else if((64 > Lat)  && (Lat >= 56))  LetterDesignator = 'V';
        // else if((56 > Lat)  && (Lat >= 48))  LetterDesignator = 'U';
        // else if((48 > Lat)  && (Lat >= 40))  LetterDesignator = 'T';
        // else if((40 > Lat)  && (Lat >= 32))  LetterDesignator = 'S';
        // else if((32 > Lat)  && (Lat >= 24))  LetterDesignator = 'R';
        // else if((24 > Lat)  && (Lat >= 16))  LetterDesignator = 'Q';
        // else if((16 > Lat)  && (Lat >= 8))   LetterDesignator = 'P';
        // else if(( 8 > Lat)  && (Lat >= 0))   LetterDesignator = 'N';
        // else if(( 0 > Lat)  && (Lat >= -8))  LetterDesignator = 'M';
        // else if((-8 > Lat)  && (Lat >= -16)) LetterDesignator = 'L';
        // else if((-16 > Lat) && (Lat >= -24)) LetterDesignator = 'K';
        // else if((-24 > Lat) && (Lat >= -32)) LetterDesignator = 'J';
        // else if((-32 > Lat) && (Lat >= -40)) LetterDesignator = 'H';
        // else if((-40 > Lat) && (Lat >= -48)) LetterDesignator = 'G';
        // else if((-48 > Lat) && (Lat >= -56)) LetterDesignator = 'F';
        // else if((-56 > Lat) && (Lat >= -64)) LetterDesignator = 'E';
        // else if((-64 > Lat) && (Lat >= -72)) LetterDesignator = 'D';
        // else if((-72 > Lat) && (Lat >= -80)) LetterDesignator = 'C';
        return LetterDesignator;
    }

    /**
     * Convert lat/long to UTM coords.  Equations from USGS Bulletin 1532
     *
     * East Longitudes are positive, West longitudes are negative.
     * North latitudes are positive, South latitudes are negative
     * Lat and Long are in fractional degrees
     *
     * Written by Chuck Gantz- chuck.gantz@globalstar.com
     */
    static void LLtoUTM(const double Lat, const double Long, 
                        double &UTMNorthing, double &UTMEasting, char* UTMZone)
    {
        double a            = WGS84_A;
        double eccSquared   = UTM_E2;
        double k0           = UTM_K0;

        double LongOrigin;
        double eccPrimeSquared;
        double N, T, C, A, M;

        // Make sure the longitude is between -180.00 .. 179.9
        double LongTemp     = (Long+180) - int((Long+180)/360)*360-180;
        double LatRad       = Lat       * DEG_TO_RAD;
        double LongRad      = LongTemp  * DEG_TO_RAD;
        double LongOriginRad;
        int    ZoneNumber;

        ZoneNumber = int((LongTemp + 180)/6) + 1;   // 1 zone is 6 degree apart

        // special case
        if( Lat >= 56.0 && Lat < 64.0 && LongTemp >= 3.0 && LongTemp < 12.0 )
            ZoneNumber = 32;

        // Special zones for Svalbard
        //if( Lat >= 72.0 && Lat < 84.0 )
        //{
        //    if(      LongTemp >= 0.0  && LongTemp <  9.0 ) ZoneNumber = 31;
        //    else if( LongTemp >= 9.0  && LongTemp < 21.0 ) ZoneNumber = 33;
        //    else if( LongTemp >= 21.0 && LongTemp < 33.0 ) ZoneNumber = 35;
        //    else if( LongTemp >= 33.0 && LongTemp < 42.0 ) ZoneNumber = 37;
        //}
        
        
        // +3 puts origin in middle of zone
        /*
        1 zone is 6 degree apart
        Find LongOrigin(x), center of grid:
        8|--- ---| 
         |--- ---|
         |--- ---|
         |--- ---|
         |---x---| (here)
         |--- ---|
         |--- ---|
         |--- ---|
        0|--- ---|
         0       6
        */
        LongOrigin      = (ZoneNumber - 1)*6 - 180 + 3;
        LongOriginRad   = LongOrigin * DEG_TO_RAD;

        //compute the UTM Zone from the latitude and longitude
        sprintf(UTMZone, "%d%c", ZoneNumber, UTMLetterDesignator(Lat));


        // compute Meridional Arc ( 2 methods, S or M)
        double ecc4   = UTM_E2 * UTM_E2;
        double ecc6   = UTM_E2 * UTM_E2 * UTM_E2;
        M = a * (
            (1 - eccSquared/4 - 3*ecc4/64 - 5*ecc6/256) * LatRad
            - (3*eccSquared/8 + 3*ecc4/32 + 45*ecc6/1024)*sin(2*LatRad)
            + (15*ecc4/256 + 45*ecc6/1024)*sin(4*LatRad)
            - (35*ecc6/3072)*sin(6*LatRad)
            );
            
        // compute Northing and Easting
        eccPrimeSquared = (eccSquared)/(1-eccSquared);

        N = a/sqrt(1-eccSquared*sin(LatRad)*sin(LatRad));   // nu
        T = tan(LatRad)*tan(LatRad);
        C = eccPrimeSquared*cos(LatRad)*cos(LatRad);
        A = cos(LatRad)*(LongRad-LongOriginRad);

/*
x = easting = K4p + K5p3 + 500000.0
K4 = k0 nu cos(lat)
K5 = (k0 nu cos^3(lat)/6)[1 – tan^2(lat) + v^2cos^2(lat)]
       
k0 * nu * ( cos(lat) + [cos^3(lat)/6)][1 – tan^2(lat) + e’^2 cos^2(lat)])
*/            
        // simplify
        // UTMEasting = (double)
        // (k0 * N * 
        //     (A + (1-T+C)*A*A*A/6 
        //     + (5-18*T+T*T+72*C-58*eccPrimeSquared)*A*A*A*A*A/120)
        //     + 500000.0);

        // Raw
        UTMEasting = (double)
        ( (k0 * N * cos(LatRad) * p) +
           
            (
             (k0 * N * cos(LatRad)* cos(LatRad)* cos(LatRad) / 6) * 
             (1 - tan(LatRad)*tan(LatRad) + eccPrimeSquared * cos(LatRad)* cos(LatRad))
             * p* p* p
            )
        + 500000.0) ;
        
        
/*

p = (LongRad-LongOriginRad)

K1 + K2p^2 + K3p^4

K1 = Sk0,
K2 = k0 nu sin(lat)cos(lat)/2 p^2
   = k0 nu p^2 sin(2lat)/4 
K2:
    sin(lat)cos(lat)/2
    = sin(lat)cos(lat) * 1/2
    = 1/2 * sin(2lat)  * 1/2
    = 1/4 * sin(2lat)
    
let v = e’^2
K3 = [k0 nu sin(lat)cos^3(lat)/24][(5 – tan^2(lat) + 9v^2cos^2(lat) + 4v^4cos^4(lat))] p^4
K3 = k0 nu [sin(lat)cos^3(lat)/24][(5 – tan^2(lat) + 9v^2cos^2(lat) + 4v^4cos^4(lat))] p^4

  -> [sin(lat)cos^3(lat)/24][(5 – tan^2(lat) + 9v^2cos^2(lat) + 4v^4cos^4(lat))]

K3:
    = 1/24 * (5 * sin(lat)cos^3(lat)
            – tan^2(lat) * sin(lat)cos^3(lat)
            + 9v^2cos^2(lat) * sin(lat)cos^3(lat)
            + 4v^4cos^4(lat) * sin(lat)cos^3(lat))

    k0 * ( M + k0 nu sin(2 lat)/4 + [(nu sin(lat)cos3(lat)/24)][(5 – tan2(lat) + 9e’2cos2(lat) + 4e’4cos4(lat)]

*/
        // simplify
        // UTMNorthing = (double)
        // (k0*(M + N * tan(LatRad) *(A*A/2+(5-T+9*C+4*C*C)*A*A*A*A/24
        //       + (61-58*T+T*T+600*C-330*eccPrimeSquared)*A*A*A*A*A*A/720)));
        
        // raw
        double p = LongRad-LongOriginRad;
        UTMNorthing = (double)
        ( (M * k0) +
          (k0 * N * 1/4 * sin(2*LatRad) * p * p ) +
          
          ( ((k0 * N * sin(LatRad)*cos(LatRad)*cos(LatRad)*cos(LatRad)) / 24) 
            * (5 - tan(LatRad)*tan(LatRad) + 9*eccPrimeSquared*cos(LatRad)*cos(LatRad)
                + 4*eccPrimeSquared*cos(LatRad)*cos(LatRad)*cos(LatRad)*cos(LatRad))
          ) * p * p * p * p
        );
            


        if(Lat < 0)
        {
            //10000000 meter offset for southern hemisphere
            UTMNorthing += 10000000.0;
        }
    }

    /**
     * Converts UTM coords to lat/long.  Equations from USGS Bulletin 1532
     *
     * East Longitudes are positive, West longitudes are negative.
     * North latitudes are positive, South latitudes are negative
     * Lat and Long are in fractional degrees.
     *
     * Written by Chuck Gantz- chuck.gantz@globalstar.com
     */
    static void UTMtoLL(const double UTMNorthing, const double UTMEasting,
                        const char* UTMZone, double& Lat,  double& Long )
    {
        double k0 = UTM_K0;
        double a = WGS84_A;
        double eccSquared = UTM_E2;
        double eccPrimeSquared;
        double e1 = (1-sqrt(1-eccSquared))/(1+sqrt(1-eccSquared));
        double N1, T1, C1, R1, D, M;
        double LongOrigin;
        double mu, phi1Rad;
        double x, y;
        int ZoneNumber;
        char* ZoneLetter;

        x = UTMEasting - 500000.0; //remove 500,000 meter offset for longitude
        y = UTMNorthing;

        ZoneNumber = strtoul(UTMZone, &ZoneLetter, 10);
        if((*ZoneLetter - 'N') < 0)
        {
            //remove 10,000,000 meter offset used for southern hemisphere
            y -= 10000000.0;
        }

        //+3 puts origin in middle of zone
        LongOrigin = (ZoneNumber - 1)*6 - 180 + 3;
        eccPrimeSquared = (eccSquared)/(1-eccSquared);
        
        M = y / k0;
        mu = M/(a*(1-eccSquared/4-3*eccSquared*eccSquared/64
                   -5*eccSquared*eccSquared*eccSquared/256));
        
        phi1Rad = mu + ((3*e1/2-27*e1*e1*e1/32)*sin(2*mu) 
                        + (21*e1*e1/16-55*e1*e1*e1*e1/32)*sin(4*mu)
                        + (151*e1*e1*e1/96)*sin(6*mu));
        
        N1 = a/sqrt(1-eccSquared*sin(phi1Rad)*sin(phi1Rad));
        T1 = tan(phi1Rad)*tan(phi1Rad);
        C1 = eccPrimeSquared*cos(phi1Rad)*cos(phi1Rad);
        R1 = a*(1-eccSquared)/pow(1-eccSquared*sin(phi1Rad)*sin(phi1Rad), 1.5);
        D = x/(N1*k0);
        
        Lat = phi1Rad - ((N1*tan(phi1Rad)/R1)
                         *(D*D/2
                           -(5+3*T1+10*C1-4*C1*C1-9*eccPrimeSquared)*D*D*D*D/24
                           +(61+90*T1+298*C1+45*T1*T1-252*eccPrimeSquared
                             -3*C1*C1)*D*D*D*D*D*D/720));
        
        Lat = Lat * RAD_TO_DEG;
        
        Long = ((D-(1+2*T1+C1)*D*D*D/6
                 +(5-2*C1+28*T1-3*C1*C1+8*eccPrimeSquared+24*T1*T1)
                 *D*D*D*D*D/120)
                / cos(phi1Rad));
        Long = LongOrigin + Long * RAD_TO_DEG;
        
    }
} // end namespace UTM

#endif // _UTM_H
