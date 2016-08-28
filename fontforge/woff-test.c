#include <fontforge.h>

int main () {
	errno = 0;
	FILE *tmp = tmpfile2();
	fclose(tmp);
	InitSimpleStuff();

	SplineFont *sf = SFDRead("XITSMath.sfd");
	if (sf) {
		//	Encoding *enc = FindOrMakeEncoding("unicode");
		//	EncMap *map = EncMapFromEncoding(sf, enc);
		WriteWOFFFont("test.woff", sf, ff_woff, 0, 0, 0, sf->map, ly_fore);
		SplineFontFree(sf);
	}
//	free(map);
}
