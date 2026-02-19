#ifndef GPS_HANDLER_H
#define GPS_HANDLER_H

void gps_init(int tx_io, int rx_io);
float get_gps_latitude(void);
float get_gps_longitude(void);

#endif