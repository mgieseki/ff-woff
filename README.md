# Reduced FontForge library for dvisvgm

This is a radically reduced version of the [FontForge](http://fontforge.org) library required to natively
build [dvisvgm](http://dvisvgm.bplaced.net) on Windows. Most of the code not needed to create autohinted
TrueType and WOFF fonts from [SFD](https://fontforge.github.io/sfdformat.html) files has been removed.

The reduced library depends on [libiconv](https://www.gnu.org/software/libiconv) and [zlib](http://www.zlib.net).

---
Thanks to George Williams and the FontForge project contributors for developing this great font editor and for
providing it as open source.
