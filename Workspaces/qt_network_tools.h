#pragma once


/**
 * @brief Finds an available port starting from the specified start_port.
 *
 * @param start_port The port number to start searching from.
 * @return The first available port number, or -1 if no port is available.
 */
int find_available_port(int start_port);