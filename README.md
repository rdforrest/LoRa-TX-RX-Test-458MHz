# LoRa-TX-RX-Test
Very simple and basic software to enable testing of LoRa modulation system for model submarine use at 458 MHz. This has NOT been tested in a model sub as yet because of the Covid lockdown. Only 6 channels and 4 times a second refresh rate used to provide a minimalistic control system for test purposes only. Has a failsafe which is activated after 10 seconds of no signal.
Uses standard defaults for RadioLib but with Frequency set to 458.75 and Bandwidth set to 62.5kHz for the UK (Thanks to Simon H for the suggestion. Edit SX1278.h file in src/modules in RadioLib to set this.)
Thanks to Jonathan Askey for suggesting and providing the accurate ppm reader.
SX127x/RFM9x - LoRa modem
Begin method:
Carrier frequency: 434.0 MHz (for SX1276/77/78/79 and RFM96/98) or 915.0 MHz (for SX1272/73 and RFM95/97)
Bandwidth: 125.0 kHz (dual-sideband)
Spreading factor: 9
Coding rate: 4/7
Sync word: SX127X_SYNC_WORD (0x12)
Output power: 10 dBm
Preamble length: 8 symbols
Gain: 0 (automatic gain control enabled)
Other:
Over-current protection: 60 mA
Inaccessible:
LoRa header mode: explicit
Frequency hopping: disabled.
Hardware:
Nanos for TX and RX. 
