#!/bin/bash

IFACE=eth0
# trigger IPv6 neighbour discovery with link-local scope multicast:
ping6 -c2 -I $IFACE ff02::1 > /dev/null
# print the results, filtered by MAC address vendor prefix of Raspberry Pi Foundation:
ip -6 neigh | grep b8:27:eb
