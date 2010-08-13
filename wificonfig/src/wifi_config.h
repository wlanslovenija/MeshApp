
#ifndef _WIFI_CONFIG_H
#define _WIFI_CONFIG_H

static void wpa_close_control_connection(void);

static struct wpa_ctrl *wpa_open_control_connection(const char *wpa_directory);

static void wpa_message_callback(char *message, size_t length);

static void wpa_print_scan_results(void);


#endif /* _WIFI_CONFIG_H */
