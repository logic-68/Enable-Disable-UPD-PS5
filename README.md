# Enable-Disable-UPD-PS5

Enable-Disable-UPD-PS5 v1.0.3
- total rewrite
- Principle of operation not changed
- Rewrites the blocker internally when it was deleted by mistake
- Changed the conversion of the string "kern.sdk_version" which seemed to be problematic

Enable-Disable-UPD-PS5 v1.0.2

Enable or disable your PS5 updates.
- Now detects your firmware version and applies the necessary files from an updates folder, containing all system versions from your USB.
- Requires for the first execution a USB key with the files necessary for each update.
- After the first execution, the files necessary for your system version will be copied internally. This will enable or disable the payload. Simply start the payload as desired.(No longer need USB constantly)
- If you want a new update of your files. Simply connect a USB disk again with the different Updates.
- Let the detection act to apply the new files. The process will start again.

# Credits
- [PS5Dev](https://github.com/PS5Dev) 
- [OpenOrbis](https://github.com/OpenOrbis)
- [master] (https://twitter.com/master_s9) for files blocker
- [SISTRo] (https://github.com/SiSTR0) for Version PS5
- [@notzecoxao](https://twitter.com/notzecoxao)

# required
Ubuntu 20.04
gcc


