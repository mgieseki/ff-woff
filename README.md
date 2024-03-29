#### This repository has been archived since [dvisvgm](https://github.com/mgieseki/dvisvgm) no longer depends on the FontForge library.

# Reduced FontForge library for dvisvgm

This is a radically reduced version of the [FontForge](https://fontforge.github.io) library required to natively
build [dvisvgm](https://dvisvgm.de) on Windows. Most of the code not needed to create autohinted
TrueType and WOFF fonts from [SFD](https://fontforge.github.io/sfdformat.html) files has been removed.

The reduced library depends on [zlib](http://www.zlib.net).

---
Thanks to George Williams and the FontForge project contributors for developing this great font editor and for
providing it as open source.
