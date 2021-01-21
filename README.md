# LoRa-TX-RX-Test
Very simple and basic software to enable testing of LoRa modulation system for model submarine use at 434 MHz. This has NOT been tested in a model sub as yet because of the Covid lockdown. Only 4 channels and 4 times a second refresh rate used to provide a minimalistic control system. Has a failsafe which is activated after 10 seconds of no signal.
Uses standard defaults for RadioLib:
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
2 Nano Everys at TX. One converts ppm to serial data.
RX uses Nano or Nano Every and a Semtech SX1278 LORA Module with a logic level convertor.
